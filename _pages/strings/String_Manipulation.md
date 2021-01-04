---
title: String Manipulation
permalink: /strings/string-manipulation/
categories: 
  - Strings
  - Routines
---

Here are a couple unofficial [routines](/routines/) for
manipulating string arrays.

## Lowercase

Here is a routine that'll make every letter lowercase (especially useful
if you are making words suitable for `noun` properties and the like):

    routine Lowercase(stringarray)
    {
        local len, i
        len = StringLength(array stringarray)
        for (i=0; i<len; i=i+1) ! the actual case-conversion loop
            {
            if array stringarray[i] >= 'A' and array stringarray[i] <= 'Z'
                array stringarray[i] = array stringarray[i] + ('a'-'A')
            }
    }

## CapitalizeEveryFirstLetter

This routine capitalizes the first letter of every word in a multi-word
string. This is useful for strings are full character names and the
like.

    routine CapitalizeEveryFirstLetter(stringarray)
    {
        local len, i, new
        len = StringLength(array stringarray)
        for (i=0; i<len; i=i+1) ! the actual case-conversion loop
            {
            if new or i=0
                {
                if array stringarray[i] >= 'a' and array stringarray[i] <= 'z'
                    array stringarray[i] = array stringarray[i] - ('a'-'A')
                new = 0
                }
            elseif array stringarray[i] >= 'A' and array stringarray[i] <= 'Z'
                array stringarray[i] = array stringarray[i] + ('a'-'A')

            if array stringarray[i] = ' '          ! a space
                new = 1
            }
    }

## StringAddTo

Here is a routine for quickly tagging on one string routine to another.
Put a value in the `add_space` parameter if you'd like to throw a space
between them.

    routine StringAddTo(original_array, addition_array, add_space)
    {
        local f
        for (f=0;f< array original_array[] ; f++ )
            {
            if (array original_array[f] = 0)
                {
                break
                }
            }

        text to (array original_array + f)
        if (add_space)
            print " ";
        StringPrint(array addition_array)
        text to 0
    }
