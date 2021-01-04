---
title: xobject
permalink: /globals/xobject/
categories: 
  - Global Variables
---

The `xobject` [global](global) is set each turn by the
[grammar matching](grammar_matching) stage of the [game
loop](game_loop). The simplest way to describe it is the
second object mentioned (of a possible two) in one command. In "UNLOCK
DOOR WITH KEY", the `xobject` would be set to the key object.

That said, the `xobject` global is not read-only so the author can
change it manually at any point to work better with other verb routines.
