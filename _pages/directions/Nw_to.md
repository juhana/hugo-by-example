---
title: nw_to
permalink: /directions/nw_to/
categories: 
  - Directions
  - Properties
---

`nw_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO NORTHWEST",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the northwest."
        nw_to twistypassage2
    }

It is [aliased](alias) by the [inv_desc](inv_desc) property.
