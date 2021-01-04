---
title: PropertyList
permalink: /routines/propertylist/
categories: 
  - Routines
---

| calling form | description |
|--------------|-------------|
| `PropertyList(object, property[, article])` | lists all the objects in `<object>.<property>`, returning the number of objects printed; if `<article>` is false or omitted, the indefinite article is used |

If an object's property comprises of pointers to various objects, it'll
print the names of all of the objects in a nice list (if it doesn't
point to objects, it'll still execute; it just won't be as pretty) and
then returns the total number.

## The Code Itself

    routine PropertyList(obj, prop, artic)
    {
        local a, b, n, total

        for (a=1; a<=obj.#prop; a++)
        {
            if obj.prop #a:  total++
        }

        for (a=1; a<=obj.#prop; a++)
        {
            b = obj.prop #a
            if b
            {
                if artic
                    The(b)
                else
                    Art(b)

                if a < total and total > 2
                    print ", ";
                elseif a = total - 1:  print " ";

                if a = total - 1
                    print AND_WORD; " ";
                n++
            }
        }
        return n
    }

## Usage

Alright, let's just throw together an example using an object's
[found_in](Found_in) property (although it might be more
useful for some custom property).

    room endofroad "End of the Road"
    {
          e_to other_end
    }

    room other_end "Other End of the Road"
    {
          w_to endofroad
    }

    scenery asphalt "asphalt"
    {
          article "the"
          found_in endofroad other_end
    }

    routine FoundInWhere(obj)
    {
        local a
        print capital Art(obj) ; " is found in ";
        a = PropertyList(obj, found_in) ! prints list, if there are elements
        if not a
            print "no rooms";
        print ". It has "; number a ; " element";
        if a ~= 1
            "s";
        "."
    }

Calling `FoundInWhere(asphalt)` would give us:

>The asphalt is found in End of the Road and Other End of the Road. It has 2 elements.

So yes, that is how that works.
