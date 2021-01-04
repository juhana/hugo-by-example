---
title: ne_to
permalink: /directions/ne_to/
categories: 
  - Directions
  - Properties
---

`ne_to` is a [direction](direction) property given to
[rooms](rooms). When a player types, "GO NORTHEAST",
[DoGo](DoGo) checks that value to see if there is another
room in that direction.

    room twistypassage "A Maze of Twisty Passage"
    {
        long_desc
            "You are in a maze of twisty passage. There is one exit to the northeast."
        ne_to twistypassage2
    }

It is [aliased](alias) by the
[key_object](key_object) property.
