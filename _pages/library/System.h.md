---
title: system.h
permalink: /library/system.h/
categories: 
  - Hugo Library
---

This header file defines some constants that are used with the
`system()` routine. It offers low-level access to the Hugo system.

Syntax for using the system routine is `system(<function>)`

| Function     | Description                           |
|--------------|---------------------------------------|
| `READ_KEY`     | Reads a single keypress (useful if you want to create a "press any key to continue" prompt) |
| `NORMALIZE_RANDOM` | Make random values predictable. Use this if you are testing your game.        |
| `INIT_RANDOM`    | Restore the randomness of the random number generator.              |
| `PAUSE_SECOND`   | Pause for one second                        |
| `PAUSE_100TH_SECOND` | Pauses for 1/100th of a second.                     |
| `GAME_RESET`   | Returns **true** if the game after a RESTORE or UNDO command.           |
| `SYSTEM_TIME`    | Returns the current time on the system the game is being played on.         |
| `MINIMAL_INTERFACE`  | Returns **true** for minimal ports of the game engine.              |

## Time-keeping

`system.h` also has some extra time-related stuff, including:

- a [string array](string_arrays) called "_time_string"
  that can be used to store time-related strings (up to 19
  characters).
- some enumerated constants and a routine called GetSystemTimeValue,
  which writes only the specific time metric (the second, minute,
  hour, day, month, year) to _time_string.

For more time-related routines, see [Time.h](Time.h)
