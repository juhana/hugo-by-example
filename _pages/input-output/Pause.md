---
title: Pause
permalink: /input-output/pause/
categories: 
  - Input-Output
---

`pause` makes the game wait for a keypress (or mouse click). It then stores the ASCII key or MOUSE_CLICK value in `word[0]`.

### Additional Notes

During a `pause` is the only time the interpreter detects the
"coordinates" of a mouse click. Otherwise, in most ports, it'll bring up
a [context menu](Addcontext).

By itself, the `pause` statement provides no text to tell the player
that the game is paused, so be sure to bundle it with a **print "PRESS A
KEY TO CONTINUE"** statement or something (some games will have a
"DoPause" routine or something similar to do this).
