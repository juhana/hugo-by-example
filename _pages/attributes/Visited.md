---
title: visited
permalink: /attributes/visited/
categories: 
  - Attributes
---

`visited` is an [attribute](attribute) for keeping track of
whether a location has been entered previously. As such, it is set by
[MovePlayer](MovePlayer) after a successful move (if the
player wasn't moved silently, [DescribePlace](DescribePlace)
is called one time before it is set). The existence of the `visited`
attribute determines whether the room's [initial
description](initial_desc) is printed when
[DescribePlace](DescribePlace) is called. `visited` is an
[alias](alias) of the [moved](moved) attribute.
