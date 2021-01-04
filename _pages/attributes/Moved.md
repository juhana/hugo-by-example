---
title: moved
permalink: /attributes/moved/
categories: 
  - Attributes
---

`moved` is an [attribute](attributes/) for keeping track of
whether an item has been physically interacted with. As such, it is set
by `DoDrop`, `DoOpen`, `DoClose`, and [Acquire](guts/acquire)
(which is called by `DoGet`). The existence of the `moved` attribute
determines whether [initial descriptions](properties/descriptions/#initial_desc) are
printed when [DescribePlace](guts/describeplace/) is called.
`moved` is [aliased](basics/alias/) by the
[visited](attributes/visited/) attribute.
