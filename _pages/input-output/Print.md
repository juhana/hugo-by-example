---
title: Print
permalink: /input-output/print/
categories: 
  - Input-Output
  - Basics
---

There are two ways to print text out to the screen in a Hugo program.
The first way is by using the `print` statement. the other way is to
print from the text bank, from which -- if memory is in short supply --
sections are loaded from the disk only when they are needed by the
program.

### print routine

The basic format of the `print` statement is:

    print "<string>"

Where <string> is and text you'd like to print.

The backslash character ("\\") is handled specially. It changes how the
following character is treated.

| Code | Output | Sample |
|------|--------|--------|
| `\"`   | Inserts a quotation mark (needed because the " character is used to delimit the string's text) | print "Robert says, \"Hello, Bob!\""<br>outputs: *Robert says, "Hello, Bob!"* |
| `\`   | Inserts a literal backslash character. | `print "Apple\\Orange\\Banana"<br>outputs: *Apple\Orange\Banana* |
| `_` | Inserts a forced space, overriding the left-justification for the rest of the string. | `print "This string is left justified."`<br>`print "_  This string is not left justified!"`<br>Outputs:<br>*This string is left justified.*<br>*This string is not left justified!* |
| `\n` | Inserts a forced newline character. | `print "One\nTwo\nThree"`<br>Outputs:<br>`One`<br>`Two`<br>`Three` |

The `print` statement will automatically output a newline at the end of
the string unless you end the statement with a semicolon.

```
print "This is on one line."
print "This is on the next line below."
print "\n"
print "This will print on
       one line.";
print "And this will be on the same line."
```

>This is on one line.  
>This is on the next line below.
>
>This will print on one line.And this will be on the same line.

Please notice that the print statements did not insert a space between
the two sentences that are on the same line. This is because there was
no space in either of the strings themselves. Also, you'll notice that
the print statement on lines 4 and 5 of the source sample is split over
two lines, but still just prints one one line. (You need to use the `\n`
to force the print statement to start a new line.

------------------------------------------------------------------------

The print statement can also be used to print out
[variables](basics/variables/) or [constants](basics/constants/)
or data types.

```
age = 100

print "The "; number age; " year old box is blue."
print "The "; object.name; " is closed."
```

>The 100 year old box is blue.  
>The coffee-can is closed.
>&gt;_

In line 1, we set the [variable](basics/variables/) *age* to the
value of 100.
In line 3, we print out some text and the *age* variable, specifying
that we want to print the number value instead of the dictionary
definition of *age*.
In line 4, we print out some text and the value pointed to by
*object.name* (in this case, the object.name is **coffee-can**) ( see
[objects](basics/objects/) for more information. )

### Printing from the text bank

If there is a large amount of text to be printed, such as an
introduction to the game, or a long room description, it is generally
better to print from the text bank, as it is not necessarily pulled into
memory at the start of the game. The only drawback to this method is
that the text is essentially static, you cannot include data types like
in the `print`. You can include the backslash codes though.

```
"This is a sample of the best possible introduction to a game ever created.
 No description lacks detail. It engages all the senses and makes you feel like
 you're really there.

 It goes on and on for a bit and gives good clues on what you need to do to
 get started. It is also quite motivational and makes you want to finish the
 game"

"The "; object.name; " sits here, ignoring all your scans."
```

Lines 1 through 7 would print out as you'd expect. Line 9 would cause an
error and the game won't be compiled. You'd have to replace line 9 with
a `print` statement for it to work.
