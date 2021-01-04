---
title: out_to
permalink: /directions/out_to/
categories: 
  - Directions
  - Properties
---

`out_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "OUT",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit leading out."
        out_to twistypassage2
    }
