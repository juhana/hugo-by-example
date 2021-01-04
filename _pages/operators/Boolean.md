---
title: Boolean
permalink: /operators/boolean/
categories: 
  - Operators
---

Some [operators](operators/) compare the values of true/false
condtions and return combinations or inversons of those values. These
are what are referred to as *boolean* operators because the values they
work with are true/false as opposed to numbers in general.

# Operators

## And

**And** is used to combine two values on the rule that, if both are
true, the result is true; otherwise the result is false. See the table
below for examples.

## Is

**Is** returns the value of an [attribute](attributes/) in an
[object](globals/object/). If the attribute is set, is returns true;
otherwise it returns false. May be inverted by using *is not*. See the
table below for examples.

## Not

**Not** is used to negate or reverse a single boolean value. In testing
whether an [attribute](attributes/) is set, or an
[object](globals/object/) is defined, *not* reverses the test. In the
following code

        if (thedoor is not open )
      ... ...
        if (not thedoor)

The first line tests that the [open](attributes/open/)
[attribute](attributes/) was not set for the
[object](globals/object/) **thedoor**, and the second line tests to
see if the object **thedoor** is not defined. Often used in a 
[verb routine](verb-routines/) to determine whether someone typed a
[parameter](definitions/parameter/) to a verb. See the table below for
examples.

## Or

**Or** is used to combine two values on the rule that, if either is
true, the result is true; otherwise the result is false. See the table
below for examples.

# Comparison Table

The following table shows the result of boolean comparisons

See Also: [Operators](operators/),
[keywords](guts/keywords/)
