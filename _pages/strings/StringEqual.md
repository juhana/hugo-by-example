---
title: StringEqual
permalink: /strings/stringequal/
categories: 
  - Strings
  - Routines
---

`StringEqual` is an "unadvertised" [hugolib.h](hugolib.h)
routine.

## The code

    routine StringEqual(a, b)
    {
        return not StringCompare(a, b)
    }

## What it does

As [StringCompare](StringCompare) returns 0 if the two
strings are the same, `StringEqual` negates its results to provide a
more intuitive "are these two strings equal?"-type routine.

**Example:**

    if StringEqual(string_array1,string_array2)
         "This line is printed if the two strings are identical."
    else
         "This line is printed if they are not."
