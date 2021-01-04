---
title: move
permalink: /guts/move/
categories: 
  - Hugo Guts
---

`move` is an [object-tree](Object_Tree)-defying command that
lets you move any object to another object willy-nilly. This, of course,
is for behind-the-scenes operations like introducing a new element to
the player character's location or moving something somewhere else.

One simple way to dispose of an item is to move it to the default object
[nothing](nothing) (of course, you could also just use the
[remove](remove) function).

### Hugo Homework

Write a wishing well object that, when it receives objects, moves them
to the location `BottomOfWell`.
