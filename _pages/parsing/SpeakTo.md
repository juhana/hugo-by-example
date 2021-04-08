---
title: SpeakTo
permalink: /parsing/speakto/
categories: 
  - Parsing
  - Routines
---

*See also: [replace SpeakTo](replacements/speakto/)*

`SpeakTo` is basically a parsing routine. It is called by the engine
when the input is in &gt;CHARACTER, \[SOME COMMAND\] format, among
others. If the character is not
[unfriendly](attributes/), it'll check
that character's [order_response](properties/order_response/) property
for a response. If no response is found (or if the character *is*
unfriendly), the `ignore_response` property is run. If none exist, it
gives the default "*X ignores you.*"

## The code

    !----------------------------------------------------------------------------
    ! SpeakTo is called by the engine when a command is addressed to a
    ! character object via:  SpeakTo(character)
    !
    ! For example, the input line
    !
    !   <character>, get the <object>
    !
    ! will call SpeakTo(<character>), with the global object containing <object>,
    ! and the verbroutine global set to &DoGet

    routine SpeakTo(char)
    {
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

        speaking = 0

        if char is not living
        {
            ParseError(6)
            return
        }

        AssignPronoun(char)

        ! Handle player/typist-related ParseError messages:
        if not FindObject(char, location)
        {
            actor = player
            ParseError(11, char)
            return
        }
        elseif char = player
        {
            actor = player
            Message(&Speakto, 1)    ! "Stop talking to yourself..."
            return
        }
        elseif not ObjectisKnown(object) and not FindObject(object, location)
        {
            actor = player
            ParseError(10, object)
            return
        }

        if char is unfriendly
            jump IgnorePlayer

        speaking = char

        ! In the event of:  >CHARACTER, GO NORTH.  GET THE THING.  GO WEST., etc.
        if not FindObject(char, location)
        {
            run char.order_response
            return true
        }

        select verbroutine
            case 0                  ! Just the character name is given,
                        ! so just "X is listening."
            {
                if not char.order_response
                    Message(&Speakto, 2, char)
            }

    #ifclear NO_VERBS
            case &DoHello           ! Note the ampersands ('&')--or else
            {                       ! the routines themselves would run
                if not char.order_response
                {
                    if char is not unfriendly
                        ! "X nods hello."
                        Message(&Speakto, 3, char)
                    else
                    {
                        jump IgnorePlayer
                    }
                }
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
                    jump TryResponse
            }
    #endif  ! ifclear NO_VERBS

            case else
            {

    ! If the character can respond to a request, this should be dealt with by
    ! an order_response property routine; order_response--if it exists--should
    ! return false if there is no response for the given verbroutine

    :TryResponse

                if not char.order_response
                    jump IgnorePlayer
                return true
            }
        return false

    :IgnorePlayer

        if not char.ignore_response
            Message(&Speakto, 4, char)      ! "X ignores you."
        return false
    }
