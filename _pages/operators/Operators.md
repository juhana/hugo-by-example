---
title: Operators
permalink: /operators/
categories: 
  - Operators
---

An **operator** is a symbol or word used to provide a bridge between the
two items in order to define some functionality. Operators generally
provide some sort of mathematical or logical functionality. The
following are the operators used in the Hugo language:

**+** : the plus symbol, adds two values, e.g. 6+3 is 9.

**-** : the minus symbol, subtracts the value on the right from the
value on the left, e.g. 6-3 is 3.

**/** : the divide symbol, divides the value on the left by the value on
the right, e.g. 6/3 is 2.

**\*** : the multiply symbol, has two uses.

1.  In an arithmetic expression, multiplies the two values together,
    e.g. 6\*3 is 18.
2.  In an [enumerate](/guts/enumerate/) command, used to specify an
    increment on the *step* parameter. In an example from the book:

```
enumerate step *2
{
    A = 1, B, C, D
}
```

giving: A = 1, B = 2, C = 4, D = 8.


**and**, **or** : boolean operators which compare two values, the "A"
value to the left of the operator, and the "B" value to the right of the
operator produce a true/false result

**not** : boolean operator which produces a result by inverting the "B"
value to the right of the operator

**[is](/attributes/is/)** : used to test whether an [attribute](/attributes/) is set in an [object](/globals/object/)

    if (Managers_Office is light)

The test can be reversed by the **NOT** operator:

    if (Managers_Office is not light)
