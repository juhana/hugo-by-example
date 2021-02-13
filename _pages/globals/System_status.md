---
title: system_status
permalink: /globals/system_status/
categories: 
  - Global Variables
---

`system_status` is a [compiler](basics/compiler/)-defined
[global variable](basics/global/). It exists entirely to hold values
returned from [system](guts/system/) or
[resource](basics/resources/) calls. If a system function is not
available on the current interpreter being used, the `system` call will
set `system_status` as -1. If there is no problem, `system_status` is
set to 0. Some uses:

1.  In a game with graphics, if the picture doesn't work, you could
    print some placeholder text like "\[This is supposed to be a picture
    of a turtle, but this interpreter doesn't support graphics\]"
2.  Two of Mike Snyder's games, Distress and Tales of the Traveling
    Swordsman, call `system(PAUSE_100TH_SECOND)` as a
    [glk](definitions/glk/) check

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

*(Glk.h, on the other hand, checks "glk-ness" by checking display.windowlines.)*

## system_status values

Besides 0 and -1, `system_status` can be set to several other values,
depending. Here is the full range (keep in mind that many of these are
used for resource files):

| Value | Constant Name (as defined by "system.h" or "resources.h") | Meaning |
| --- | --- | --- |
| 0 | STAT_NOERROR | System or resource call worked |
| -1 | STAT_UNAVAILABLE | Function not available on current interpreter |
| 101 | STAT_NOFILE | File wasn't found |
| 102 | STAT_NORESOURCE | Resource wasn't found |
| 103 | STAT_LOADERROR | File found but did not load properly |
