---
title: player
permalink: /globals/player/
categories: 
  - Global Variables
---

`player` is a [hugolib.h](/library/hugolib.h/)-defined 
[global variable](/basics/global/) that points to the
[[player character object](/characters/). This is done in the
[init](/routines/init/) routine that sets up the game, but it can be
changed at any point (if you are writing a game with
[character-switching](/strings/changing-player-characters/)).

Of course, setting the `player` global variable in
[init](/routines/init/) is what lets all of your routines and things
refer to the player as "player".
