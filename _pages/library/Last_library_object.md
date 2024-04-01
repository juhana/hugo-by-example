---
title: last_library_object
permalink: /library/last_library_object/
categories: 
  - Hugo Library
---

The last_library_object, in theory, is the last object before actual game objects (your rooms, characters, etc.) are defined.  Of course, this might not be technically correct if additional object-declaring libraries are included after Hugo's default libraries (or Roodylib).  If that is the case, you might want to [replace](guts/replace) last_library_object again between the last of the library inclusions and your game code.
