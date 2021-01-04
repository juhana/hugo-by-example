---
title: MapGen
permalink: /contributions/mapgen/
categories: 
  - Library Contributions
---

`MapGen` is yet another one of Cardinal Teulbach's library
contributions. It assigns random connections to a set of rooms. Download it
[here](http://ifarchive.smallwhitehouse.org/if-archive/programming/hugo/library/contributions/mapgen.h).
There are some rules in its use:

1.  Rooms must be defined a certain way (see below).
2.  Randomly-connected rooms must be defined consecutively (with no
    other objects defined between them).
3.  Call `MakeMap()` when you'd like to initially set the room
    connections (or would like to shuffle them again).

### Randomly-Connected Room Definitions

`MapGen` is picky when it comes to rooms. You may want to create a class
of rooms like the following:

    property coord  ! declare the coord property that MakeGen uses

    room randomroom
    {
        coord 0,0,0
        n_to 0
        ne_to 0
        e_to 0
        se_to 0
        s_to 0
        sw_to 0
        w_to 0
        nw_to 0
    !\ games with up and down would also need
            u_to 0
            d_to 0    \!
    }

    ! allowing you to do:

    randomroom r1 "cave passage"
    {}
