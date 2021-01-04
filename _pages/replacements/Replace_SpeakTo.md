---
title: Replace SpeakTo
permalink: /replacements/speakto/
categories: 
  - Replacements
---

*See also: [SpeakTo](/parsing/speakto/)*

### What it fixes

1.  Removes the [jump](/guts/jump/) command for easy replacing.
2.  Is pickier about when it sets and clears the
    [speaking](/globals/speaking/) global now.
3.  Has some code to allow for successful (returning true)
    conversation-ending commands

### The code

    replace SpeakTo(char)
    {
        local TryOrder, IgnoreResponse, retval, stay, same, different
    #ifset USE_CHECKHELD
        if verbroutine = &DoDrop_CheckHeld
            verbroutine = &DoDrop
        elseif verbroutine = &DoPutIn_CheckHeld
            verbroutine = &DoPutIn
    #endif

    #ifset VERBSTUBS
        if verbroutine = &DoHelpChar and object = player
        {
            verbroutine = &DoHelp
            object = nothing
        }
    #endif

    #ifset USE_CHECKHELD
        ResetCheckHeld
    #endif

    #ifset DEBUG
        if debug_flags & D_PARSE
        {
            print "\B[Speakto("; char.name;
            if (debug_flags & D_OBJNUM)
                print " ["; number char; "]";
            print ") verbroutine="; number verbroutine;
            print ", object="; object.name;
            if (debug_flags & D_OBJNUM)
                print " ["; number object; "]";
            print ", xobject="; xobject.name;
            if (debug_flags & D_OBJNUM)
                print " ["; number xobject; "]";
            print "]\b"
        }
    #endif

        if char is not living
        {
            ParseError(6)  ! "That doesn't make any sense."
            return
        }

        AssignPronoun(char)

        ! Handle player/typist-related ParseError messages:
        if char = player
            Message(&Speakto, 1)    ! "Stop talking to yourself..."
        elseif not ObjectisKnown(object) and not FindObject(object, location)
            ParseError(10, object)
        else
            stay = true

        if not stay
           {
           speaking = 0
           return
           }

        if char is unfriendly
            IgnoreResponse = true
        else
        {
            ! In the event of:  >CHARACTER, GO NORTH.  GET THE THING.  GO WEST., etc.
            if not FindObject(char, location)
            {
                speaking = char
                run char.order_response
                return true
            }

            same = (char = speaking)

            select verbroutine
                case 0                  ! Just the character name is given,
                            ! so just "X is listening."
                {
                    if not char.order_response
                        Message(&Speakto, 2, char)
                    retval = true
                }

    #ifclear NO_VERBS
                case &DoHello           ! Note the ampersands ('&')--or else
                {                       ! the routines themselves would run
                    if not char.order_response
                    {
                        if char is not unfriendly
                            {
                            ! "X nods hello."
                            Message(&Speakto, 3, char)
                            retval = true
                            }
                        else
                        {
                            IgnoreResponse = true
                        }
                    }
                    else
                        retval = true
                }

                case &DoAskQuestion
                    return Perform(&DoAsk, char, object)

                case &DoTalk
                {
                    if xobject
                        ParseError(6)
                    else
                        return Perform(&DoAsk, char, object)
                }

                case &DoTell
                {
                    if object = player
                        return Perform(&DoAsk, char, xobject)
                    else
                        TryOrder = true
                }
    #endif  ! ifclear NO_VERBS

                case else
                {

        ! If the character can respond to a request, this should be dealt with by
        ! an order_response property routine; order_response--if it exists--should
        ! return false if there is no response for the given verbroutine

                    TryOrder = true
                }
        }

        if TryOrder
        {
            if (not char.order_response)
                IgnoreResponse = true
            else
                retval = true
        }

        different = (speaking ~= char)

    !   This same/different local variable stuff allows for certain
    !   orders to end conversations. If your order_response code clears
    !   the speaking global, this code prevents it being reset.

        if retval and not (same and different)
            speaking = char

        if IgnoreResponse
        {
            if not char.ignore_response
                Message(&Speakto, 4, char)      ! "X ignores you."
            speaking = 0  ! clear the speaking global
        }
        return retval
    }
