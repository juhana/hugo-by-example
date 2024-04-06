---
title: last_library_object
permalink: /library/last_library_object/
categories: 
  - Hugo Library
---

The last_library_object, in theory, is the last object before actual game objects (your rooms, characters, etc.) are defined.  Of course, this might not be technically correct if additional object-declaring libraries are included after Hugo's default libraries (or Roodylib).  If that is the case, you might want to [replace](guts/replace) last_library_object again between the last of the library inclusions and your game code.

In the standard Hugo library, the last_library_object is only declared if the game is compiled with the SET_DEBUG flag, and it is only used by the Hugofix command for checking which objectsin the game do not have an artile ("the","an") defined.

Still, it's kind of a useful trick that one may want to use all of the time (in which case you would want to declare it yourself after all of the libraries have been included).  It is not too unusual to use a [for loop](loops/for) to check every object in the game for something, whether it be objects of a certain class or objects in particular locations.  Starting the loop variable at values higher than the last_library_object ensures that you don't get a false positive from any of the library objects.
