---
title: Boxdraw.h
permalink: /library-contributions/boxdraw.h/
categories: 
  - Library Contributions
---

`Boxdraw.h` is a library contribution for drawing colored text boxes
written by Cardinal Teulbachs. Considering that games that use this will
not play properly on glk interpreters such as Gargoyle (they do not like
when the [locate](/input-output/locate/) command is used in the main text
window), people are recommended to take a look at
*Boxdrawglk.h*. This page mainly exists so people
can see the original documentation.

### The original code

    !\===========================================================================
    NOTE: This is version 5, dated 970818. It supercedes the previous version,
    version 4. This version incorporates the following changes:

    1. The display variables have been changed to conform with Hugo v2.4
       standards. Specifically, the variable "linelength" is now the property
       "display.linelength" and the variable pagelength is the property
       "display.windowlines".

    NOTE: In what follows, the word "epigram" refers mainly not to a short,
          pithy quotation, but rather to the onscreen box such short, pithy
          quotations are typically displayed in in computer text adventure
          games.


                          THE TWO ROUTINES AND WHAT THEY DO:

    Box(epiflag)

    Box() is a box-drawing routine for Hugo v2.3. It takes one argument,
    WHICH THE USER SHOULD NEVER SUPPLY. IOW, for all intents and purposes
    as regards the user, Box() takes no arguments.

    When Box() is called, an array of strings (box_array[]) is read and drawn
    inside a colored box on the screen. The vertical position of the box
    on the screen is determined by the position of the cursor at the time the
    routine is called. IOW, the box begins drawing at the cursor's current
    (vertical) position. All boxes, however, are centered horizontally, and
    this is a behavior which cannot be overridden.

    The color of the box and its text are determined by the two globals
    BOX_TEXTCOLOR and BOX_BGCOLOR, which must be set up prior to the draw. If
    these values are not set, the box will be drawn in reverse-video colors.

    There is no provision for variable margins. All boxes are drawn "tight"
    around the enclosed text. That is, every box will be number-of-lines-
    plus-two high by length-of-longest-line-plus-four wide. Also, there is
    no way to override the text-centering. Every line of text in a box will
    be center-justified. If a user desires right- or left-justified text,
    however, it can still be accomplished by supplying leading or trailing
    spaces in the text strings themselves.

    The number of lines of text a box can accommodate is controlled by the
    constant MAX_BOX_LINES. MAX_BOX_LINES is set to 10 by default.


    Epigram(pauseflag)

    Epigram() is a routine for Hugo v2.3 that uses Box() to display epigrams
    on the screen. Epigram() takes one true-or-false argument (pauseflag). The
    purpose of the argument is this: it is desirable at different times for
    epigrams to behave in different ways. Most of the time, an epigram should
    wait for all of a current turn's text to be printed before displaying itself
    on the screen. This is the default mode, and no argument need be supplied
    in order to get this kind of behavior. However, there are times as well
    (such as during the opening sequence of a game) when the epigram should
    display immediately, pausing to allow the player to read it before
    continuing on with the next line of code. For situations like this,
    Epigram() should be called with "true".

    The only other difference between an epigram and a normal inline box is
    the vertical position on the screen at which it displays. An epigram always
    displays five rows down from the top of the screen, which means that any
    existing text at that position will be overdrawn. For this reason (and
    others as well), it is suggested that epigrams be used in moderation and
    only in ways that are not likely to interfere with the playing of a game.

    Here's how to use Box():

    First, store the strings you want boxed in box_array[]:

            box_array[0] = "This box drawn with Box()"
            box_array[1] = "by Cardinal Teulbachs (c) 1997"
            box_array[2] = " "
            box_array[3] = "All Rights, whatever those might be, Reserved"

    Then, just call Box():

            Box()

    That's all there is to it. All the contents of box_array[] will be centered
    on the screen in a colored box. (Note, however, that a null string will be
    interpreted as the end of the array, so that if a blank line is desired
    inside the box, one should use a delimited space instead, as in case
    box_array[2] above).

    To display the same text as an epigram, call Epigram():

            Epigram()
    or
            Epigram(true)

    Now the box will display in the upper center of the screen, overwriting
    whatever is beneath it. Remember that when Epigram() is called with a
    non-zero argument, the screen pauses and waits for a keypress. Otherwise it
    waits until a turn is completely finished before displaying itself.

    IMPORTANT: IN ADDITION TO THE CODE SUPPLIED BELOW, THE FOLLOWING LINES
               MUST BE ADDED TO THE END OF THE main() ROUTINE:

               if epigram_on
               { "" : Box(true) }


    Ok. That's it. Enjoy!
    This file by Cardinal Teulbachs, (c) 1997

    ===========================================================================\!
    ! Either just #include this whole file before init() in your source, or
    ! declare these values before init()

    constant MAX_BOX_LINES 10                  ! max lines allowed in a box
    global BOX_TEXTCOLOR = BGCOLOR             ! text color for boxes
    global BOX_BGCOLOR = TEXTCOLOR             ! background color for boxes
    array box_array[MAX_BOX_LINES]             ! the string array
    global EPIGRAM_ON                          ! switch for epigram display mode

    !\
       NOTE: The BOX_TEXTCOLOR and BOX_BGCOLOR globals won't work properly
             unless they are re-initialized in the init() routine. So do that.
    \!

    ! and put these routines anywhere after the above declarations.

    routine Epigram(pauseflag)
    {
      if pauseflag
      {
        Box(true)
        locate display.linelength, display.windowlines
        pause
      }
      else
        EPIGRAM_ON = true

      return true
    }

    routine Box(epiflag)   ! epiflag should never be supplied by user
    {
      local a, b, l, old_lng, lng, startpos, endpos, row = 3

      Font(PROP_OFF)

      for (a=0; a <= MAX_BOX_LINES; a++)
      {
        old_lng = lng
        if box_array[a] = 0
          break

        l = string(_temp_string, box_array[a])
        lng = higher(old_lng,l)
      }

      if lng >= (display.linelength - 4)    ! if strings too long
      {                                     ! display them using normal
        print ""                            ! left-justifying engine routine
        for (b=0; b <= MAX_BOX_LINES; b++)
        {
          if box_array[b] = 0
            break
          print box_array[b]
        }
        b = 0
        while(box_array[b] ~= 0)            ! then flush the array
        {
          box_array[b] = 0
          if b = MAX_BOX_LINES - 1
            break
          b++
        }
        return false                        ! and bail out
      }

      lng = lng + 4

      if not mod(display.linelength,2) and not mod(lng,2)   ! if screen width and string
        endpos = (display.linelength/2 + lng/2)             ! length evenly divide by 2
      else
        endpos = ((display.linelength/2 + lng/2) + 1)       ! if one or both lengths odd
      startpos = (display.linelength/2 - lng/2)

      if epiflag
        startpos += 1

      if epiflag                                    ! if this is epigram
        locate startpos, row
      else                                          ! elseif this is regular box
        print to startpos;

      color BOX_TEXTCOLOR, BOX_BGCOLOR
                                            !        Draw:
      print " ";                            ! top left corner of box

      for (b=0; b <= (lng - 3); b++)
        print " ";                          ! top of box

      print " ";                            ! top right corner of box

      if not epiflag
      { color TEXTCOLOR, BGCOLOR
        print to display.linelength                 !       End Line
      }

      for (b=0; b < a; b++)
      {
        l = string(_temp_string, box_array[b])

        if epiflag                          ! if this is epigram
          locate startpos, ++row
        else                                ! elseif this is regular box
          print to startpos;

        color BOX_TEXTCOLOR, BOX_BGCOLOR

                                            !       Draw:
        print " ";                          ! left side of box

        print to (display.linelength/2 - l/2); box_array[b];     ! the string, centered
        print to (endpos-1);

        print " ";                          ! right side of box

        if not epiflag
        { color TEXTCOLOR, BGCOLOR
          print to display.linelength               !  End Line, Repeat
        }
      }

      if epiflag                            ! if this is epigram
        locate startpos, ++row
      else                                  ! elseif this is regular box
        print to startpos;

      color BOX_TEXTCOLOR, BOX_BGCOLOR

                                            !       Draw:
      print " ";                            ! bottom left corner of box

      for (b=0; b <= (lng - 3); b++)
        print " ";                          ! bottom of box

      print " ";                            ! bottom right corner of box

      if not epiflag
      { color TEXTCOLOR, BGCOLOR
        print to display.linelength                 !       End Line
      }

      a = 0
      while(box_array[a] ~= 0)              ! flush string array
      { box_array[a] = 0
        if a = MAX_BOX_LINES - 1
          break
        a++
      }

      color TEXTCOLOR, BGCOLOR
      Font(DEFAULT_FONT)

      EPIGRAM_ON = false                    ! turn off epigram switch and

      return true                           ! go home happy and contented
    }
