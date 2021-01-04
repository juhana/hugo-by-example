---
title: Counter
permalink: /globals/counter/
categories: 
  - Global Variables
---

`counter` is a [global variable](/basics/global/) used to store the
number of turns used in a game so far. A non-turn-counting game that has
[STATUSTYPE](/globals/statustype/) set to 0 will ignore `counter`
altogether. Games with `STATUSTYPE` set to 1 will show the current
[score](/globals/score/) and turn counter in the status line. If
`STATUSTYPE` is set to 2, the turn counter will represent "minutes since
midnight" (60 moves = 1 am). You can *further* modify this by changing
the call in [PrintStatusLine](/input-output/printstatusline/) to the
[HoursMinutes](/guts/hoursminutes/) routine from
`HoursMinutes(counter)` to `HoursMinutes(counter, true)`, which will
turn it into military time format.
