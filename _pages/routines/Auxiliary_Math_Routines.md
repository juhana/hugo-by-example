---
title: Auxiliary Math Routines
permalink: /routines/auxiliary-math-routines/
categories: 
  - Routines
---

[Hugolib.h](Hugolib.h) provides some "auxiliary math
routines", providing a range of useful functions.

| Routine        | Returns:                                        |
|----------------|-------------------------------------------------|
| `abs(a)`       | the absolute value of &lt;a&gt;                 |
| `higher(a, b)` | the greater of &lt;a&gt; or &lt;b&gt;           |
| `lower(a, b)`  | the lower of &lt;a&gt; or &lt;b&gt;             |
| `mod(a, b)`    | the remainder of &lt;a&gt; divided by &lt;b&gt; |
| `pow(a, b)`    | &lt;a&gt; to the power of &lt;b&gt;             |

### Examples:

Here is a routine that uses `abs` to determine if the difference between
two numbers falls within a specified range:

    routine IsNear(fir,sec,range)
    {
        if (abs(fir - sec) <= range)
            return true
        else
            return false
    }

In games with multiple [windows](window), `mod` is nice for
determining if you have an odd or even screen width (in characters):

            if mod(display.screenwidth,2)
