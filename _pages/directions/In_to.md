---
title: in_to
permalink: /directions/in_to/
categories: 
  - Directions
  - Properties
---

`in_to` is a [direction](classes/direction/) property given to
[rooms](basics/rooms/). When a player types, "IN",
[DoGo](verb-routines/dogo/) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit going in."
        in_to twistypassage2
    }
