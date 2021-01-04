---
title: Color
permalink: /input-output/color/
categories: 
  - Basics
  - Input-Output
---

The `color` command changes the color of the text and/or the background.

For example, to change the color of the text to blue, use the code
`color BLUE`. The Hugo [standard library](/library/)
defines the sixteen standard colors as:

| Value | Color   | Constant name | Sample | Value | Color         | Constant name  | Sample |
|-------|---------|---------------|--------|-------|---------------|----------------|--------|
| 0     | Black   | BLACK         |        | 8     | Dark gray     | DARK_GRAY     |        |
| 1     | Blue    | BLUE          |        | 9     | Light blue    | LIGHT_BLUE    |        |
| 2     | Green   | GREEN         |        | 10    | Light green   | LIGHT_GREEN   |        |
| 3     | Cyan    | CYAN          |        | 11    | Light cyan    | LIGHT_CYAN    |        |
| 4     | Red     | RED           |        | 12    | Light red     | LIGHT_RED     |        |
| 5     | Magenta | MAGENTA       |        | 13    | Light magenta | LIGHT_MAGENTA |        |
| 6     | Brown   | BROWN         |        | 14    | Light yellow  | YELLOW         |        |
| 7     | White   | WHITE         |        | 15    | Bright white  | BRIGHT_WHITE  |        |

These colors can appear differently on different interpreters (or not at
all). Some interpreters may also allow the user to define their own
colors. These default colors have their own values:

| Value | Constant name       | What it is                                           |
|-------|---------------------|------------------------------------------------------|
| 16    | DEF_FOREGROUND     | Foreground defined by interpreter                    |
| 17    | DEF_BACKGROUND     | Background defined by interpreter                    |
| 18    | DEF_SL_FOREGROUND | Status line foreground defined by interpreter        |
| 19    | DEF_SL_BACKGROUND | Status line foreground defined by interpreter        |
| 20    | MATCH_FOREGROUND   | Whatever the current foreground color is (assumedly) |

    global TEXTCOLOR        = DEF_FOREGROUND        ! normal text color
    global BGCOLOR          = DEF_BACKGROUND        ! normal background color
    global SL_TEXTCOLOR     = DEF_SL_FOREGROUND     ! statusline text color
    global SL_BGCOLOR       = DEF_SL_BACKGROUND     ! statusline background color
    global INPUTCOLOR       = MATCH_FOREGROUND      ! input color

As you can see, games without custom color definitions automatically set
their colors to these values. If you *do* change some colors in your
game, it is best to change all of the color
[globals](/basics/variables/). There is no way for
the game to know what the default colors are and therefore can't tell if
you have, say, BLUE on BLUE.

#### Menus

If you have menus, you may want to set the following menu color globals,
too:

    global MENU_TEXTCOLOR
    global MENU_BGCOLOR
    global MENU_SELECTCOLOR
    global MENU_SELECTBGCOLOR
