---
title: object
permalink: /globals/object/
categories: 
  - Global Variables
---

The `object` [global](basics/global/) is set each turn by the
[grammar matching](definitions/grammar-matching/) stage of the
[game loop](loops/game-loop/). The simplest way to describe it is the
first object mentioned (of a possible two) in one command. In "GET
ROCK", the `object` would be set to the rock object.

That said, the `object` global is not read-only so the author can change
it manually at any point to work better with other verb routines.
