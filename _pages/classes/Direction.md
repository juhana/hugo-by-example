---
title: Direction
permalink: /classes/direction/
categories: 
  - Classes
---

When a player types **&gt;GO EAST**, the word "east" points to an
`e_obj` direction object. All of the directions (up, down, in, out,
north, northeast, east, southeast, south, southwest, west, and
northwest) have a direction object, and they all are objects in the
`direction` class. These objects are very useful. Routines like
[DoGo](verb-routines/dogo/) and [PushDir](verb-routines/pushdir/) make sure the
current object is of type "direction" and use the `object.dir_to`
[property](properties/) to determine what room exit it should
be looking for.
For information on creating your own directions for the `direction`
class, check out [this page](tips/tedious-shipboard-directions/).


## The class (and its objects)

    property dir_to alias capacity          ! for directions only
    property dir_from alias size            !

    class direction
    {
        type direction
        article "the"
        found_in
        {
            if self in direction
                return location
        }
        long_desc
        {
            OMessage(direction, 1) ! "You see nothing special to the <direction>."
        }
        is static, known
    }

    direction n_obj "north"
    {
        in direction
        nouns "n", "north"
        dir_to n_to
        dir_from s_obj
    }

    direction ne_obj "northeast"
    {
        in direction
        nouns "ne", "northeast"
        dir_to ne_to
        dir_from sw_obj
    }

    direction e_obj "east"
    {
        in direction
        nouns "e", "east"
        dir_to e_to
        dir_from w_obj
    }

    direction se_obj "southeast"
    {
        in direction
        nouns "se", "southeast"
        dir_to se_to
        dir_from nw_obj
    }

    direction s_obj "south"
    {
        in direction
        nouns "s", "south"
        dir_to s_to
        dir_from n_obj
    }

    direction sw_obj "southwest"
    {
        in direction
        nouns "sw", "southwest"
        dir_to sw_to
        dir_from ne_obj
    }

    direction w_obj "west"
    {
        in direction
        nouns "w", "west"
        dir_to w_to
        dir_from e_obj
    }

    direction nw_obj "northwest"
    {
        in direction
        nouns "nw", "northwest"
        dir_to nw_to
        dir_from se_obj
    }

    direction u_obj "above"
    {
        in direction
        nouns "u", "up"
        article ""
        dir_to u_to
        dir_from d_obj
    }

    direction d_obj "below"
    {
        in direction
        nouns "d", "down"
        article ""
        dir_to d_to
        dir_from u_obj
    }

    direction in_obj "in"
    {
        in direction
        noun "in", "inside"
        article ""
        dir_to in_to
        dir_from out_obj
        long_desc
        {
            OMessage(direction, 2) ! "You'll have to be a little more specific about what you'd like to look in."
        }
    }

    direction out_obj "out"
    {
        in direction
        noun "out", "outside"
        article ""
        dir_to out_to
        dir_from in_obj
        long_desc
        {
            OMessage(direction, 2) ! "You'll have to be a little more specific about what you'd like to look out."
        }
    }

## Direction properties that play nice with others

Occasionally, you might want to write a game that automatically lists
exits for the player or has an automapper. Both of these things use code
that'll check each exit in a room, executing whatever code is in the
direction property. This becomes a problem if you have put print strings
there (or other unexpected code). For this to work, you might need to
employ some of the following coding tricks.

### Direction-specific "can't go" messages

Instead of something like this:

    room cavepassage "Cave Passage"
    {
        w_to bigroom
        e_to
            "There is an impenetrable jumble of rocks in that direction."
    }

Do this:

    room cavepassage "Cave Passage"
    {
        w_to bigroom
        cant_go {
                if object = e_obj
                    "There is an impenetrable jumble of rocks in that direction."
                else
                    return false ! do a normal "You can't go that way" message for other directions
                }
    }

### "Success" messages

Sometimes you'll want some preliminary text before letting a player move
to another room. Instead of:

    room desertroom1 "In The Desert"
    {
        s_to  {
              "Blinking your eyes against the whirling sandstorm, you trudge southward until you reach the..."
              return desertoasis
              }
    }

You might want:

    room desertroom1 "In The Desert"
    {
        s_to  {
              if verbroutine = &DoGo ! the next line will only run if the player actually typed >GO SOUTH
                  "Blinking your eyes against the whirling sandstorm, you trudge southward until you reach the..."
              return desertoasis
              }
    }

Another option would be:

    room desertroom1 "In The Desert"
    {
        s_to desertoasis
        before
           {
           location DoGo
              {
              if object = s_obj
                 "Blinking your eyes against the whirling sandstorm, you trudge southward until you reach the..."
              return false ! go on with DoGo like normal
              }
           }
    }
