---
title: system
permalink: /guts/system/
categories: 
  - Hugo Guts
---

`system` is a function built-in to the
[Hugo engine](interpreters/he/) that calls "low-level system functions."
While it's certainly possible to just call the system functions by their
(built-in) number, including
["system.h"](library/system.h/) will define several
[constants](basics/constants/) which act as a key. These functions
include:

| Value | Constant Name (as defined by "system.h") | What It Does |
| --- | --- | --- |
| 11 | READ_KEY | Reads keypress (doesn't pause game) |
| 21 | NORMALIZE_RANDOM | Make random numbers predictable (used by HugoFix) |
| 22 | INIT_RANDOM | Restore “random” random values(used by HugoFix) |
| 31 | PAUSE_SECOND | Pause for one second |
| 32 | PAUSE_100TH_SECOND | Pause one hundredth of a second (used by "abuses" like Hugo Tetris) |
| 41 | GAME_RESET | Returns true after restore or undo (oddly, it doesn't work for restarts) |
| 51 | SYSTEM_TIME | Stores system time in parse$ |
| 61 | MINIMAL_INTERFACE | Returns true for minimal ports |
