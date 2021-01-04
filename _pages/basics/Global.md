---
title: Global
permalink: /basics/global/
categories: 
  - Basics
---

The **global** command defines a public [variable](basics/variables/)
which is available anywhere in the program at any time. All references
to a global refer to the same variable and must have a unique name,
different from any other global variable,
[attribute](attributes/), [property](properties/), or
[object](basics/objects/). It is a
[declaration](declarations/) and is not executable
[code](definitions/code/).

        ! Global variable to store the number of chocolate cake slices.
        global  cake_slice_count

        global  table, chair
        global  car = Ford   ! car variable is Ford object
        global  batteries = 5        ! number started with
        global  current_color = "Viridian"

        ! Global variable to store the number of chocolate cake slices,
        ! with a starting value defined right at the start.

        global cake_slice_count = 10

Some reserved global variables are defined by the compiler:

<table>
<thead>
<tr class="header">
<th><p>Variable name</p></th>
<th><p>Used for</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><b><a href="object_(Global)">object</a></b></p></td>
<td><p>Direct object of a verb action</p></td>
</tr>
<tr class="even">
<td><p><b><a href="xobject">xobject</a></b></p></td>
<td><p>Indirect object</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="self">self</a></b></p></td>
<td><p>Self-referential object</p></td>
</tr>
<tr class="even">
<td><p><b><a href="words">words</a></b></p></td>
<td><p>Total number of words in word array</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="player">player</a></b></p></td>
<td><p>The player object</p></td>
</tr>
<tr class="even">
<td><p><b><a href="actor">actor</a></b></p></td>
<td><p>Player, or a char. (for scripts)</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="Location">location</a></b></p></td>
<td><p>Location of the player object</p></td>
</tr>
<tr class="even">
<td><p><b><a href="Verbroutine">verbroutine</a></b></p></td>
<td><p>Current verb routine</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="Endflag">endflag</a></b></p></td>
<td><p>If non-false, run <a href="EndGame">EndGame</a></p></td>
</tr>
<tr class="even">
<td><p><b><a href="prompt">prompt</a></b></p></td>
<td><p>The character(s) used for the prompt (to let the<br />
player know when it's time to type their next command<br />
next command to the game.)</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="objects">objects</a></b></p></td>
<td><p>Total number of objects</p></td>
</tr>
<tr class="even">
<td><p><b><a href="system_status">system_status</a></b></p></td>
<td><p>After certain operations</p></td>
</tr>
</tbody>
</table>

The [Hugo Library](library/) also defines several global
variables, including:

<table>
<thead>
<tr class="header">
<th><p>Variable name</p></th>
<th><p>Used for</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><b><a href="STATUSTYPE">STATUSTYPE</a></b></p></td>
<td><p>The type of information used in the status bar<br />
 0 - no status<br />
 1 - score/turns<br />
 2 - time of day</p></td>
</tr>
<tr class="even">
<td><p><b><a href="TEXTCOLOR">TEXTCOLOR</a></b></p></td>
<td><p>The default color of the text that is printed<br />
<i>for interpreters that support it</i></p></td>
</tr>
<tr class="odd">
<td><p><b><a href="player_person">player_person</a></b></p></td>
<td><p>1=first, 2=second, 3=third</p></td>
</tr>
<tr class="even">
<td><p><b><a href="Scoring">MAX_SCORE</a></b></p></td>
<td><p>Total possible score in game</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="FORMAT">FORMAT</a></b></p></td>
<td><p>Contains bitmap of format masks</p></td>
</tr>
<tr class="even">
<td><p><b><a href="DEFAULT_FONT">DEFAULT_FONT</a></b></p></td>
<td><p>0=monospaced normal text</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="UNDO_OFF">UNDO_OFF</a></b></p></td>
<td><p>Overrides undo when true</p></td>
</tr>
<tr class="even">
<td><p><b><a href="counter">counter</a></b></p></td>
<td><p>Elapsed turns (or time, as desired)</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="score">score</a></b></p></td>
<td><p>Accumulated score</p></td>
</tr>
<tr class="even">
<td><p><b><a href="verbosity">verbosity</a></b></p></td>
<td><p>For room descriptions<br />
 0 - BRIEF<br />
 1 - SUPERBRIEF<br />
 2 - VERBOSE</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="speaking">speaking</a></b></p></td>
<td><p>Set to whatever character the player is currently speaking to</p></td>
</tr>
<tr class="even">
<td><p><b><a href="old_location">old_location</a></b></p></td>
<td><p>The previous location</p></td>
</tr>
<tr class="odd">
<td><p><b><a href="obstacle">obstacle</a></b></p></td>
<td><p>if set to an object, that object prevents the player from leaving the room</p></td>
</tr>
<tr class="even">
<td><p><b><a href="light_source">light_source</a></b></p></td>
<td><p>Current object providing light (can be the location); set by <a href="FindLight">FindLight</a></p></td>
</tr>
<tr class="odd">
<td><p><b><a href="Event_flag">event_flag</a></b></p></td>
<td><p><code>event_flag</code> value determines whether actions like waiting should be interrupted</p></td>
</tr>
<tr class="even">
<td><p><b><a href="need_newline">need_newline</a></b></p></td>
<td><p>true when newline should be printed</p></td>
</tr>
</tbody>
</table>

See Also: [local](basics/locals/)