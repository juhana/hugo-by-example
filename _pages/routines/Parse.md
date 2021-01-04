---
title: Parse
permalink: /routines/parse/
categories: 
  - Routines
  - Parsing
---

Parse is the routine that interprets the input line. For the most part,
authors won't need to touch it at all (unless they are writing their own
parser, at which point this whole site would probably be useless).
Still, you will probably want to take a look at it, especially if you
are working with [PreParse](/parsing/preparse/),
[AssignPronoun](/parsing/assignpronoun/),
[SetObjWord](/parsing/setobjword/), or
[ParseError](/parsing/parseerror/).

### The code

Here is the Parse routine itself. For a better understanding of every
routine that Parse calls, take a look at `hugolib.h`.

    !----------------------------------------------------------------------------
    ! Parse is called by the engine without parameters after input but before
    ! any grammar matching; returning true signals the engine to reparse the
    ! existing input (in case it has been changed)
    !
    ! The engine parser is responsible for splitting the input line into the
    ! word[] array, removing removals, replacing synonyms, and combining
    ! compounds.
    !
    ! This Parse routine is then called to take care of:
    !       - picking out extra_scenery words
    !       - checking for an "again" command
    !       - rewording imperatives to "<Name>, <command>"
    !       - renaming pronouns to objects
    !       - changing "then <do something else>" into a new command
    !
    ! Control then returns to the engine for grammar matching and, if that is
    ! successful, calling of the matched verb routine.

    ! NOTE:  There are some snags with the object-based pronoun replacement
    ! system (such as, for example, requiring a specific object in grammar)
    ! so OLD_STYLE_PRONOUNS are still being used.

    #set OLD_STYLE_PRONOUNS

    ! skipping some #ifclear OLD_STYLE_PRONOUNS code

    routine Parse
    {
        local a
        local reparse
        local temp_verb, temp_obj, temp_xobj

        ResetParse

        list_nest = 0
        event_flag = 0

        if nothing ~= 0                   ! best place to check this
            print "[WARNING:  Objects/classes defined before library]"

    #ifset DEBUG
        if debug_flags & D_PARSE_RANK
        {
            print "[parser_data[BEST_PARSE_RANK] = 0]"
        }
    #endif

    ! skipping some #ifclear OLD_STYLE_PRONOUNS code

        if word[1] = "~oops"
            return

        ! Allow the player object to override the parsing cycle completely
        temp_verb = verbroutine
        temp_obj = object
        temp_xobj = xobject
        verbroutine = &PreParse
        object = nothing
        xobject = nothing
        if player.before
        {
            verbroutine = temp_verb
            object = temp_obj
            xobject = temp_xobj
            parser_data[PARSER_STATUS] = 0
            parser_data[LAST_PARSER_STATUS] = 0
            return false
        }
        verbroutine = temp_verb
        object = temp_obj
        xobject = temp_xobj

    ! The following, devised by Jim Newland, checks to see if the player
    ! input refers to an unnecessary item of scenery (for example) which is
    ! nonetheless mentioned in the location description.

        for (a=2; a<=words and word[a]~="" and word[a]~="then"; a++)
        {
            if Inlist(location, extra_scenery, word[a])
            {
                Message(&Parse, 1)
                word[1] = ""            ! force ParseError(0)
                words = 0
                customerror_flag = true
                return true
            }
        }

        if PreParse:  reparse = true            ! easily replaceable routine

        ! Last player-specified object
        if object > 0 and object < objects and last_object ~= -1
            AssignPronoun(object)
        parser_data[LAST_PARSER_STATUS] = 0

        ! Must do this after AssignPronoun, and reset it to 0
        ! after both of Perform and ParseError:
        parser_data[PARSER_STATUS] = PARSER_ACTIVE

    ! skipping some #ifclear OLD_STYLE_PRONOUNS code

        ! To repeat last command
        if (word[1] = "again" or word[1] = "g") and word[2] = ""
        {
            for (a=1; a<=oldword[0]; a++)
                word[a] = oldword[a]
            words = oldword[0]
            reparse = true
            jump LeaveParse
        }

        local count
    #ifset OLD_STYLE_PRONOUNS
        local n, number_pronouns
    #endif

        for (count=2; count<=words and word[count]~=""; count++)
        {
            select word[count]

    #ifset OLD_STYLE_PRONOUNS
                ! Rename pronouns to appropriate objects
                case "it", "them", "him", "her"
                {
                    select word[count]
                        case "it":      a = it_obj
                        case "them":    a = them_obj
                        case "him":     a = him_obj
                        case "her":     a = her_obj

                    if a = nothing
                    {
                        ! "...be a little more specific"
                        ParseError(13)
                        words = 0
                        customerror_flag = true
                        return
                    }
                    ! Avoid, e.g., "put it it something"
                    elseif word[count] ~= word[count+1]
                    {
                        ! For her_obj, we can run into trouble, since
                        ! it's both possessive and a pronoun, so only
                        ! replace "her" where it's the last word:
                        if a ~= her_obj or
                            (a = her_obj and (count = 2 or count = words))
                        {
                            n = SetObjWord(count, a)
                            replace_pronoun[number_pronouns] = a
                            number_pronouns++
                            if n > 1
                                count = count + (n - 1)
                            parser_data[PARSER_STATUS] |= PRONOUNS_SET
                            reparse = true
                        }
                    }
                }
    #endif

                ! Allow for "then..." and "and then..."
                case "then"
                {
                    ! end of this command
                    word[count] = "."
                    if word[count-1] = "~and"
                        DeleteWord(count-1)
                    reparse = true
                    break
                }
        }

    #ifset OLD_STYLE_PRONOUNS
        if number_pronouns = 2 and replace_pronoun[0] = replace_pronoun[1]
            number_pronouns--

        if number_pronouns > 0
        {
            PrintReplacedPronouns(number_pronouns)
        }
    #endif

    ! Reword imperatives given as "Tell Bob to do something" as "Bob, do
    ! something" so that the engine automatically reroutes them to SpeakTo

        if word[1] = "tell", "order", "instruct", "ask", "command"
        {
            for (a=1; a<=words and word[a]~=""; a++)
            {
                if word[a] = "to"
                {
                    !DeleteWord(a)   ! "to"
                    word[a] = "~and"
                    DeleteWord(1)   ! "tell", "order", etc.
                    reparse = true
                    break
                }
            }
        }

    #ifset USE_PLURAL_OBJECTS
        if ParsePluralObjects:  reparse = true
    #endif

    #ifset USE_CHECKHELD
        ParseCheckHeld
    #endif

        ! Store current command for future reference
        local ow
        for (a=1; a<=words and a<MAX_WORDS; a++)
        {
            if word[a] = "g", "again"
            {
                if word[a+1] = ""
                    a++
            }
            else
                oldword[++ow] = word[a]
        }
        oldword[a] = ""
        oldword[0] = ow

    :LeaveParse

    #ifset DEBUG
        if debug_flags & D_PARSE
        {
            Font(BOLD_ON)
            for (a=1; a<=words and word[a]~=""; a++)
                print "["; word[a]; "] ";
            print newline
            if parse$ ~= ""
                print "[parse$ = \""; parse$; "\"]"
            Font(BOLD_OFF)
        }
    #endif

        return reparse
    }
