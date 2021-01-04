---
title: need_newline
permalink: /globals/need_newline/
categories: 
  - Global Variables
---

`need_newline` is a [global variable](basics/global/) mainly used by
[DescribePlace](guts/describeplace/) to determine whether or not
new lines are needed at various points. Specifically, if the
`INDENT_SIZE` constant is set to 0,
`need_newline` is set true to increase readability.
