---
title: PreParse
permalink: /parsing/preparse/
categories: 
  - Parsing
  - Routines
---

PreParse, as one might guess, is called by [Parse](Parse) and
executed before the bulk of parsing is done.

In `hugolib.h`, it looks like this:

    routine PreParse
    {}

It is an empty canvas just waiting to be painted
([replaced](replace)) by you! PreParse can be used for
several techniques, some of which we will explore here.

# Things to know about PreParse

-   When `PreParse` is called, [object](Object_(Global)) and
    [xobject](xobject) have not been set by the engine yet.
-   `PreParse` is only called if the player's input line has been
    successfully matched to [verb grammar](verb_grammar).
    Otherwise, the engine calls [ParseError](ParseError)
    directly.
-   When `PreParse` is called, the global
    [verbroutine](verbroutine) still equals the verb routine
    of the previous turn. It will be reset by the engine after
    [Parse](Parse) is finished.

# Uses for PreParse

### Spoon-feeding the Parser

Sometimes it's hard to set up our verb grammar to properly understand
every variation of a command. We can use PreParse to reorder commands
into something our game will like better:

*Kent Tessman's Down*

    replace PreParse
    {
        local i

        ! Since "get off wing" or "exit wing" will cause a parser complaint
        ! because the player isn't really "in" the wing, change either to
        ! simply "exit" (i.e., to direct the library to out_to).
        !
        if (word[1] = "get", "climb") and word[2] = "off"
        {
            word[1] = "exit"
            DeleteWord(2)
        }
        if word[1] = "exit" and ObjWord(word[2], wing)
            DeleteWord(2)

        ! Allow handing of, e.g., "ask girl about her mother", so that "her"
        ! doesn't get mapped incorrectly
        !
        if word[1] = "ask", "tell"
        {
            for (i=2; i<=words and word[i]~=""; i++)
            {
                if word[i] = "his", "her", "your"
                {
                    DeleteWord(i)
                    break
                }
            }
        }
    }

In another example, the game understands the problem command just fine.
We just don't like the result it gives.

*John Menichelli's HugoZork*

    ! This routine replaces "~all" with "grue" - if "~all" is passed through
    ! while in a dark location or while the player is a ghost, multiple
    ! "It's too dark to see!" or "Your hand passes through the object." messages
    ! will be printed; one for each object in the location. I replaced it with
    ! "grue" because the grue is a scenery item that is always in the player's
    ! location and thus can always be referred to.

    replace PreParse
    {
            if (not FindLight(location) or
               player is ghost) and
               word[1] ~= "drop"
            {
                    if word[2] = "~all"
                    {
                            word[2] = "grue"
                    }
                    elseif word[3] = "~all"
                    {
                            word[3] = "grue"
                    }
            }
            return false
    }

### Other Methods of Using Pre-Parse

Without even touching PreParse itself, you can also use PreParse to
execute code each turn by adding code to the player_character object.

*Kent Tessman's Future Boy!*

            before
            {
            actor PreParse
            {
                ! Reset things that need resetting each turn

                ! SOUND_STOP here so that, for instance, dialogue doesn't
                ! continue for several turns if the player keeps typing
                !if not just_played_sound
                !   PlaySound(SOUND_STOP)
                just_played_sound = false

                if display.needs_repaint
                {
                    CheckIndentSize

                    if DisplayHasGraphics
                    {
                        ClearFullScreen
                        PrintStatusline
                        if DisplayHasGraphics
                            ForceAllPanelRepaint
                    }

                    display.needs_repaint = false
                }
                return false
            }

Notice that it returns false so any PreParse routine code is also run.

>**Important Note**
>
>If you add or subtract words from the word array, be sure to update the `words` global or else [Parse](Parse) may not function correctly.

So yeah, PreParse is useful indeed. Remember our slogan- "Got a problem
the parser can't handle? That's 'PreParse'-terous!"

See also: [Parse](Parse)
