---
title: restore
permalink: /guts/restore/
categories: 
  - Hugo Guts
---

`restore` is a built-in function for prompting a saved-game-restoring
dialog. After a successful game restoration, all
[globals](globals) and things are set to the value they were
in the saved game, with the notable exception of the [word
array](word_array). Most commonly, it is used by the verb
routine [DoRestore](DoRestore).

### How to call

`restore` returns a [true](true) or [false](false)
value based on its success, so it is called in the following manner:

    x = restore ! the x variable gets set to 1 or 0
    ! or
    if not restore
         "(message to be printed if restore doesn't work)"

The conditional "if not restore" itself executes `restore`. If it works,
the game resumes from the saved game point. If it doesn't, we print some
kind of error message. This is how `DoRestore` does it.
