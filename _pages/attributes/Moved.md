---
title: moved
permalink: /attributes/moved/
categories: 
  - Attributes
---

`moved` is an [attribute](attribute) for keeping track of
whether an item has been physically interacted with. As such, it is set
by `DoDrop`, `DoOpen`, `DoClose`, and [Acquire](Acquire)
(which is called by `DoGet`). The existence of the `moved` attribute
determines whether [initial descriptions](initial_desc) are
printed when [DescribePlace](DescribePlace) is called.
`moved` is [aliased](alias) by the
[visited](visited) attribute.
