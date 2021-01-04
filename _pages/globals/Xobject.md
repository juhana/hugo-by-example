---
title: xobject
permalink: /globals/xobject/
categories: 
  - Global Variables
---

The `xobject` [global](basics/global/) is set each turn by the
[grammar matching](definitions/grammar-matching/) stage of the 
[game loop](loops/game-loop/). The simplest way to describe it is the
second object mentioned (of a possible two) in one command. In "UNLOCK
DOOR WITH KEY", the `xobject` would be set to the key object.

That said, the `xobject` global is not read-only so the author can
change it manually at any point to work better with other verb routines.
