---
title: endflag
permalink: /globals/endflag/
categories: 
  - Global Variables
---

`endflag` is a compiler-defined [global variable](basics/global/). 
If set to anything besides 0, a game *instantly* stops whatever it was doing 
and ends the game, calling the routine [EndGame](routines/endgame/).

| event_flag value | behavior                                                                                                                                                                    |
|-------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0                 | Nothing (this is what endflag equals by default)                                                                                                                            |
| 1                 | [PrintEndGame](routines/printendgame/) prints "You have won!" message                                                                                                      |
| 2                 | [PrintEndGame](routines/printendgame/) prints "You have lost!" message                                                                                                     |
| 3+                | Normally not supported (the game will still end but nothing will be printed). If [PrintEndGame](routines/printendgame/) is replaced, you can reserve additional responses. |

align="top"\|*effects of different endflag values:*
