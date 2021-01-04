---
title: player
permalink: /globals/player/
categories: 
  - Global Variables
---

`player` is a [hugolib.h](hugolib.h)-defined [global
variable](Globals) that points to the [player character
object](characters#Player_Characters). This is done in the
[init](init) routine that sets up the game, but it can be
changed at any point (if you are writing a game with
[character-switching](Changing_Player_Characters)).

Of course, setting the `player` global variable in
[init](init) is what lets all of your routines and things
refer to the player as "player".
