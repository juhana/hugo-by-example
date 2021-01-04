---
title: react_after
permalink: /properties/react_after/
categories: 
  - Properties
---

**react_after** is a [property](properties/) available for an
[object](globals/object/) and is defined by the
[standard library](library/).

## react_after

Unsurprisingly, `react_after` is to
[react_before](properties/react_before/) what
[`after`](properties/after/) is to [`before`](properties/before/). To be
honest, it's a seldom used property (judging by the Hugo game sources on
the IF Archive). Let's throw together an example anyways.

Let's have a game where the PC enters a room where NPC Bob is. We want
the room to be described normally, but then we want Bob to notice the
player and give him a party hat. Hooray!

    room STARTLOCATION "Start Location"
    {
        e_to testroom
    }

    room testroom "Test Room"
    {
        w_to STARTLOCATION
    }

    character bob "Bob"
    {
        noun "bob"
        in testroom
        react_after
            {
            if actor = player and verbroutine = &DoGo and location is not special
                {
                Indent
                "Bob notices you. \"Fantastic! You're here for the party!\""
                Indent
                "He gives you the party hat."
                move partyhat to player
                testroom is special
                }
            else
            return false
            }
    }

    object partyhat "party hat"
    {
        article "a"
        adjective "party"
        noun "hat"
        in bob
    }

Since the location changes mid-DoGo, Bob's `react_after` is still
executed before the turn is over but after DescribePlace has been called
(FOOTNOTE 1). This results in:

<div class="output">

&gt;e

Test Room
Bob is here. Bob has a party hat.
Bob notices you. "Fantastic! You're here for the party!"
He gives you the party hat.

</div>

So yeah, that's one way to use `react_after`.

FOOTNOTE 1 - This example also could have been accomplished with some
"`after {location DoGo`" code.

## found_in objects

Since `found_in` objects are not in the player's location according to
the object tree, a `react_after` property for an object like that would
not be executed. Luckily, [events](timers/events/) for `found_in`
objects *are* run so you can accomplish the same thing that way.
