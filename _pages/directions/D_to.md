---
title: d_to
permalink: /directions/d_to/
categories: 
  - Properties
  - Directions
---

`d_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "GO DOWN",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit going down."
        d_to twistypassage2
    }
