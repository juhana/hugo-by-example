---
title: remove
permalink: /guts/remove/
categories: 
  - Hugo Guts
---

The `remove` command takes an object away from its current
[parent](guts/parent/). As it moves the object to the nothing
object, it is pretty much the same as the command:

    move <object> to 0

All in all, assuming the object isn't in scope by means of
[found_in](scope/found_in/) or [in_scope](properties/in_scope/),
`remove` is a quick way to take an object "out of play".

### Into the void

Alternatively, some authors prefer to create a "void" location where
they keep all unused objects. I *think* this is to keep game objects
away from the `nothing` object (where all the other
room objects are). Anyhow, that's also something to consider.
