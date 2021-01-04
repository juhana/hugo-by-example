---
title: Location
permalink: /globals/location/
categories: 
  - Global Variables
---


`location` is a [global variable](basics/global/) set by
[init](routines/init/) at the beginning of the game and by travel
[routines](routines/) like [MovePlayer](routines/moveplayer/)
and [DoGo](verb-routines/dogo/) after a successful move. Having a global
variable to refer to allows for easy checking of the
[player](globals/player/)'s [scope](scope/) (or even, just
the name of the current room).

### Using `location` to check scope

    if <object> in location

### Putting something *always* in scope

    object <some object>
    {
        found_in location ! will be available in every room
    }
