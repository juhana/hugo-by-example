---
title: Argument
permalink: /definitions/argument
categories: 
  - Definitions
---

An **argument** is a value supplied to a [routine](routine),
like:

    routine RoutineName(argument1,argument2)

### Kent's own words

>Truth is, arguments are just the first local variables in a routine,
so
>
>```
>    routine MyRoutine(first_arg)
>    {
>         ...
>```
>
>is the same as
>
>```
>    routine MyRoutine
>    {
>         local first_arg
>         ...
>```
>
>since either can be called as MyRoutine(value) and have first_arg =
value.

So, arguments are [local variables](locals), but it is
convenient to use their separate syntax as it makes the
[routine](routine) easier to read.
