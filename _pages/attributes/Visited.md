---
title: visited
permalink: /attributes/visited/
categories: 
  - Attributes
---

`visited` is an [attribute](attributes/) for keeping track of
whether a location has been entered previously. As such, it is set by
[MovePlayer](routines/moveplayer/) after a successful move (if the
player wasn't moved silently, [DescribePlace](guts/describeplace/)
is called one time before it is set). The existence of the `visited`
attribute determines whether the room's
[initial description](properties/descriptions/#initial_desc) is printed when
[DescribePlace](guts/describeplace/) is called. `visited` is an
[alias](basics/alias/) of the [moved](attributes/moved/) attribute.
