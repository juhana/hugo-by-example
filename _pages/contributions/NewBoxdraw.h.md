---
title: NewBoxdraw.h
permalink: /contributions/newboxdraw.h/
categories: 
  - Library Contributions
---

`NewBoxdraw.h` is an updated version of Cardinal Teulbachs'
[Boxdraw.h](contributions/boxdraw.h/). If a game is being played on a glk
client such as Gargoyle, the boxes and epigrams are drawn as just normal
blocks of text.

### Ways to call

`    Box(quotefile) - Draws the text in a box in normal scrollback`

`    TitleEpigram(quotefile) - Clears the screen, displays the quote box, waits for a pause, then clears the screen again.`

### Other notes

Besides including this extension, if not using Roodylibe, you'll want to add this to the
[main](routines/main/) routine-

            if nextepigram
               Epigram(nextepigram)

### The code itself

    !::
    ! NewBoxDraw
    !::

    !\#ifset VERSIONS
    #message "NewBoxDraw.h Version 1.0"
    #endif \!

    #ifclear _NEWBOXDRAW_H
    #set _NEWBOXDRAW_H

    property line alias misc
    global nextepigram
    attribute centered alias special
    property simplefont alias capacity

    #ifset _ROODYLIB_H
    object boxlib
    {
       type settings
       in main_instructions
       execute
       {
          if nextepigram
             Epigram(nextepigram)
       }
    }
    #endif

    class quote
    {
       line 0
       simplefont ITALIC_ON  ! note: gargoyle will only honor italic OR bold, not
                             ! both
    }

    routine Epigram(quotefile, pauseflag)
    {
       nextepigram = quotefile
       if not system(61) and parser_data[PARSER_STATUS] ~= PARSER_RESET
          return
       Box(quotefile, pauseflag)
    }

    routine TitleEpigram(quotefile)
    {
       InitScreen
       nextepigram = quotefile
       Box(quotefile, true)
       ""
       InitScreen
    }

    routine QuoteboxPosition
    {
       return 3
    }

    routine Box(quotefile, pauseflag,force_simple)
    {
       local a,i, l, lng, pos_start, pos_end, start_row, old_lng, current_pos
    #ifset _ROODYLIB_H
    #ifclear NO_ACCESSIBILITY
       if not force_simple
          force_simple = (cheap = 1)
    #endif
    #endif
       if system(61) or force_simple
       {
          a = quotefile.#line
          if quotefile.simplefont
             Font(quotefile.simplefont)
          for (i=1;i<=a ;i++ )
          {
             Indent
             if i = 1 and not nextepigram
                print "[";
             print quotefile.line #i;
             if i = a and not nextepigram
                print "]"
             else
                ""
          }
          nextepigram = 0
          if quotefile.simplefont
             Font(quotefile.simplefont * 2)
          ExtraText(quotefile)
          if pauseflag
             TopPause
          return
       }
       for (i = 1;i<= quotefile.#line ;i++ )
       {
          old_lng = l
          l = string(_temp_string, quotefile.line #i )
          lng = higher(old_lng,l)
       }
       if lng >= (display.linelength - 4)
       {
          Box(quotefile,pauseflag,true)
          return
       }
       ""
       FONT(PROP_OFF)
       if nextepigram
       {
          start_row = display.statusline_height + QuoteboxPosition
          current_pos = display.cursor_row
       }
       else
       {
          start_row = display.cursor_row
       }
       pos_start = (display.screenwidth / 2 - (lng/2) - 2)
       pos_end = pos_start + lng + 3
       for (i = 1;i<= quotefile.#line ;i++ )
       {
          locate pos_start, (start_row + i - 1)
          if i = 1
          {
             color TEXTCOLOR, TEXTCOLOR
             print "[ ";
             color BGCOLOR, TEXTCOLOR
          }
          else
             print "\_ ";
          if quotefile is centered
          {
             l = string(_temp_string, quotefile.line #i )
             if l < lng
                print to (display.linelength / 2 - (l / 2));
          }
          print quotefile.line #i;
          if i = quotefile.#line
          {
             print to (pos_end - 1);
             color TEXTCOLOR, TEXTCOLOR
             print "]"
          }
          else
          {
             local x
             for (x = (i+1);x<= quotefile.#line ;x++ )
             {
                if quotefile.line #x
                {
                   print to pos_end
                   break
                }
             }
          }
       }
       color TEXTCOLOR, BGCOLOR
       ExtraText(quotefile)
       if nextepigram
          locate 1, current_pos
       FONT(DEFAULT_FONT)
       if pauseflag
          TopPause
       nextepigram = 0
    }

    routine ExtraText(quotefile)
    {}

    #ifclear _ROODYLIB_H
    routine InitScreen
    {
       local simple_port
       color TEXTCOLOR, BGCOLOR, INPUTCOLOR
       Font(DEFAULT_FONT)
       simple_port = (not ((display.screenheight + 100) < display.windowlines) and
          system(61)) ! non-glk simple port
       if not system(61)
          window 0
       if not simple_port
          cls
       if not system(61)
          CenterTitle("",0,1,1) ! Draw an empty window
       if not system(61)
          locate 1, display.windowlines
       elseif simple_port ! non-glk simple port
          ""

       if display.needs_repaint
          display.needs_repaint = false
    }

    routine TopPause(pausetext)
    {
       Font(BOLD_OFF | ITALIC_OFF | UNDERLINE_OFF | PROP_OFF)
       if not system(61)
       {
          window display.statusline_height
          {
             cls
          }
       }
       window  1 ! display.statusline_height
       {
          local y
          y = display.linelength
          color SL_TEXTCOLOR, SL_BGCOLOR
          cls			! make sure we've drawn the entire status bar in the
                      !  proper colors
    !		locate 1,1
          text to _temp_string
          if pausetext
             print pausetext;
          else
             print "[PRESS A KEY TO CONTINUE]";
          text to 0

          local alength
          alength = StringLength(_temp_string)
          print to (display.linelength/2 - alength/2);
          StringPrint(_temp_string)
       }
       color TEXTCOLOR, BGCOLOR, INPUTCOLOR
       Font(DEFAULT_FONT)
       pause
    }
    #endif
    #endif ! _NEWBOXDRAW_H
