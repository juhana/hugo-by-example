---
title: IsNear
permalink: /routines/isnear/
categories: 
  - Routines
---

`IsNear` is an unofficial utility routine for determining whether two
numbers are within a certain proximity of eachother. I've found that as
I (Roody) do more and more games with multiple windows, I find myself
wanting to work with approximations, so the screen might work one way if
the screen width is in the 40-80 character range and might work another
if it is in the 80-120 range (and so on). `IsNear` intends to make such
situations easier to code for.

    routine IsNear(fir,sec,range)
    {
        if (abs(fir - sec) <= range)
            return true
        else
            return false
    }
