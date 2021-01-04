---
title: Display Object
permalink: /guts/display-object/
categories: 
  - Hugo Guts
---

The display object is the game author's way of "peeking" at the player's
interpreter window. It maps out the screen to a grid of characters.
Having this measurement allows the author to center text and lay out
[windows](/input-output/window/) (or really do anything that requires
specific screen placement). Since the grid *is* character based, these
numbers are affected by the font size the player is using, whether it's
a proportional or fixed-width font, etc. Ideally, an author should be
aware of these things.

You can check various aspects of the display object (and sometimes
change them) by using display object properties. The default properties
are named in `hugolib.h` using the
[enumerate](/basics/constants/) command:

    enumerate start = 1, step 1
    {
        screenwidth, screenheight,      ! built-in display object read-only
        linelength, windowlines,        ! properties
        cursor_column, cursor_row,
        hasgraphics, title_caption,
        hasvideo, needs_repaint,
        pointer_x, pointer_y
    }

    property statusline_height alias n_to   ! library-specific display object
                        ! properties

    object display
    {
        statusline_height 1
    }

`title_caption` and `needs_repaint`, listed above in the "read-only"
section, can actually be changed by the program, as can
`statusline_height`.

In fact, let's talk about each property in greater detail.

| Property Name          | Description                                                                                                               |
|------------------------|---------------------------------------------------------------------------------------------------------------------------|
| **screenwidth**        | width of the display, in characters                                                                                       |
| **screenheight**       | height of the display, in characters (see below)                                                                          |
| **linelength**         | width of the current text window                                                                                          |
| **windowlines**        | height of the current text window (see below)                                                                             |
| **cursor_column**     | horizontal position of the cursor in the current text window                                                              |
| **cursor_row**        | vertical position of the cursor in the current text window                                                                |
| **hasgraphics**        | returns true if graphic display is available                                                                              |
| **hasvideo**           | returns true if video playback is available                                                                               |
| **pointer_x**         | horizontal mouse position (in characters)                                                                                 |
| **pointer_y**         | vertical mouse position (in characters)                                                                                   |
| **title_caption**     | sets the window title for the game (where supported)                                                                      |
| **needs_repaint**     | set to true when the GUI display changes (such as when window size is changed); may then be reset to false by the program |
| **statusline_height** | of the last-printed status line                                                                                           |

**Some random observations-**

-   In a normal game with just two windows (the main window and the
    status line window), the sum of the main window's
    `display.windowlines` property and the `display.statusline_height`
    property will usually *but not always* equal `display.screenheight`.
    Doing things like changing the size of the interpreter window can
    confuse these values, so as an author, be aware that the sum is not
    a hard-and-fast rule.
-   Glk-based interpreters such as Gargoyle cannot properly gauge the
    number of lines in the main window (it'll detect something like
    30,000 lines). This breaks functions like
    [locate](/input-output/locate/) or the usage of `display.windowlines` in
    the main window.
-   Since Hugo won't do anything with a mouse click during a normal
    player input except do default interpreter behavior (like 
    [bringing up on a context menu](/guts/addcontext/), `display.pointer_x`
    and `display.pointer_y` are presumably only useful in conjunction
    with [pause](/input-output/pause/) (and the MOUSE_CLICK
    [constant](/basics/constants/)).
-   The writable properties, such as `title_caption` and
    `statusline_height` can be changed repeatedly throughout the game.
    In the case of `statusline_height`, going from a larger status line
    to a smaller one may require a strategically-placed
    [cls](/input-output/cls/) (clear screen) or "[window](/input-output/window/)
    0" to get rid of old status line "residue."
-   As the display object is the first object defined in
    [hugolib.h](/library/hugolib.h/), it has a value of 1.

## Display Properties in Action

### Centering Text

Here is a simplified version of [hugolib.h's](/library/hugolib.h/)
`CenterTitle` routine, which uses `display.linelength` to determine the
middle of the screen:

    routine CenterTitle(a)  ! "a" is some dictionary entry
    {
        local l
        Font(PROP_OFF)  ! Fixed width fonts will give you accurate text placement
        l = string(_temp_string, a)  ! we write the dictionary entry to a string,
                                         ! saving the length as "l"
        window 0                        ! remove previous window
        window 1    ! creates a 1 line high window at the top of the screen
        {
            cls
            locate (display.linelength/2 - l/2), 1
      ! The previous line moves the cursor to half of the screen size minus half of the word or phrase
      ! that we are writing. That way, when we print out the word or phrase, it'll be equally distributed
      ! to both sides.

            print a;
        }
        color TEXTCOLOR, BGCOLOR
        FONT(DEFAULT_FONT)
        cls
        locate 1, 1
    }

### Needs Repainting

`needs_repaint` will not revert to **false** until the author explicitly
sets it. Let's say you have a game with fancy graphics and windows, but
the windows aren't redrawn every turn. This makes your game vulnerable
for screen corruption every time the player resizes the window. To get
around this, you could have code like this:

    player_character you "you"
    {
    before
       {
       actor PreParse
          {
             if display.needs_repaint
                {
                DrawWindows() ! our fictional routine that redraws all windows
                display.needs_repaint = false ! set needs_repaint back to false so we are ready for the next change
                }
             else
                return false
          }
       }
    }

</div>
