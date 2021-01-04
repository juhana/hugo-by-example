---
title: words
permalink: /globals/words/
categories: 
  - Global Variables
---

`words` is a [hugolib.h](library/hugolib.h/)-defined 
[global variable](basics/global/). Set each turn by the engine, it holds the
total number of words used in the player input and is invaluable when
writing parser-helping code. How it works:

1.  Words like "the", "a", and "an" are ignored.
2.  Words like "then" and certain punctuation (like full stops) are
    saved as word "". In the command:

    `&gt;GET FIRECRACKER THEN LIGHT IT`

    `words` would be set to 5, but "THEN" would be saved as "" (this is
    how Hugo separates stringed commands).
3.  `words` is set to the total number of valid dictionary words and ""'s.

## `words` in action

Here is an example script of a game that prints the value of `words`
each turn:

>&gt;look. x me. listen to me.
>
>Start Location  
>words = 9
>
>Looking good.  
>words = 7
>
>You are not making a sound.  
>words = 4

Notice how `words` is decremented as the game processes each part of the
multi-command input.

## Using `words` to find the end of the command

Considering that `words` is takes the whole input into account, one must
be careful to not write code that assumes `words` equals the number of
words in the current command. To find the length of *just* the current
command, one could do something like this:

    local a
    for (a=1; a < words ; a++)
    {
        if word[(a+1)] = ""
            break
    }

Now, `a` will equal the number of words in the first command.

## changing `words`

When deleting or adding words to the [word array](basics/word-array/)
during [PreParse](parsing/preparse/), it is important to also update
`words` to match the new total. This is why it is recommended to use
utility routines like [InsertWord](guts/insertword/) or
[DeleteWord](guts/deleteword/) for word array modification, as they
update `word` for you.
