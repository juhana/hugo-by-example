---
title: window.h
permalink: /library/window.h/
categories: 
  - Hugo Library
---

The **window.h** header file defines a basic window
[class](Object_Classes) to make using
[windows](window) in your game a little bit easier.

Using the library, you need to **\#include "window.h"** after you've
included **hugolib.h**

After including the file, you can define a window class thusly:

    window_class sample_window "sample"
    {
      win_left     1  ! leftmost column
      win_top      1  ! topmost row
      win_right    20 !rightmost column
      win_bottom   5  ! bottommost row

      win_textcolor  WHITE    ! text color for any output
      win_backcolor  BLACK    ! background color
      win_titlecolor LIGHT_RED !text color for the title
      win_titleback  YELLOW   ! title background color
    }

The window class also defines the following routines

| Routine    | What it does         |
|------------|----------------------|
| win_init  | Initializes the window (sets its size, text-colors, title, etc, based on the class definition |
| win_clear | Clears the window (based on **win_textcolor** and **win_backcolor** |
| win_end   | Deactivate the window (returns output to the "main" window) and returns the text and background colors to the previously defined colors. |

See the article [window](window) for sample code that shows the class in use.
