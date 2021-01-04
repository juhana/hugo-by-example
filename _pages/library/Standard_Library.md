---
title: Standard Library
permalink: /library/
categories: 
  - Hugo Library
  - Basics
---

| Library component  | Summary of what it does  |
|--------------------|--------------------------|
| [`hugolib.h`](library/hugolib.h/)  | Defines the common [properties](properties/) and [attributes](attributes/) used in Hugo games. It also defines several global [variables](basics/variables/) constants used by routines in the library files. |
| [`system.h`](library/system.h/)  | Has routines for taking advantage of engine/interpreter capabilities like game pauses. |
| `resource.h`  | Has routines for the inclusion of sound and graphics.  |
| [`window.h`](library/window.h/)  | Has some pre-written classes for games with multiple windows.  |
| [`verblib.g` & `verblib.h`](library/verblib/)  | Verblib.g has the Hugo Standard Libary verb grammar tokens and verblib.h has the verb routines.  |
| `verbstub.g` & `verbstub.h` | The verbstub files define verbs that are less common and is not included in compilation by default.  |
| `hugofix.g` & `hugofix.h`  | Has additional verb routines for game debugging. |
