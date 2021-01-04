---
title: restart
permalink: /guts/restart/
categories: 
  - Hugo Guts
---

`restart` is a built-in function for restarting the instance of the
game. All [globals](globals) and things are reset, with the
notable exception of the [word array](word_array). Most
commonly, it is used by the verb routine
[DoRestart](DoRestart).

### How to call

`restart` returns a [true](true) or [false](false)
value based on its success, so it is called in the following manner:

    x = restart ! the x variable gets set to 1 or 0
    ! or
    if not restart
         "(message to be printed if restart doesn't work)"

The conditional "if not restart" itself executes `restart`. If it works,
the game starts over right there. If it doesn't, we print some kind of
error message. This is how `DoRestart` does it.
