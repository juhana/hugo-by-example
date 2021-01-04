---
title: return
permalink: /guts/return/
categories: 
  - Hugo Guts
---

`return` is a command for exiting out of routines. Depending on what
value you return, you can "inform" the routine that called it whether
the routine was a success or provide a value for some other purpose.

### Returning false

A routine that gets to its end, without any instruction on how to
return, will be the same as a similar routine that returns false. In
fact, the following three routines, for all intents and purposes, would
act just the same:

    routine test1
    {
       "Hello."
    }

    routine test2
    {
       "Hello."
       return
    }

    routine test3
    {
       "Hello."
       return false
    }

All three would print "Hello." if called, but the routines that called
them won't be able to tell that anything had happened.

### Returning true

Returning any non-zero value, though, is like saying, "Hey, the routine
was successful!" Verb routines return true if successful, at which point
[main](/routines/main/) is run and a turn passes. If they return false,
though, no turn ensues.
Most commonly, returning true is done like this:

    routine DoLookAround
    {
        DescribePlace(location, true)
        return true
    }

(`true` is a "hard-coded Boolean constant meaning 1.")

Because of returning true, a calling routine might do this:

    if Some_Routine
       {
       ...
       some code
       ...
       }
    else
       {
       ...
       some other code
       ...
       }

#### Other values

Of course, sometimes the point of a routine is to actually find a value
for the calling routine! You'll often see things like this:

    routine Some_Routine
    {
    ...
    song_to_play = RandomSong
    ...
    }

    routine RandomSong
    {
        local a
        a = random(5)
        return (jukebox.songs #a)
    }

In the above example, `RandomSong` would return the address of whatever
is in the jukebox object's "songs" property array.

## Returning Routines

Let's say you have a verb routine for a verb that in some circumstances
acts one way and at other times, acts like another already-established
verb. You could have something like this:

    routine DoSwivel
    {
       select object
            case statue : "Now you are getting your games confused."
            case else : return Perform(&DoMove,object)
        return false
    }

Now, the statue will have a special response to "swivel" (but not
"move"), and for every other object, the success of the action will rely
on the success of `Perform(&DoMove)`. If `DoMove` succeeds, it'll return
true, which *`DoSwivel`* will then return true, and the game will use a
turn. Otherwise, `DoSwivel` will not take a turn, just like any other
failed action.

## Returning property values

`return` can be pretty important with property values, too. Object
properties like [name](/properties/name/) expect strings to be provided as
a property value, not a property routine (like
[long_desc](/properties/descriptions/) or
[short_desc](/properties/descriptions/)). In a game where an object's name
depends on circumstance, you could have something like this:

    object car
    {
       noun
           {
           if self is painted
              return "red car"
           else
              return "blue car"
           }
    }

    ! Now it'll be treated just like:
    object car "blue car"
    {}

`return` is also important when using things like
[globals](/basics/global/) or other non-static things for object
property values. If you provide the globals as is, the property will
take the value of the globals at compilation time and leave it at that.
To ensure that it is interpreted as *the value of such-and-such-now*,
you use a property routine to return the current value:

    window_class border_window! "top"
    {
        win_left
            return (display.screenwidth / 2 - 22) ! leftmost column
        win_top
            return (display.screenheight /2 - 3)! topmost row
        win_right
            return (display.screenwidth / 2 + 22) !rightmost column
        win_bottom
            return (display.screenheight /2 + 2) ! bottommost row

        win_textcolor
            return BGCOLOR    ! text color for any output
      win_backcolor
            return SL_TEXTCOLOR    ! background color

    }

Now, when something refers to `border_window.win_left`, that will mean
the current value of "display.screenwidth / 2 - 22".
