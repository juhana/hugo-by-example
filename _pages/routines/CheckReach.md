---
title: CheckReach
permalink: /routines/checkreach/
categories: 
  - Scope
  - Routines
---

## Definition

| calling form         | description                                                                                                                                                                |
|----------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `CheckReach(object)` | Checks to see if the specified object is within reach of the player object. Returns true if accessible; returns false and prints an appropriate message if not accessible. |

From this simple description from the manual, one might imagine that
`CheckReach` can be used whenever you want to check whether a player can
take or manipulate an object. This is not true
([FindObject](/scope/findobject/) is much better suited for *that*
task). `CheckReach` is a routine used specifically for situations where
*some objects are out of reach* (like when the PC is in a chair or
vehicle). In fact, to work properly, it requires you to set a `reach`
property for the object that the player is in.

## Stuck to the couch

Let's jump straight into an example:

    room STARTLOCATION "Living Room"
    {
        long_desc
            "Woo, it's your living room."
    }

    object tv "television"
    {
        in STARTLOCATION
        article "the"
        noun "tv","television"
        long_desc  {
                if self is switchedon
                "The tv is on."
                else
                "The tv is off."
               }
        before
            {
            object DoSwitchOn
                {
                if parent(remote) = player
                    {
                    "You turn on the television with the remote."
                    tv is switchedon
                    return true
                    }
                else
                    return false
                }
            }
        is switchable, static
    }

    object couch "couch"
    {
        article "the"
        nearby tv
        noun "couch"
        reach table remote
        is enterable, platform, static
    }

    object table "coffee table"
    {
        article "the"
        nearby tv
        adjective "coffee"
        noun "table"
        is static, platform
    }

    object remote "remote control"
    {
        article "the"
        adjective "remote"
        noun "remote","control"
        in table
    }

A transcript of a game using this sparse code would look like this:

>Living Room, on the couch  
>Woo, it's your living room.  
>The television and the coffee table are here. Sitting on the coffee
>table is the remote control.
>
>&gt;turn on tv  
>You can't reach the television from the couch.
>
>&gt;get remote  
>Taken.
>
>&gt;turn on tv  
>You turn on the television with the remote.
>
>&gt;x tv  
>The tv is on.

## CheckReach in verb routines

In the couch object above, you'll notice how the `reach` property is
followed by a list the objects you **can** interact with. Everything
else, you can only examine or look into. This is because almost every
verb in [verblib.h](/library/verblib/) runs `CheckReach`. For
example, take a look at **DoMove**:

    routine DoMove
    {
        if not CheckReach(object):  return false

        VMessage(&DoMove)                ! "You can't move that."
        return true
    }

When you add new verbs to your games, remember that if it is a verb
affected by reach, you'll want to add a similar `CheckReach` line.

Other things to keep in mind:

If you want the player to not reach *anything*, try giving the enterable
object a `reach` property of 1.

`CheckReach` will not work properly if `object.before` properties get in
the way. If you have an object with a special failure message for
`DoGet`, you'll have to add a line like
`if player in <reach affecting object>:return false` or
`if not CheckReach(object): return true` (we return true so `CheckReach`
is called only once) to your `object.before.object DoGet` code.

## CheckReach and components

The current `CheckReach` requires that an object within reach also has
all of its components explicitly listed in the `reach` property. If you
want a version that automatically checks for components, look at
"[replace CheckReach](/replacements/checkreach/)".
