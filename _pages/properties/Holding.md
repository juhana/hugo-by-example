---
title: holding
permalink: /properties/holding/
categories: 
  - Properties
---

`holding` is a property given to [containers](basics/containers-and-platforms/).
When determining whether a container has room for another object (based
on its [capacity](properties/capacity/)),
[CalculateHolding](routines/calculateholding/) uses it to store the sum
of [size](properties/size/) values for each object already in it. Because
of this, the author is not required to set an initial value (other than
0) as it will just be re-set the next time `CalculateHolding` is run.
