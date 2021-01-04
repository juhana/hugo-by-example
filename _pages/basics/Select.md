---
title: select
permalink: /basics/select/
categories: 
  - Basics
---

The **select** statement is used to choose a particular statement to
execute when the value examined by the select statement matches the
particular case value. The following example from the book shows this:

    select hour
       case 1: print "one";
       case 2: print "two";
       case 3: print "three";
    .
    .
    .
       case 12: print "twelve";
    print " o'clock."

The value of **hour** is examined and if it matches any of the case
statements specified, control is transfered to that specific case
statement.

Unlike the C programming language, the match of a case value does not
"fall through" to the remainder of any case statements following the one
that is selected; the select statement executes only the code for that
case value; other cases are not executed, and execution continues with
the next statement after the **select** statement.

A select statement ends with, and execution follows after the select
statement with the first statement that is not a case statement.

See Also: [case](/basics/case/)
