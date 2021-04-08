---
title: found_in
permalink: /scope/found_in/
categories: 
  - Scope
  - Properties
---

The `found_in` [property](properties/) is defined by the
[standard library](library/) and is used for objects
that are in multiple rooms. As such, they don't have specific parent
objects like other objects.

## found_in (object [property](properties/))

    object sun "sun"
    {
         noun "sun"
         long_desc
              "The sun sure is bright!"
         before
              {
            object DoLook
            {
                return false
            }
            object
            {
                "Don't be ridiculous."
            }
              }
         found_in tunnel_entrance, open_field , mountain_top
    }

In the above example, there are three rooms where the sun object can be
referred to.

### adding locations to a found_in property

Imagine you have a game where you divert a small stream. Originally just
in two locations, we want the stream to show up in two more.

         found_in stream_start, stream_fork

The above would NOT allow us to add more rooms to it since the engine
believes that `found_in` property can only have two elements in it.
Instead, we do:

         found_in stream_start, stream_fork, 0, 0

Then, when the player diverts the stream, we would add this code:

         stream.found_in #3 = new_stream_path
         stream.found_in #4 = new_waterfall

Lastly, if your game starts with your `found_in` property comprising of
multiple zero values (like "found_in 0, 0, 0" (to be filled later), you
can do "found_in \#3" instead.

### clearing found_in properties

Since an object with a `found_in` property is not technically *in*
whatever room it is found in, something like **remove <object>** won't
work. Instead, you'll need to set the relevant `found_in` elements to 0.

### other uses

John Menichelli's Hugozork port uses `found_in` to put objects like the
"grue" and "blessings" in the player's scope at all times, allowing such
commands like "what is a grue?" and "count blessings." Here is the
latter example:

    scenery blessings "blessings"
    {
            noun "blessings"
            article "my"
            found_in {return location}
            before
            {
                    object DoCount
                    {
                            "Well, for one, you are playing Hugo Zork..."
                    }
            }
    }

The downside to this is that the player could do something like "&gt;X
BLESSINGS" and get "Blessings look like you would expect." as a
response. Still, that's not a command most players would think to do
under those circumstances, and IF is all about smoke and mirrors anyway
so it's a valid option.
*objlib.h* aliases `found_in` to a couple other
properties. In the door class definition, it is called `between` and is
used to declare which rooms you can see a door from. It is also aliased
to the `part_of` property for component objects since they are in scope
whenever their parent object is around.

### react_before, react_after, and events

Since `found_in` objects are not "physically" in the room according to
the [object tree](basics/object-tree), any `react_before` or
`react_after` code is ignored. [Event](timers/events/) code, on the
other hand, *is* run. Since events are run after any successful turn,
while there's no way to replace `react_before`, you could easily emulate
the behavior of `react_after`.
