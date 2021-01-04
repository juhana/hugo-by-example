---
title: door_to
permalink: /properties/door_to/
categories: 
  - Properties
  - Directions
---

**`door_to`** is a [property](/properties/) defined by the
[standard library](/library/) which allows for
**&gt;ENTER OBJECT** (where [`object`](/globals/object/) leads to
another location). Obviously, it is used by the
[door class](/classes/doors/) defined in *objlib.h*, but
it can be used for lots of other things.

    room castle "Castle"
    {
         long_desc
               "Inside, the castle is exactly what you expected - tacky and featureless
                with ant eggs near the top and gravel at the bottom. To anyone else, the
                colours sprayed randomly on the wall would just be colours sprayed randomly
                on the wall. To a daring inter-dimensional espionage operative like yourself,
                however, they are obviously used to focus communications across the dimensions.
                The only exit is out, back to the goldfish bowl. Your attention is drawn
                to a glass box resting in the middle of the room here, this looks like Panchax's
                work.
                \nA smooth warp, a jagged warp and a small warp are also clearly the boss's
                work."
    }

    scenery smoothwarp "smooth warp"
    {
         in castle
         article "the"
         adjective "smooth"
         noun "warp"
         long_desc
              "The smooth warp looks the trendiest of all the warps. It must lead somewhere
               pretty cool."
         door_to clearing
    }

Which gives us:

>&gt;enter smooth warp  
>Inter-dimensional travel hurts. A lot. Especially when you haven't done
it for a while. You buck and roll through the journey, feeling very
nauseous, then, with a small popping noise, take over a body with the
aid of a customised host-parasite interface. Your host has arms and
legs. Looks like trouble!
>
>Clearing  
>It's stopped raining here at the moment, but the clouds overhead show
that it could start again any minute. If they decide to burst, the tree
stump in the centre of the clearing would probably fill up with water.
Paths go south, southeast and east. In all other directions the
undergrowth is too tangled to make any progress. Micky Blowtorch, your
ex-colleague, now a crazed warp junkie, is lounging around the stump,
looking suitably bemused.  
>&gt;


## More castles

Here is another example since Johnny wants to see some moats and
drawbridges, oh my!

    room bythemoat "By the Moat"
    {
        long_desc
             "You are in front of a moat. Yadda yadda."
    }

    scenery moat "moat"
    {
          article "the"
          noun "moat"
          door_to
                "You don't feel like a swim right now."
          in bythemoat
    }

    object drawbridge "drawbridge"
    {
          article "the"
          noun "drawbridge" "bridge"
          when_open
                "The drawbridge is down."
          when_closed
                "The drawbridge is up."
          door_to {
                  if self is open
                       return insidecastle
                  else
                       "The drawbridge is up."
                  }
          is openable
          in bythemoat
    }
