---
title: event_flag
permalink: /globals/event_flag/
categories: 
  - Global Variables
---

`event_flag` is a [hugolib.h](Hugolib.h)-declared [global
variable](Variables#Global_Variables) that affects in-game
waiting. Without them, [events](Events) and
[`each_turn`](Each_turn) properties would run several times
per wait command, as `>WAIT` defaults to three turns.

| event_flag value | effect                                                     |
|-------------------|------------------------------------------------------------|
| 0 (false)         | Waiting progresses unhindered.                             |
| 1 (true)          | A "Do you want to continue waiting? (Y/N)" prompt is given |
| 2                 | The wait cycle is broken without a choice                  |

align="top"\|*set event_flag to the following:*
