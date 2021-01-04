---
title: Replace Parse
permalink: /replacements/parse/
categories: 
  - Replacements
---

### What it fixes

Currently, if HugoFix's parser monitoring is on,
`Parse` attempts to print [parse$](/parsing/parse$/) each turn.
Unfortunately, `parse$` is not set until after
[grammar matching](/loops/game-loop/), so `parse$` equals "" in most cases
(the exception to this rule is commands where the string
[grammar token](/basics/grammar-tokens/) is used). This version removes that
`parse$`-printing code (see also:
[replace ParseError](/replacements/parseerror/)).

This also removes the [jump](/guts/jump/) command so the jump labels
don't clash with the original routine.

### The code

    replace Parse
    {
        local a
        local reparse
        local temp_verb, temp_obj, temp_xobj
        local JumpToEnd

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

    #ifclear OLD_STYLE_PRONOUNS
        ! Only need to set up all attributes once, so that a given
        ! pronoun will satisfy any grammatical attribute requirements
        if it_object is not 127
        {
            local i
            for (i=0; i<128; i++)
            {
                it_object is i
                him_object is i
                her_object is i
                them_object is i
            }
        }
    #endif

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

    #ifclear OLD_STYLE_PRONOUNS
        move it_object to parent(it_obj)
        move him_object to parent(him_obj)
        move her_object to parent(her_obj)
        move them_object to parent(them_obj)
    #endif

        ! To repeat last command
        if (word[1] = "again" or word[1] = "g") and word[2] = ""
        {
            for (a=1; a<=oldword[0]; a++)
                word[a] = oldword[a]
            words = oldword[0]
            reparse = true
            JumpToEnd = true
        }
        if  not JumpToEnd
            {

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

            }
        ! old "LeaveParse area

    #ifset DEBUG
        if debug_flags & D_PARSE
        {
            local w
            Font(BOLD_ON)
            for (w=1; w<=words and word[w]~=""; w++)
                {
                print "[";
                if (word[w] ~= -1)
                    print word[w];
                else
                    print "\Iparse$\i";
                "] ";
                }
            print newline
            Font(BOLD_OFF)
        }
    #endif
        return reparse
    }
