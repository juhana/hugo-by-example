---
title: system_status
permalink: /globals/system_status/
categories: 
  - Global Variables
---

`system_status` is a [compiler](Hugo_Compiler)-defined
[global variable](globals). It exists entirely to hold values
returned from [system](system) or
[resource](resources) calls. If a system function is not
available on the current interpreter being used, the `system` call will
set `system_status` as -1. If there is no problem, `system_status` is
set to 0. Some uses:

1.  In a game with graphics, if the picture doesn't work, you could
    print some placeholder text like "\[This is supposed to be a picture
    of a turtle, but this interpreter doesn't support graphics\]"
2.  Two of Mike Snyder's games, Distress and Tales of the Traveling
    Swordsman, call `system(PAUSE_100TH_SECOND)` as a
    [glk](glk) check

<!-- -->

    !----------------------------------------------------------------------------
    ! detect for whether or not this is a GLK port.
    routine is_glk_port
    {
        system(PAUSE_100TH_SECOND)
        if (system_status = 0) {
            return false
        } else {
            return true
        }
    }

*([Glk.h](Glk.h), on the other hand, checks "glk-ness" by
checking display.windowlines.)*

## system_status values

Besides 0 and -1, `system_status` can be set to several other values,
depending. Here is the full range (keep in mind that many of these are
used for resource files):

<table>
<thead>
<tr class="header">
<th><p>Value</p></th>
<th><p>Constant Name<br />
(as defined by "system.h" or "resources.h")</p></th>
<th><p>Meaning</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>0</p></td>
<td><p>STAT_NOERROR</p></td>
<td><p>System or resource call worked</p></td>
</tr>
<tr class="even">
<td><p>-1</p></td>
<td><p>STAT_UNAVAILABLE</p></td>
<td><p>Function not available on current interpreter</p></td>
</tr>
<tr class="odd">
<td><p>101</p></td>
<td><p>STAT_NOFILE</p></td>
<td><p>File wasn't found</p></td>
</tr>
<tr class="even">
<td><p>102</p></td>
<td><p>STAT_NORESOURCE</p></td>
<td><p>Resource wasn't found</p></td>
</tr>
<tr class="odd">
<td><p>103</p></td>
<td><p>STAT_LOADERROR</p></td>
<td><p>File found but did not load properly</p></td>
</tr>
</tbody>
</table>
