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

| Variable name | Used for |
| --- | --- |
| [object](globals/object) | Direct object of a verb action |
| [xobject](globals/xobject) | Indirect object |
| [self](globals/self) | Self-referential object |
| [words](globals/words) | Total number of words in word array |
| [player](globals/player) | The player object |
| [actor](globals/actor) | Player, or a char. (for scripts) |
| [location](globals/location) | Location of the player object |
| [verbroutine](globals/verbroutine) | Current verb routine |
| [endflag](globals/endflag) | If non-false, run EndGame |
| [prompt](globals/prompt) | The character(s) used for the prompt (to let the player know when it's time to type their next command next command to the game.) |
| objects | Total number of objects |
| [system_status](globals/system_status) | After certain operations |

The [Hugo Library](library/) also defines several global
variables, including:

| Variable name | Used for |
| --- | --- |
| [STATUSTYPE](globals/statustype) | The type of information used in the status bar 0 - no status 1 - score/turns 2 - time of day |
| [TEXTCOLOR](globals/textcolor) | The default color of the text that is printed for interpreters that support it |
| [player_person](globals/player_person) | 1=first, 2=second, 3=third |
| [MAX_SCORE](globals/max_score) | Total possible score in game |
| [FORMAT](globals/format) | Contains bitmap of format masks |
| [DEFAULT_FONT](globals/default_font) | 0=monospaced normal text |
| [UNDO_OFF](globals/undo_off) | Overrides undo when true |
| [counter](globals/counter) | Elapsed turns (or time, as desired) |
| [score](globals/score) | Accumulated score |
| [verbosity](globals/verbosity) | For room descriptions 0 - BRIEF 1 - SUPERBRIEF 2 - VERBOSE |
| [speaking](globals/speaking) | Set to whatever character the player is currently speaking to |
| [old_location](globals/old_location) | The previous location |
| [obstacle](globals/obstacle) | if set to an object, that object prevents the player from leaving the room |
| [light_source](globals/light_source) | Current object providing light (can be the location); set by FindLight |
| [event_flag](globals/event_flag) | event_flag value determines whether actions like waiting should be interrupted |
| [need_newline](globals/need_newline) | true when newline should be printed |

See Also: [local](basics/locals/)