---
title: text to
permalink: /strings/text-to/
categories: 
  - Strings
---

Sometimes you might want to execute some code without all of those pesky
print statements being actually shown to the player. Other times, you
might be frustrated when you have trouble adding multiple print
statements or things like `print number var` to a string array. For both
of these, `text to` is your answer!

The manual says this:

|                 |                                                              |
|-----------------|--------------------------------------------------------------|
| text to <value> | Sends text to the array table, beginning at address <value>. |
| text to 0       | Restores normal printing.                                    |

In practice, <value> is likely to be an array. Future Boy has the
following code, which we will comment on step by step:

```
string(_temp_string, "Talk to ")
text to (_temp_string + 8)
The(i)
text to 0
```

1.  That first line writes "Talk to " to the string array `_temp_string`
2.  Now we switch on "text to". The "+ 8" signifies that we're going to
    start adding to the array 8 places in (so, after "Talk to ").
3.  `i` in this case stands for a living character in the room. We'll
    pretend it returns with "the janitor".
4.  This stops the writing-to-`_temp_string`, leaving it as "Talk to the
    janitor" (in this made up example). After this point, the Future Boy
    code goes on to add the phrase to the dictionary and then adds it to
    the in-game menu. You may have other uses.

So, that is one way it can be used. Let's try another example!

### Another example!

When one uses the `PrintStatusLine` routine provided by `hubolib.h` with
STATUSTYPE 1, the score and move counter is printed exactly 65 places
across on any display larger than 80 columns. This will look great on
some displays but it'll put the counter near the center of the screen
for some people. Wouldn't we rather put it always in the upper right
corner of our screen?

We can use `display.screenwidth` to figure out the width of the screen,
but as our score and turn counter numbers go up in digits, we want to
keep the status line as consistent as possible. `text to` to the rescue!

    ! this routine won't work if you have #set NO_STRING_ARRAYS in your code.
    ! Of course, if you have turned off string arrays, what are you doing looking at
    ! "text to?"

    replace PrintStatusline
    {
        if display.linelength < 80
            display.statusline_height = 2
        else
            display.statusline_height = 1

        Font(BOLD_OFF | ITALIC_OFF | UNDERLINE_OFF | PROP_OFF)
        window display.statusline_height
        {
            color SL_TEXTCOLOR, SL_BGCOLOR
            cls
            locate 1, 1
            if not location
                print "_";
            elseif not light_source
                print "In the dark";
            else
            {
                if FORMAT & DESCFORM_F:  print "_";
                print capital location.name;
            }

    ! (The part we're changing)
    !           print to 65; ! is 65 characters good for every window size? No!

    ! Instead, let's begin by writing the entire 'SCORE / MOVES' to array _temp_string
    ! (_temp_string is an array declared by the library)

                    text to _temp_string
            if STATUSTYPE = 1
                print number score; " / "; number counter;
            elseif STATUSTYPE = 2
                print HoursMinutes(counter);
                text to 0
    ! Ok, we've closed off the string array

    ! Now, if the screen is wide enough, let's move to the end of the screen MINUS the length of the _temp_string array
    ! plus two extra spaces for good measure (so there's a little space to the right on the status bar)
            if display.statusline_height = 1
                print to (display.screenwidth - (StringLength(_temp_string) + 2));
            else
            {
                locate 1, 2
                if FORMAT & DESCFORM_F:  print "_";
            }

     ! Now let's print it!
            if STATUSTYPE = 1,2
                         StringPrint(_temp_string)
        }
        color TEXTCOLOR, BGCOLOR
        Font(DEFAULT_FONT)
    }

There we go! We're all `text to` pros now!
