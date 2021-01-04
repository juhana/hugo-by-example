---
title: quit
permalink: /guts/quit/
categories: 
  - Hugo Guts
---

`quit` is the command that exits out of the 
[game loop](loops/game-loop/) completely. See how it is called in the
DoQuit routine:

    routine DoQuit
    {
        PrintScore
        VMessage(&DoQuit)                        ! "Are you sure?"
        GetInput
        if YesorNo = true
            quit
    }
