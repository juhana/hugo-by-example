---
title: u_to
permalink: /directions/u_to/
categories: 
  - Directions
  - Properties
---

`u_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO UP",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit going up."
        u_to twistypassage2
    }

It is [aliased](alias) by the [desc_detail](desc_detail) property.
