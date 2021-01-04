---
title: Standard Library
permalink: /library/
categories: 
  - Hugo Library
  - Basics
---

| Library component  | Summary of what it does  |
|--------------------|--------------------------|
| [`hugolib.h`](Hugolib.h)  | Defines the common [properties](properties) and [attributes](attributes) used in Hugo games. It also defines several global [variables](variables) constants used by routines in the library files. |
| [`system.h`](System.h)  | Has routines for taking advantage of engine/interpreter capabilities like game pauses. |
| [`resource.h`](Resource.h)  | Has routines for the inclusion of sound and graphics.  |
| [`window.h`](Window.h)  | Has some pre-written classes for games with multiple windows.  |
| [`verblib.g` & `verblib.h`](Verblib.h_g)  | Verblib.g has the Hugo Standard Libary verb grammar tokens and verblib.h has the verb routines.  |
| [`verbstub.g` & `verbstub.h`](Verbstub.h_g) | The verbstub files define verbs that are less common and is not included in compilation by default.  |
| [`hugofix.g` & `hugofix.h`](Hugofix.h_g)  | Has additional verb routines for game debugging. |
