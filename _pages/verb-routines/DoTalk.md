---
title: DoTalk
permalink: /verb-routines/dotalk/
categories: 
  - Verb Routines
---

`DoTalk` is the [verb routine](:Category:Verb_Routines)
responsible for processing "talk" or "talk to" commands.

## The code

    routine DoTalk
    {
        if word[2] = "to" and not xobject
        {
            if object is unfriendly
            {
                if not object.ignore_response
                    Message(&Speakto, 4)    ! "X ignores you."
                speaking = 0
            }
            elseif object = player
            {
                Message(&Speakto, 1)    ! "Stop talking to yourself."
                return false
            }
            else
            {
                speaking = object
                Message(&Speakto, 2)            ! "X is listening."
    #ifclear NO_SCRIPTS
                SkipScript(object)
    #endif
            }
            return true
        }

        VMessage(&DoTalk, 1)     ! "Tell or ask about something specific..."
        return false
    }
