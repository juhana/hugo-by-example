---
title: Grammar Matching
permalink: /definitions/grammar-matching/
categories: 
  - Definitions
---

"Grammar matching" is the part of the [game loop](game_loop)
where the game matches the [word array](word_array) against
the grammar table, determining the proper verb routine (and setting the
[object](object_(Global)) and [xobject](xobject)
global variables, if applicable) or parser error message. It comes after
the parsing stage but before the `before` routines.
