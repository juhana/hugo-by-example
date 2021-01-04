---
title: Replace Perform
permalink: /replacements/perform/
categories: 
  - Replacements
---

### What it fixes

1.  Removes the [jump](/guts/jump/) command... just because.
    Personally, I've never had to [replace](/guts/replace/)
    `Perform`.

### The code

    replace Perform(action, obj, xobj, queue, isxverb)
    {
        local r
        local objtemp, xobjtemp, verbtemp, actortemp
    #ifclear NO_XVERBS
        local restoring
        if verbroutine = &DoRestore:  restoring = true
    #endif

    #ifset DEBUG
        if debug_flags & D_PARSE
        {
            print "\B[Perform("; number action; ", "; obj.name;
            if (debug_flags & D_OBJNUM) or queue = -1
                print " ["; number obj; "]";
            print ", "; xobj.name;
            if (debug_flags & D_OBJNUM) or queue = -1
                print " ["; number xobj; "]";
            if queue
                print ", "; number queue;
            print ")]\b"
        }
    #endif

        if queue
            parser_data[PARSER_STATUS] |= PERFORM_QUEUE

        if not queue and object
            parser_data[LAST_SINGLE_OBJECT] = object
        else
            parser_data[LAST_SINGLE_OBJECT] = 0

        parser_data[VERB_IS_XVERB] = isxverb

        objtemp = object
        xobjtemp = xobject
        verbtemp = verbroutine
        actortemp = actor

        object = obj
        xobject = xobj
        verbroutine = action
        actor = player

    #ifclear OLD_STYLE_PRONOUNS
        local number_pronouns = 0
        if object = it_object:      object = it_obj
        elseif object = him_object: object = him_obj
        elseif object = her_object: object = her_obj
        elseif object = them_object:    object = them_obj
        if object ~= obj
        {
            replace_pronoun[number_pronouns] = object
            number_pronouns++
        }
        if xobject = it_object:     xobject = it_obj
        elseif xobject = him_object:    xobject = him_obj
        elseif xobject = her_object:    xobject = her_obj
        elseif xobject = them_object:   xobject = them_obj
        if xobject ~= xobj
        {
            replace_pronoun[number_pronouns] = xobject
            number_pronouns++
        }
        if number_pronouns
        {
            parser_data[PARSER_STATUS] |= PRONOUNS_SET
            PrintReplacedPronouns(number_pronouns)
        }
    #endif

    #ifclear NO_OBJLIB
        SetupDirectionObjects
    #endif

        ! Itemize each object in a list of multiple objects
        if queue > 0 and object > display
        {
    #ifset USE_CHECKHELD
            ! Check if an ImplicitTakeForDrop was just done, meaning we
            ! need a newline before printing the next "object:"
            if checkheld is workflag
                print ""
            checkheld is not workflag
    #endif
            print object.name; ":  ";
        }

        r = BeforeRoutines(queue)
        if not r ! if action not stopped by before routines
            {
            r = call action                 ! object.after and xobject.after
                            ! run by verbroutine
    #ifclear NO_XVERBS
            if restoring
                verbroutine = &DoRestore
    #endif
            if r  ! if action was successful, run after routines
                {
                AfterRoutines
                }
            }

    !:DonePerform area
    #ifset USE_CHECKHELD
        ResetCheckHeld
    #endif

        last_object = object

        verbroutine = verbtemp
        object = objtemp
        xobject = xobjtemp
        actor = actortemp

        if queue = -1
            last_object = -1
        parser_data[PARSER_STATUS] = PARSER_RESET

        return r
    }
