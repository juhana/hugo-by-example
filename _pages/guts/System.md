---
title: system
permalink: /guts/system/
categories: 
  - Hugo Guts
---

`system` is a function built-in to the [Hugo
engine](Hugo_Engine) that calls "low-level system functions."
While it's certainly possible to just call the system functions by their
(built-in) number, [including](include)
["system.h"](system.h) will define several
[constants](constants) which act as a key. These functions
include:

<table>
<thead>
<tr class="header">
<th><p>Value</p></th>
<th><p>Constant Name<br />
(as defined by "system.h")</p></th>
<th><p>What It Does</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>11</p></td>
<td><p>READ_KEY</p></td>
<td><p>Reads keypress (doesn't pause game)</p></td>
</tr>
<tr class="even">
<td><p>21</p></td>
<td><p>NORMALIZE_RANDOM</p></td>
<td><p>Make random numbers predictable (used by <a href="HugoFix">HugoFix</a>)</p></td>
</tr>
<tr class="odd">
<td><p>22</p></td>
<td><p>INIT_RANDOM</p></td>
<td><p>Restore “random” random values(used by <a href="HugoFix">HugoFix</a>)</p></td>
</tr>
<tr class="even">
<td><p>31</p></td>
<td><p>PAUSE_SECOND</p></td>
<td><p>Pause for one second</p></td>
</tr>
<tr class="odd">
<td><p>32</p></td>
<td><p>PAUSE_100TH_SECOND</p></td>
<td><p>Pause one hundredth of a second (used by "abuses" like Hugo Tetris)</p></td>
</tr>
<tr class="even">
<td><p>41</p></td>
<td><p>GAME_RESET</p></td>
<td><p>Returns true after restore or undo (oddly, it doesn't work for restarts)</p></td>
</tr>
<tr class="odd">
<td><p>51</p></td>
<td><p>SYSTEM_TIME</p></td>
<td><p>Stores system time in parse$</p></td>
</tr>
<tr class="even">
<td><p>61</p></td>
<td><p>MINIMAL_INTERFACE</p></td>
<td><p>Returns true for minimal ports</p></td>
</tr>
</tbody>
</table>
