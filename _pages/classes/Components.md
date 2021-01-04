---
title: Components
permalink: /classes/components/
categories: 
  - Classes
---

| From *objlib.h*                                                                                                                                                                                                                                                                                                                       |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Components are essentially movable scenery objects, which are considered to be attached to another object. The part_of property is initialized with the object of which the new object is a component. Note that children of components are not listed in the room description; their children are, however, listed when directly examining the object. |

# components (object [class](/basics/object_classes/))

`Components`, simply enough, are objects that are *part of* another
object. The way this is handled is not through some kind of container or
platform modeling. Instead, it involves a bit of
[scope](/scope/) trickery. Let's take a look at the code:

    property part_of alias found_in

    class component
    {
        type component
        part_of nothing

    #ifclear NO_VERBS
        before
        {
            object DoGet, DoDrop, DoPutIn
            {
                OMessage(component)     ! "You can't separate that..."
            }
        }
        after
        {
            xobject DoAsk, DoTell
            {
                return Perform(verbroutine, object, self.part_of)
            }
            object DoShow, DoGive
            {
                return Perform(verbroutine, self.part_of, xobject)
            }
        }
        exclude_from_all
        {
            if verbroutine = &DoGet
                return true
            else
                return false
        }
    #else
        exclude_from_all
            return false
    #endif
        is static, hidden
    }

The `component` class uses the `part_of`
[property](/properties/), which is just an
[alias](/basics/alias/) of [found_in](/scope/found_in/). Like all
[found_in](/scope/found_in/) objects, this means that the component
object is not in the same room as its "parent" object according to the
[object tree](/basics/object_tree), but it is accessible wherever
that object may be. As you can see above, it also has code to redirect
certain commands to that "parent" object.

## An example

    object clock "grandfather clock"
    {
        article "the"
        adjective "grandfather"
        noun "clock"
        article "the"
        long_desc
            "The grandfather clock consists of a clock face and a clock mantel."
    in study
    }

    component clockface "clock face"
    {
        part_of clock
        article "the"
        adjective "clock"
        noun "face"
    }

    component clockmantel "clock mantel"
    {
        part_of clock
        article "the"
        adjective "clock"
        noun "mantel"
        is platform
    }

    object mice "three blind mice"
    {
        adjective "three" "blind"
        article "the"
        noun "mice"
        is plural
        in clockmantel
    }

This gives us:

>&gt;x clock  
>The grandfather clock consists of a clock face and a clock mantel.
>
>&gt;x mantel  
>The clock mantel looks just like you would expect.  
>Sitting on the clock mantel are the three blind mice.
>&gt;
