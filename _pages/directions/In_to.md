---
title: in_to
permalink: /directions/in_to/
categories: 
  - Directions
  - Properties
---

`in_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "IN",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit going in."
        in_to twistypassage2
    }
