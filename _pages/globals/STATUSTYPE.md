---
title: STATUSTYPE
permalink: /globals/statustype/
categories: 
  - Global Variables
---

The value of the `STATUSTYPE` [global variable](basics/global/) determines what is
printed in the status line (the area above the main window) besides the room location.

| STATUSTYPE value | behavior                                                                                 |
|------------------|------------------------------------------------------------------------------------------|
| 0                | Only the location name is printed (perfect for all you hipsters making *artistic* games) |
| 1                | `<score> / <moves>` in the corner (the classic status line)                              |
| 2                | time display in the corner (see below)                                                   |

### time display

When `STATUSTYPE` is 2, the game counter means *minutes since midnight*
(0 = 12:00 am, 300 = 5:00 am, 900 = 3:00 pm, etc.).
