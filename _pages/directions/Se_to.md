---
title: se_to
permalink: /directions/se_to/
categories: 
  - Directions
  - Properties
---

`se_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO SOUTHEAST",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the southeast."
        se_to twistypassage2
    }

It is [aliased](alias) by the
[when_closed](when_closed) property.
