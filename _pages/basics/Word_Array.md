---
title: Word Array
permalink: /basics/word-array/
categories: 
  - Basics
---

The word array is best explained in the Hugo Book, but this page will
try to provide a quick overview.

After every input, the engine writes every understood word to an array-
a *word array*, if you will. In the following command:

>&gt;GET LAMP

"GET" would be saved to word\[1\], and "LAMP" would be saved to word\[2\].

## Multi-command inputs

When you have something like this:

>&gt;GO NORTH. DIG. G. G.

The whole line is saved to the word array. That's why when we write
command-finessing routines that use the [words](words) global
to find the maximum number of words, we can't assume that
`word[<words>]` is the last word of the first command. Therefore, it
is often better to start at the beginning of a command when using loops
and such.

#### loop that finds the last word of the current command

    local a
    for (a=1; a < words ; a++)
    {
        if word[(a+1)] = ""
            break
    }

### How multi-command inputs are processed

In the earlier multi-command example, originally, the word array would
originally go from word\[1\] to word\[9\]. After "GO NORTH" is
processed, though, the line is re-parsed and will only be six elements
long, going from word\[1\] ("DIG") to word\[6\] (the last full-stop).

## Particular to the Word Array

Unlike [globals](globals) (or just about anything else), the
word array is not affected by state-changing things like
[undo](undo), [restore](restore), or
[restart](restart). It is only affected by actual inputs or
being written over by code. This makes the word array an effective yet
sneaky way to maintain certain behaviors through UNDOs and RESTARTs. For
instance, the the [beta.h](beta.h) library extension uses the
word array to let the code know that the `transcript_is_on` global
should be reset to true after a restart.

## Command Manipulation

[PreParse](PreParse) code often involves modifying the
player's input to a phrasing that is easier for us to parse. One does
this using routines like [InsertWord](InsertWord) or
[DeleteWord](DeleteWord) to make space in or remove words
from the word array. The important thing is that if you change the total
number of words, you should also change the value of the
[words](words) global to match.
