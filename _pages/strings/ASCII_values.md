---
title: ASCII values
permalink: /strings/ascii-values/
categories: 
  - Strings
---

Every character in a printed string ("B","p","ñ", etc.) has its own
number called an "ASCII value."

![ASCII table](/assets/images/Asciitable.png)

In Hugo, if we want to alphabetize some strings or change the case of
something or even ROT13 something, we would do it by going through the
string, character by character, changing or noting the ASCII values as
necessary.

## Alphabetization

The [hugolib.h](/library/hugolib.h/) routine
[StringCompare](/strings/stringcompare/) compares each digit of two
strings. If the first digit of the first word is lexically lower,
`StringCompare` would return **-1** at this point. Looking at the chart,
we can see that it means that word would be alphabetized first.
Conversely, if that digit was lexically higher, we'd know that the
second word would come first, alphabetically (and `StringCompare` would
return **1**). If both of those digits are equal, we know that it is the
same letter. `StringCompare` then goes on to compare the second
character of both strings (and so on). If it gets to the end of both
strings without finding a difference, `StringCompare` returns **0** and
we know the strings are identical.

## Uppercase/lowercase modification

Here is a bit of code from the make-the-string-lowercase routine on the
[String Manipulation](/strings/string-manipulation/) page:

    if array stringarray[i] >= 'A' and array stringarray[i] <= 'Z'
        array stringarray[i] = array stringarray[i] + ('a'-'A')

That code basically says, "if this letter has a value between 65 and 90
(the uppercase range), make it equal the same number plus 32 (the
difference between "a" (97) and "A" (65)). That should be the lowercase
version of that letter."

In any case, knowing about ASCII values (and having a chart to reference
like the one above) will make string-modification routines a lot easier
to read (and write!).
