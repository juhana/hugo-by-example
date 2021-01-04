---
title: Case
permalink: /basics/case/
categories: 
  - Basics
---

The **case** statement is used to specify an action to take when the
value examined by the [select](basics/select/) statement matches the
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

Each *case* statement permits one statement. If more statements are
required for any case label, the block should be encapsulated by **{**
before the start of code for the particular case value and **}** at the
end of the code for that case value.

Unlike the C programming language, the match of a case value executes
only the code for that value in that [select](basics/select/)
statement; other cases are not executed; execution continues with the
next statement after the **select** statement.

See Also: [select](basics/select/)
