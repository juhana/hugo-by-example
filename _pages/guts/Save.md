---
title: save
permalink: /guts/save/
categories: 
  - Hugo Guts
---

`save` is a built-in function for pulling up a save game dialog. A
successful save saves game state information to file, which can later be
retrieved by [restore](restore). Most commonly, `save` is
used by the verb routine [DoSave](DoSave).

### How to call

`save` returns a [true](true) or [false](false)
value based on its success, so it is called in the following manner:

    x = save ! the x variable gets set to 1 or 0
    ! or
    if not save
         "(message to be printed if restore doesn't work)"

The conditional "if not save" itself executes `save`. If it works, the
game state has been successfully saved to a file. If it doesn't, we
print some kind of error message. This is how `DoSave` does it.
