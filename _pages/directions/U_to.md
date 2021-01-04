---
title: u_to
permalink: /directions/u_to/
categories: 
  - Directions
  - Properties
---

`u_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "GO UP",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit going up."
        u_to twistypassage2
    }

It is [aliased](basics/alias/) by the [desc_detail](properties/desc_detail/) property.
