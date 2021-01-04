---
title: old_location
permalink: /globals/old_location/
categories: 
  - Global Variables
---

`old_location` is a [global variable](/basics/global/) used to hold
the previous room the [player](/globals/player/) was
in. Set by "travel" [routines](/routines/) like
[MovePlayer](/routines/moveplayer/) and [DoGo](/verb-routines/dogo/) after a
successful move, its value stays the same until the next successful
move. [Follow.h](/contributions/follow/) uses it to move followers into the
room the player is in.

## Hugo Homework

Code a room where an alarm is tripped if you enter from one
direction but not another one.
