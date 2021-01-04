---
title: Cls
permalink: /input-output/cls/
categories: 
  - Input-Output
---

Simply enough, `cls` clears the *current window*. When used in the main
window, it can serve various narrative purposes like signifying that the
player character is in unfamiliar territory or is discombobulated.
`cls` is just as useful (if not moreso), though, in other
[windows](Window), as windows often need to be cleared before
we redraw them. It is at its most complicated, though, when dealing with
a different-size-hopping status window (add another floating window for
further complications), where it may require several alternating `cls`'s
and "[window 0](Window)"'s to properly clear the status
window.
