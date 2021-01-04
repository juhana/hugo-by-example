---
title: Location
permalink: /globals/location/
categories: 
  - Global Variables
---


`location` is a [global variable](Globals) set by
[init](init) at the beginning of the game and by travel
[routines](routines) like [MovePlayer](MovePlayer)
and [DoGo](DoGo) after a successful move. Having a global
variable to refer to allows for easy checking of the
[player](player)'s [scope](scope) (or even, just
the name of the current room).

### Using `location` to check scope

    if <object> in location

### Putting something *always* in scope

    object <some object>
    {
        found_in location ! will be available in every room
    }
