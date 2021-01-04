---
title: DoTell
permalink: /verb-routines/dotell/
categories: 
  - Verb Routines
---

`DoTell` is the [verb routine](:Category:Verb_Routines)
responsible for processing "tell" commands.

## The code

    !----------------------------------------------------------------------------
    routine DoTell
    {
        if object = player
            VMessage(&DoAsk, 2)      ! "Talking to yourself..."

        if xobject = 0
        {
            VMessage(&DoTell, 1)    ! "Tell about something specific..."
            return false
        }

        speaking = object


        if object is unfriendly
        {
            if not object.ignore_response
                Message(&Speakto, 4)    ! "X ignores you."
            speaking = 0
        }
        else
        {
            if not object.after
            {
                if not xobject.after
                    VMessage(&DoTell, 2)    ! "Not interested..."
            }
    #ifclear NO_SCRIPTS
            SkipScript(object)
    #endif
        }
        return true
    }
