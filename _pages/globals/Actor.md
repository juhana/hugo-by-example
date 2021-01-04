---
title: Actor
permalink: /globals/actor/
categories: 
  - Global variables
---

`actor` is a [global variable](/basics/global/) that represents the
character performing the [current action](/globals/verbroutine/). In
the case of an average verb routine, `actor` is set to the
[player](/globals/player/) object. In the case of
[character scripts](/characters/scripts/), though, `actor` is set to the 
character in question. Checking for the `actor` global allows code that works
for several different characters.