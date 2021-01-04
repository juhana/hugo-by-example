---
title: Grammar Matching
permalink: /definitions/grammar-matching/
categories: 
  - Definitions
---

"Grammar matching" is the part of the [game loop](loops/game-loop/)
where the game matches the [word array](basics/word-array/) against
the grammar table, determining the proper verb routine (and setting the
[object](basics/global/) and [xobject](globals/xobject/)
global variables, if applicable) or parser error message. It comes after
the parsing stage but before the `before` routines.
