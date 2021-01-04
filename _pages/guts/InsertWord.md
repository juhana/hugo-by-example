---
title: InsertWord
permalink: /guts/insertword/
categories: 
  - Hugo Guts
---

`InsertWord` is a [hugolib.h](hugolib.h)-provided
[routine](routine) for [word array](word_array)
modification. Basically, it just makes space for you so that you may add
words yourself.

## The code

    routine InsertWord(p, n)                ! inserts <n> words at position <p>
    {
        local i

        if n = 0:  n = 1

        if words+n >= MAX_WORDS:  return

        for (i=words+n; i>p; i--)
            word[i] = word[i-n]
        words = words + n

        return n
    }

## An example

Without coming up with a situation where it would be useful, here is an
example:

    InsertWord(3,2) ! make two empty word array elements at position 3
    word[3] = "<first word>"
    word[4] = "<second word>"
