---
title: \#include
permalink: /guts/include/
categories: 
  - Hugo Guts
---

With the `#include` command, one can separate one game source into
several files. Besides being used to include [library files](/library/) and 
[library contributions](/contributions/), one can
separate their game source into location, object, or character files-
whatever helps the game seem less unwieldy.

## Checking for previously-included extensions

When used with the `#if` command, at the inclusion of one library
contribution, one can check to see if another necessary extension has
already been included. Take, for instance, the CheapGLK library
contribution, which requires "glk.h".

At the beginning of "cheapglk.h", there is this:

    #ifclear _GLK_H
    #include "glk.h"
    #endif

This assures that we will never process the body of the "cheapglk.h"
code without first processing "glk.h"
