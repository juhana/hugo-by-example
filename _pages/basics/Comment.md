---
title: Comments
permalink: /basics/comments/
categories: 
  - Basics
---

A comment may be placed in a Hugo program anywhere that
[whitespace](whitespace) (blanks and tabs) may be used. There
are two types of comments, *[line comments](line_comment)*
and *[block comments](block_comment)*.

A line comment is an unquoted [exclamation
point](exclamation_point) **!**. The exclamation point is
treated as an end of line; it and anything following it on the same line
are ignored.

A block comment is a line beginning with exclamation point followed by
backslash, **!\\** and continues until the inverse symbol, a backslash
followed by an exclamation point, **\\!**. Everything inside the block
comment is ignored by the compiler.
