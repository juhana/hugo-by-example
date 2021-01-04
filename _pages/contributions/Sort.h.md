---
title: Sort.h
permalink: /contributions/sort.h/
categories: 
  - Library Contributions
---

`Sort.h` is a library extension contributed by Christopher Tate. It is
versatile in that the one routine can be used to arrange objects or
values in a number of ways (increasing/decreasing order,
alphabetical/reverse alphabetical order, etc.)- all depending on which
routine you have it call. It uses the 
[Bubble Sort](http://en.wikipedia.org/wiki/Bubble_sort) method of sorting.

## The extension itself

Following is the code in its entirety, allowing you to cut and paste it
into your own file or take a look at its workings:

    !\-----------------------------------------------------------------------
        Sorting arrays of objects in Hugo
        Copyright 2001 by Christopher Tate <ctate@acm.org>

        A "comparison routine", as used here, is a routine that returns
        non-zero when the order of its two arguments should be
        swapped.  The arguments are always passed in the order they
        currently appear in the array.

        For example, if you want to sort the array by the objects'
        "height" property in such a way that the shortest object -- the
        one with the smallest "height" -- is first, you could use this
        comparison routine:

            routine AscendingHeightComparison(obj1, obj2)
            {
                return (obj1.height > obj2.height)
            }

        If obj1's height is greater than obj2's, it means that the taller
        object currently appears earlier in the array, so the two elements
        should be swapped.

        Assuming that your array of objects is called "lineup" and the
        number of objects in the array is in the variable "num_suspects,"
        you would sort the array like this:

            SortArray(lineup, num_suspects, &AscendingHeightComparison)

        Note that you need the '&' character to indicate that the argument
        is the address of the comparison routine, not the result of running it.
    -----------------------------------------------------------------------\!

    #ifclear _SORT_H
    #set _SORT_H

    !-----------------------------------------------------------------------
    ! SortArray() arguments:
    !
    ! data = array to sort
    ! num = number of elements in the array
    ! comp_routine = the address of the comparison routine to use

    routine SortArray(data, num, comp_routine)
    {
        local i
        local did_swap

        for (i = 0; i < num; i = i + 1)
        {
            local j
            did_swap = false
            for (j = num - 1; j > i; j = j - 1)
            {
                local swap
                swap = call comp_routine(array data[j-1], array data[j])
                if swap
                {
                    local tmp
                    tmp = array data[j]
                    array data[j] = array data[j-1]
                    array data[j-1] = tmp
                    did_swap = true
                }
            }
            ! if we didn't swap any elements, then the array is sorted
            if not did_swap : return
        }
    }

    !-----------------------------------------------------------------------
    ! SORT_ASCENDING() and SORT_DESCENDING()
    !
    ! These simple comparison routines are provided to handle the
    ! common cases of sorting a numeric array in ascending or
    ! descending order.  For example, to sort an entire numeric array
    ! called "data" in ascending order, just do this:
    !
    ! SortArray(data, data[], &SORT_ASCENDING)

    routine SORT_ASCENDING(obj1, obj2)
    {
        return (obj1 > obj2)
    }

    routine SORT_DESCENDING(obj1, obj2)
    {
        return (obj1 < obj2)
    }

    #endif

As you can see, it is set up to be `#include`'d like any other optional
library file.

### How to call

To reiterate, to sort an array of numbers in descending order, one would
have this is in the code:

            SortArray(array_comprised_of_number_values, number_of_elements_in_array, &SORT_DESCENDING)

Sorting objects by property value will require new routines. A routine
that sorts by `character.weight` value would look like:

    routine HeavyToLight(obj1, obj2)
    {
        return (obj1.weight < obj2.weight)
    }

In that example, the array would be filled with pointers to the objects
themselves instead of just numbers.

## Unofficial additions

### Alphabetical order

Like we said in the introduction, `Sort.h` can be used for sorting
`object.name`'s or other string properties by alphabetical order.
Following are two additional routines that use
[StringCompare](strings/stringcompare/) to do so. If sorting a
property other than `name`, change the code where applicable.

    ! We'll need an additional string array so we can properly compare uppercase strings
    ! to lowercase strings
    array lowercase[10] ! will compare up to 10 characters of string; use more or less if you want

    routine SortAlphNames(obj1, obj2)
    {
        local len, k
        len = string(lowercase, array obj2.name, 10)
        for (k=0; k<len; k=k+1) ! the actual case-conversion loop
            {
            if lowercase[k] >= 'A' and lowercase[k] <= 'Z'
            lowercase[k] = lowercase[k] + ('a'-'A')
            }
        len = string(_temp_string, array obj1.name, 255)
        for (k=0; k<len; k=k+1) ! the actual case-conversion loop
            {
            if _temp_string[k] >= 'A' and _temp_string[k] <= 'Z'
                _temp_string[k] = _temp_string[k] + ('a'-'A')
            }
        if StringCompare(lowercase,_temp_string) = -1
            return 1
        else
            return 0
    }

    !  The routine doesn't need to return with some kind of comparison statement
    !  Returning true or false works just as well

### Reverse alphabetical order

    routine SortReverseAlphNames(obj1, obj2)
    {
        local len, k
        len = string(lowercase, array obj2.name, 10)
        for (k=0; k<len; k=k+1) ! the actual case-conversion loop
            {
            if lowercase[k] >= 'A' and lowercase[k] <= 'Z'
                lowercase[k] = lowercase[k] + ('a'-'A')
            }
        len = string(_temp_string, array obj1.name, 255)
        for (k=0; k<len; k=k+1) ! the actual case-conversion loop
            {
            if _temp_string[k] >= 'A' and _temp_string[k] <= 'Z'
                _temp_string[k] = _temp_string[k] + ('a'-'A')
            }
        if StringCompare(lowercase,_temp_string) = 1
            return 1
        else
            return 0
    }

### Random order

Here is a quick routine just for shaking things up:

    routine SORT_RANDOM(obj1, obj2)
    {
        return (random(2) - 1)
    }

See also: [SortProp](routines/sortprop/)
