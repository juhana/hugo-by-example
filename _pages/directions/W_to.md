---
title: w_to
permalink: /directions/w_to/
categories: 
  - Directions
  - Properties
---

`w_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "GO WEST",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the west."
        w_to twistypassage2
    }

It is [aliased](basics/alias/) by the [contains_desc](properties/contains_desc/) property.
