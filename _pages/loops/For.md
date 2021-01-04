---
title: For
permalink: /loops/for/
categories: 
  - Loops
---

The most complex loop is the `for` statement, for all of its
configurations.

## `for (`<assignment>`; `<expression>`; `<modifier>`)`

There are things to be said about each of these parts, so let's break it
down:

| `for` loop component | description                                                      | example      |
|----------------------|------------------------------------------------------------------|--------------|
| <assignment>         | declares the starting value of the variable the loop is using    | *i=1*        |
| <expression>         | the code block will execute *as long as this expression is true* | *i &lt;= 15* |
| <modifier>           | change to the variable after every iteration of the loop         | *i++*        |

Let's look at this code for the bat in HugoZork:

         local i
         for (i=0; i<3; i++)
         {
         "_   Fweep!"
         }

Which results in:

<div class="output">

`  Fweep!   Fweep!   Fweep!`

</div>

## Defining By Omission

The `for` loop will still work if one of the components mentioned above
is missing. Depending on which one, the resulting loop will perform in
different ways.

| omission type            | how it is processed                                                                                                                                                                                                                                                                                                       |
|--------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **for (; i&lt;4 ; i++)** | A missing assignment results in the loop starting with the value of the variable ("i" in this case) being whatever it was before the loop. Of course, if the variable is a recently-defined [local variable](Variables#Local_Variables) that hasn't been given a value yet, that means it'll be starting at 0. |
| **for (i=1;;i++)**       | If there isn't an <expression> declared, the loop will execute indefinitely. This means that the code block must execute [break](Break) under some circumstances.                                                                                                                                              |
| **for (i=1; i&lt;4 ;)**  | (Yes, that last semi-colon is necessary) This case requires the code block to [break](Break) under certain circumstances or change the value of the variable itself to avoid an endless loop, but other than that, it will still run fine.                                                                     |

## `for `*`x`*` in `*`object`*

The *other* way that `for` can be used is for executing code against
every object within another object.

This executes the code block with the first child of the object as the
variable. It then executes again with the next child (and so on).
