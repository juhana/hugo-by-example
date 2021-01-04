---
title: w_to
permalink: /directions/w_to/
categories: 
  - Directions
  - Properties
---

`w_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO WEST",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the west."
        w_to twistypassage2
    }

It is [aliased](alias) by the [contains_desc](contains_desc) property.
