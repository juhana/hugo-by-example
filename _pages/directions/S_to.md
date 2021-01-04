---
title: s_to
permalink: /directions/s_to/
categories: 
  - Directions
  - Properties
---

`s_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO SOUTH",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the south."
        s_to twistypassage2
    }

It is [aliased](alias) by the
[ignore_response](ignore_response) property.
