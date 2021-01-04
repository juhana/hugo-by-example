---
title: ne_to
permalink: /directions/ne_to/
categories: 
  - Directions
  - Properties
---

`ne_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "GO NORTHEAST",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the northeast."
        ne_to twistypassage2
    }

It is [aliased](basics/alias/) by the
[key_object](properties/key_object/) property.
