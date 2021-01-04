---
title: DeleteWord
permalink: /guts/deleteword/
categories: 
  - Hugo Guts
---

`DeleteWord` is a [hugolib.h](hugolib.h)-provided
[routine](routine) for [word array](word_array)
modification. As the name suggests, it removes words from the word array
and updates the value of the [words](words) global.

## The code

    routine DeleteWord(p, n)                ! deletes <n> words at position <p>
    {
        local i

        if n = 0:  n = 1

        if (words < n) or (p + n >= MAX_WORDS):  return

        for (i=p; i<=words-n; i++)
            word[i] = word[i+n]
        word[words] = ""
        words = words - n

        return n
    }

## An example

Examples from various Kent Tessman games:

        local i

        ! Since "get off wing" or "exit wing" will cause a parser complaint
        ! because the player isn't really "in" the wing, change either to
        ! simply "exit" (i.e., to direct the library to out_to).
        !
        if (word[1] = "get", "climb") and word[2] = "off"
        {
            word[1] = "exit"
            DeleteWord(2)
        }
        if word[1] = "exit" and ObjWord(word[2], wing)
            DeleteWord(2)

        ! Allow handing of, e.g., "ask girl about her mother", so that "her"
        ! doesn't get mapped incorrectly
        !
        if word[1] = "ask", "tell"
        {
            for (i=2; i<=words and word[i]~=""; i++)
            {
                if word[i] = "his", "her", "your"
                {
                    DeleteWord(i)
                    break
                }
            }
        }

        ! Change "character, thank you" to "thank character"
        if (word[3] = "thank", "thanks") and word[2] = "~and"
        {
            word[2] = word[3]
            word[3] = word[1]
            DeleteWord(1)
        }
