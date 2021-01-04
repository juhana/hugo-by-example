---
title: If
permalink: /basics/if/
categories: 
  - Basics
---

The **if** statement allows for comparisons and tests for the purpose of
making choices of things to do. One or more comparisons, separated by
boolean operators, are made, and if all of the comparisons are
successful, *statement1* is executed. If any comparison in the **if**
statement fails, the optional **else** clause is invoked, and statement2
is *executed*, otherwise execution continues with the statement
following the **if** statement.

*Statement1* may appear immediately after the **if** statement, or may
appear on the next line. *Statement2*, if present, may appear
immediately after the **else** clause, or on the next line. The **else**
may optionally be followed by a colon (**:**). If the code to be
executed in *statement1* and/or in *statement2* exceeds one line, it
must be placed in a block consisting of an open brace **{** followed by
the code to be executed and closed with a close brace **}**.

The types of comparisons which may be made are as follows:

| type    | sample                                       |
|---------|----------------------------------------------|
| case 1: | &lt;*value1*&gt;                             |
| case 2: | &lt;*value1*&gt; *operator* &lt;*value2*&gt; |
| case 3: | **not** &lt;*value1*&gt;                     |

-   In a case 1 comparison, *value1* is compared to true, which is the
    boolean value true, or any number other than zero. If the result
    evaluates to true, the comparison is successful.
-   In a case 2 comparison, *value1* is compared to *value2* according
    to the supplied operator, and both values must be equivalent, either
    they are both numbers, both boolean values, or both strings. The
    possible comparisons are as follows

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
<col style="width: 70%" />
</colgroup>
<thead>
<tr class="header">
<th><p>operator</p></th>
<th><p>comparison</p></th>
<th><p>meaning</p></th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p><strong>&lt;</strong><br />
(less than)</p></td>
<td><p><em>value1</em> &lt; <em>value2</em></p></td>
<td><p>if value1 is less than value2, the comparison is successful</p></td>
</tr>
<tr class="even">
<td><p><strong>&gt;</strong><br />
(greater than)</p></td>
<td><p><em>value1</em> &gt; <em>value2</em></p></td>
<td><p>if value1 is greater than value2, the comparison is successful</p></td>
</tr>
<tr class="odd">
<td><p><strong>=</strong><br />
(equal)</p></td>
<td><p><em>value1</em> = <em>value2</em></p></td>
<td><p>if value1 is equal to value2, the comparison is successful</p></td>
</tr>
<tr class="even">
<td><p><strong>~=</strong><br />
(not equal)</p></td>
<td><p><em>value1</em> ~= <em>value2</em></p></td>
<td><p>if value1 is not equal to value2, the comparison is successful</p></td>
</tr>
<tr class="odd">
<td><p><strong>&lt;=</strong><br />
(less than or equal)</p></td>
<td><p><em>value1</em> &lt;= <em>value2</em></p></td>
<td><p>if value1 is less than or equal to value2, the comparison is successful</p></td>
</tr>
<tr class="even">
<td><p><strong>&gt;=</strong><br />
(greater than or equal)</p></td>
<td><p><em>value1</em> &gt;= <em>value2</em></p></td>
<td><p>if value1 is greater than or equal to value2, the comparison is successful</p></td>
</tr>
<tr class="odd">
<td><p><strong>is</strong></p></td>
<td><p><em>object1</em> is <em>attribute2</em></p></td>
<td><p>if the specified attribute2 is set in object1, the comparison is successful</p></td>
</tr>
<tr class="even">
<td><p><strong>is not</strong></p></td>
<td><p><em>object1</em> is not <em>attribute2</em></p></td>
<td><p>if the specified attribute2 is not set in object1, the comparison is successful</p></td>
</tr>
<tr class="odd">
<td></td>
<td></td>
<td></td>
</tr>
</tbody>
</table>

-   In a case 3 comparison, the operator is **not** and the result is
    tested to determine if it is false, and if the result is false, the
    comparison is successful

The boolean operators that separate each comparison are as follows:

| boolean operator                | meaning                                                 |
|---------------------------------|---------------------------------------------------------|
| comparison1 **and** comparison2 | if both comparisons are true, the result is successful. |
| comparison1 **or** comparison2  | if either comparison is true, the result is successful. |
| **not** comparison2             | if comparison2 is not true, the result is successful.   |
|                                 |                                                         |

If there are questions over how the comparisons are to be made, they may
be isolated within parentheses. For example

       if self is open and self is locked or self is switchable

Would test to see if the item is open, and it is locked, then test if it
is switchable. Only if all three tests succeed will the test succeed.
However, if the intended test was open and locked, or if it is
switchable, then parentheses are required, like this:

       if (self is open and self is locked) or (self is switchable)

In this case, if it passes the first two tests, or the second test, it
succeeds.
