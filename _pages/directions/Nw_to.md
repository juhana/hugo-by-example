---
title: nw_to
permalink: /directions/nw_to/
categories: 
  - Directions
  - Properties
---

`nw_to` is a [direction](/classes/direction/) property given to
[rooms](/basics/rooms/). When a player types, "GO NORTHWEST",
[DoGo](/verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the northwest."
        nw_to twistypassage2
    }

It is [aliased](/basics/alias/) by the [inv_desc](/properties/inv_desc/) property.
