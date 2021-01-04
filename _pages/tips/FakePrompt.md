---
title: Fake Prompt
permalink: /tips/fakeprompt/
categories: 
  - Tips
---

This page isn't about a "fake prompt" along the lines of
[input](/input-output/input/)/[GetInput](/input-output/getinput/). This page is
about using a looping routine to present a flashing cursor where the
player can enter text. The benefit of this method is that whatever the
player enters can be entered into a
[string array](/strings/string-arrays/) and is not subjected to the rules of a
normal prompt (where one has to train the player to use quotation marks
to be able to deal with unexpected words). On the downside, it relies
heavily on locate, so to work properly, it needs to be used in a window
written entirely in fixed-width fonts.

It requires the inclusion of [system.h](/library/system.h/) and will
not work with [glk](/definitions/glk/) or simple interpreters.

## The code

    routine FakePrompt(array_to_fill)
    {

        local a, key, letters,c,r,f
        c = display.cursor_column
        r = display.cursor_row
        array array_to_fill[0] = 0
        for (f = 0;f< array array_to_fill[] ; f++ )
            {
            array array_to_fill[f] = 0
            }

        while not key
            {
                locate c, r
                a++
                key = system(READ_KEY)
                if key = ENTER_KEY
                    {
                    Asteriskcheck(a,c,r)
                    break
                    }
                elseif key = 8 or key = 516 ! should be backspace
                    {
                    if (letters and display.cursor_column = 1)
                        {
                        Asteriskcheck(a,c,r)
                        c = display.linelength !- 1
                        locate c, --r
                        print " ";
                        array array_to_fill[--letters] = 0
                        locate --c
                        }
                    elseif (letters)
                        {
                        print " ";
                        array array_to_fill[--letters] = 0
                        locate (c - 1)
                        print " ";
                        locate --c
                        }
                    }
                elseif key > 31 and key < 127
                    {
                    if ((display.cursor_column + 1) < display.linelength)
                        {
                        array array_to_fill[letters++] = key
                        printchar key
                        c++
                        if (a>50)
                            print "*";
                        locate c
                        }
                    elseif ((display.cursor_row ) < display.windowlines)
                        {
                        Asteriskcheck(a,c,r)
                        c = 2
                        r++
                        locate c,r
                        array array_to_fill[letters++] = key
                        printchar key
                        c++
                        if (a>50)
                            print "*";
                        locate c,r
                        }
                    }
                    if a=50
                        {
                        print "*";
                        }
                    elseif a = 100
                        {
                        Asteriskcheck(a,c,r)
                        a = 0
                        }
                    system_status = 0
                    key = 0
                    system(PAUSE_100TH_SECOND)
            }
    }

    routine Asteriskcheck(a_position,cursor,row)
    {
        if (a_position>50)
            {
            print " ";
            locate (cursor)
            return true
            }
    }
