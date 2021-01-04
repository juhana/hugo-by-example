---
title: Events
permalink: /timers/events/
categories: 
  - Timers
---

Events are routines that are run every turn (well, every non-xverb,
true-returning, counter-increasing turn). An untampered-with `main`
routine looks like:

    routine main
    {
            counter = counter + 1
            PrintStatusLine
            run location.each_turn
            runevents
            RunScripts
            if speaking not in location
                    speaking = 0
    }

As you can see, events are run after `location.each_turn` but before
character scripts.

## There Are Two Kinds of Event in the World

### global events

Global events are executed every turn of the game. It is defined like
this:

    event
    {
    ...Event routine...
    }

### global attached to an object

The other kind of global is executed only when the player is in scope of
a particular object. The object can be any kind of object really,
including the location itself or a [`found_in`](Found_in)
object. This kind of object is defined like this:

    event in <object>  ! the "in" is optional
    {
    ...Event routine...
    }

If the `self` token is used in the event code, it'll refer to the object
the event is attached to.

[Fuses](Fuses_and_Daemons) and
[daemons](Fuses_and_Daemons) are actually just
object-attached events that are moved in and out of scope with
`Activate` and `Deactivate` routines.

## event_flag reminder

In a game without modified `DoWait` routines, waiting takes up three
turns. If your events are designed to be run one step (or command) at a
time, you'll have to insert set the [event_flag](Event_flag)
global to the right setting, depending on the behavior that you want.
