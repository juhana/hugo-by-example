---
title: n_to
permalink: /directions/n_to/
categories: 
  - Directions
  - Properties
---

`n_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "GO NORTH",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the north."
        n_to twistypassage2
    }

It is [aliased](basics/alias/) by the `statusline_height` property.
