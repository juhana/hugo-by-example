---
title: n_to
permalink: /directions/n_to/
categories: 
  - Directions
  - Properties
---

`n_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO NORTH",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the north."
        n_to twistypassage2
    }

It is [aliased](alias) by the
[statusline_height](statusline_height) property.
