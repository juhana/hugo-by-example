---
title: Array
permalink: /basics/array/
categories: 
  - Basics
---

*For information on the word array, see the [Word Array](basics/word-array/) entry.*  
*For information on string arrays, see the [String Arrays](strings/string-arrays/) entry.*  
*For information on multiple-element properties, see [Properties](properties/).*

Arrays are a method of storing multiple-element information. They are
convenient for saving lists or the states of several things at once.

## Declaring an array

Before we can fill an array, we need to declare it. Example:

    array list_of_characters[10]

`list_of_characters` has 10 elements. Now, since array element numbers
start at `array_name[0]`, this one would go from `list_of_characters[0]`
to `list_of_characters[9]`. For people new to arrays, that idea can be a
bit unintuitive.

## Filling an array

Now, in a [routine](routines/) somewhere, we can fill the
array. There are several ways this can be done.

### One by one

One way involves listing each element individually.

    list_of_characters[0] = Fred
    list_of_characters[1] = Slappy
    list_of_characters[2] = Meredith
    list_of_characters[3] = Agnes
    ! etc.

### A bunch at once

Another method combines everything into one line:

    list_of_characters[0] = Fred, Slappy, Meredith, Agnes !... etc.

This way, the engine automatically defines `list_of_characters[1]` as
Slappy, and so on.

### Stuck in the middle with Hugh

In fact, we don't even need to start at the beginning. In the following:

    list_of_characters[5] = Hugh, Jack, Emily, Tabitha !... etc.

`list_of_characters[6]` automatically gets defined as Jack, and so on.

## Getting the array length

To get the number of elements in an array quickly, refer to it as such:
`list_of_characters[]` would return 10.

## Arrays as routine parameters

Occasionally, you'll want to write [routines](routines/) that
can be fed different arrays as [parameters](definitions/parameter/). In
those cases, within the routine itself, you'll need to preface the
parameter name with "array". Hugo needs a little assistance knowing that
it is dealing with arrays.

**Example:**

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

## Arrays vs. Properties

In many ways, the workings of arrays and multiple-property elements are
interchangeable. Working with both involves writing loop scripts that
check each element before adding new elements (or clearing them). Which
method you use will largely depend on which feels better for your
purposes.
