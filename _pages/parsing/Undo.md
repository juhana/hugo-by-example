---
title: undo
permalink: /parsing/undo/
categories: 
  - Parsing
---

`undo` is a built-in function for reverting to the previous turn. All
[globals](basics/global/) and property values and such are set back
to their earlier values, with the notable exception of the
[word array](basics/word-array/). Most commonly, it is used by the verb
routine `DoUndo`.

### How to call

`undo` returns a [true](definitions/true/) or [false](definitions/false)
value based on its success, so it is called in the following manner:

    x = undo ! the x variable gets set to 1 or 0
    ! or
    if not undo
         "(message to be printed if undo doesn't work)"

The conditional "if not undo" itself executes `undo`. If it works, the
game goes back a turn. If it doesn't, we print some kind of error
message. This is how `DoUndo` does it.

# `undo` Options

The following explores additional `undo` options an author has at his or
her disposal.

## Turning UNDO Off

#### Permanently

If you are writing some kind of nontraditional game or are just a bad
person, you can "`#set NO_UNDO`" in your game so &gt;UNDO is not
recognized as a command (nor will it mention UNDO when EndGame() is
called).

#### Temporarily

If there are sections of your game where you don't want UNDO to work,
you can set the global variable [`UNDO_OFF`](globals/undo_off/) to a
non-zero value, resulting in an "Unable to undo." response. Set
`UNDO_OFF` back to 0 when the player is in the clear again.

## Limiting The Number of Undos

Normally, the Hugo interpreter will allow `UNDO` for as many turns as
memory allows. On some platforms, this can be more than a thousand
turns. Although not necessarily recommended, you could limit the number
of times one can UNDO for consistency across platforms or to give the
player a larger sense of finality. Let's use
[PreParse](parsing/preparse/)!

    global undo_counter

    player_character you "you"
    {
        before
            {
            actor PreParse
                {
                ! We check to see if the player is UNDOing
                            ! and add to our undo_counter
                if (word[1] = "undo","u") and word[2] = 0
                    {
                        undo_counter++
                        return false
                    }
                ! The player hasn't UNDO'd. let's reset the undo_counter!
                else
                    {
                    undo_counter = 0
                    return false
                    }
                }
            }
    }


    ! In this example, we limit the player to 5 UNDOs
    replace DoUndo
    {
        if undo_counter > 5
            {
            "Can't undo anymore."
            return false
            }
        if not UNDO_OFF
        {
            if undo
            {
                PrintStatusline
                DescribePlace(location)
            }
            else
                VMessage(&DoUndo)
        }
        else
            VMessage(&DoUndo)
    }

## One UNDO To Win Them All

What if you have a game where you want UNDO to take a player back to
before he made a game unwinnable (no matter how many turns)? We can loop
UNDO and the player won't suspect a thing! Silly player! *(Not always
possible; see note at bottom.)*

    global badness
    global turns_since_badness

    routine main
    {
        if badness  {
                turns_since_badness++
                }
           < rest of your main code >
    }

    room STARTINGLOCATION "Start Location"
    {
           long_desc {
                     "That kiddie pool sure looks inviting!"
                     }
           in_to {
                 if not waterwings in player
                 badness = 1
                 return KiddiePool
                 }
    }

    room KiddiePool "The Kiddie Pool"
    {
          long_desc {
                    if waterwings is not worn
                           "Oh dear, this pool is actually quite deep. You are drowning! Agonizingly slowly!"
                    else
                           "Yay! Splashsville!"
                    }
    }

    replace DoUndo
    {
        if badness
            "(Undoing back until the game was winnable.)"
        if not UNDO_OFF
        {
            if undo
            {
                            ! no need to alter the value of turns_since_badness since a successful undo
                            ! decreases it anyways
                if turns_since_badness
                {
                Perform(&DoUndo,0,0,0,1)
                return
                }
                PrintStatusline
                DescribePlace(location)
            }
                    ! On the slight chance the interpreter runs out of undo memory before it gets
                    ! back to a winnable state
            elseif turns_since_badness
                    {
                    "Dang, we can't UNDO enough to put you in a winnable position. I hope you saved!"
                     return
                    }
                    else
                VMessage(&DoUndo)
        }
        else
            VMessage(&DoUndo)
    }

Unwinnable position? More like *unswimmable* position, har har! Of
course, you could also use similar code to take a player back to the
beginning of a conversation tree that you don't want them dissecting one
move at a time or whatever other scenario you could think of.
