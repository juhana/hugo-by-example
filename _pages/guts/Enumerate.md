---
title: Enumerate
permalink: /guts/enumerate/
categories: 
  - Hugo Guts
---

`enumerate` is a convenient function for quickly giving varying values
to either [constants](/basics/constants/) or
[global variables](/basics/variables/).

<table>
<thead>
<tr class="header">
<th><p>Usage</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>enumerate [globals] [ start=&lt;starting value&gt; ] [ step &lt;+|-|*|/&gt; &lt;number to add/subtract/multiply/divide by&gt; ]<br />
{<br />
&lt;constant/global #1&gt; , &lt;constant/global # 2&gt;, &lt;constant/global # 3&gt;, ! etc<br />
}</p></td>
</tr>
</tbody>
</table>

## "No Frills" Enumeration

If no start or step values are specified, the values given by
`enumerate` start at 0 and increase by 1 for each constant/variable. In
the following:

    enumerate
    {
    MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY
    }

MONDAY = 0, TUESDAY = 1, WEDNESDAY = 2, THURSDAY = 3, AND FRIDAY = 4.

You can even change it up at any point like this:

    enumerate
    {
    A, B, C = 5, D, E
    }

A = 0, B = 1, C = 5, D = 6, E = 7. Despite the leap, the increase-by-one
pattern continues unabated.

## Starting

You don't have to start at 0, though. With the `start` option, you can
start at any value you want.

    enumerate start = 1
    {
    A, B, C
    }

A = 1 , B = 2, C = 3. The [standard library](/library/) does this all of the time.

## Stepping

We can change the difference between each step, too. If we have:

    enumerate step *2
    {
    A=1 , B, C
    }

A = 1 , B = 2 , C = 4

## Both

You can do both like this:

    enumerate start=2 step * 2
    {
        FIRST, SECOND, THIRD, FOURTH, FIFTH
    }

FIRST = 2 , SECOND = 4, THIRD = 8, FOURTH = 16, FIFTH = 32

## Global Variables

All of the examples so far have shown how to
[declare](/declarations/) [constants](/basics/constants/). If
you want to declare some 
[global variables](/basics/variables/) with some initial
starting values, you just add "globals" like in the following:

    enumerate globals
    {
    <global1>, <global2>,...
    }

It'll work with all of the above stuff, too.
