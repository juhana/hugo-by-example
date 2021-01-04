---
title: StringCompare
permalink: /strings/stringcompare/
categories: 
  - Strings
  - Routines
---

| calling form                   | description               |
|--------------------------------|---------------------------|
| `StringCompare(array1,array2)` | Returns 1 if `array1` is lexically greater than `array2`, -1 if `array1` is lexically less than `array2`, and 0 if the strings are identical. |

`StringCompare` is a surprisingly seldom-used string-handling routine.
No available-source Hugo games actually use it, but it *is* used by the
[alphabetization routines](Sort.h#Unofficial_additions) for
the [Sort.h](Sort.h) library contribution. First, they
convert both string arrays to lowercase letters (as mixed case letters
can screw up [lexical values](ASCII_values)), and then they
use `StringCompare` to determine alphabetical order.
