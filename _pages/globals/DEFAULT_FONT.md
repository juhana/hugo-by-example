---
title: DEFAULT_FONT
permalink: /globals/default_font/
categories: 
  - Global Variables
---

Setting a `DEFAULT_FONT` [variable](basics/variables/) allows
routines like [PrintStatusLine](input-output/printstatusline/) to return to
the game's chosen font style, regardless of what it is. If no
`DEFAULT_FONT` has been set, the game will be monospaced (like
[Font](input-output/font/)(PROP_OFF)). Oftentimes, games will set
`DEFAULT_FONT` to **PROP_ON**, but one define it with many
[constants](basics/constants/), using mask syntax:

    DEFAULT_FONT = PROP_ON|BOLD_OFF|ITALIC_OFF|UNDERLINE_OFF
