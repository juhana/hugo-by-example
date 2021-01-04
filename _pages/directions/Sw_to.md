---
title: sw_to
permalink: /directions/sw_to/
categories: 
  - Directions
  - Properties
---

`sw_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO SOUTHWEST",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the southwest."
        sw_to twistypassage2
    }

It is [aliased](alias) by the
[order_response](order_response) property.
