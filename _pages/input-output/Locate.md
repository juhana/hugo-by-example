---
title: Locate
permalink: /input-output/locate/
categories: 
  - Input-Output
---


| calling form               | description                                              |
|----------------------------|----------------------------------------------------------|
| `locate `<column>`, `<row> | Sets the cursor position within the current text window. |

`locate` moves the cursor to the coordinates (in character spacing)
provided.

## Uses

This is useful for drawing floating boxes like those in
[Boxdraw.h](contributions/boxdraw.h/) or drawing maps like in the Automap
library contribution. It can even be used within
menus to move the cursor to a corner where it is not
a distraction.

## Keep In Mind

Be aware of where your cursor is after you're done with it. Sometimes
you'll need to move it back to where it was. Also, in
[glk](definitions/glk/) clients like Gargoyle, `locate` only works in the
status window. Trying to do it in the main window will be trouble.

## Example Code

Let's pretend that you are the sort of chap who is slightly bothered
when he opens up a Hugo game, just to see the game text start scrolling
from the bottom of the screen. `locate` can fix that! First, you'd need
to \#include the Glk.h library contribution, and
then you can add this to the `init` routine:


    ! first, we'll follow Glk.h's advice and run 'glkcheck'
          glkcheck

    ! now, if the game is being played on an official, non-glk interpreter, we'll move the cursor up
          if not glk
                  locate 1 , 3
    ! (staying in the first column but moving three rows down from top so the game text starts up there)

In [glk](definitions/glk/) clients, text is drawn from the top anyway, so
now, all of our games look GREAT!
