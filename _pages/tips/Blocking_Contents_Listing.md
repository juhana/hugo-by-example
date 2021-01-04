---
title: Blocking Contents Listing
permalink: /properties/blocking-contents-listing/
categories: 
  - Tips
---

[**list_contents**](/properties/list_contents) is a [property](/properties) which is defined
by the [standard library](standard_library).

One of the problems I've had is that containers are all-too happy to
describe their contents to anyone who would listen. This might be OK,
but looks awkward if a character says something like, "There's a head in
the box!" and Hugo describes the room with something like this:

>There is a box here. In the box is a head.

Overriding list_contents can help. We can skip contents-listing, unless
the container is being specifically looked at. For instance:

    object cauldron "cauldron"
    {
       noun "cauldron"
       in CauldronRoom
       is container, open
       list_contents
       {
          ! Skip contents-listing if not looking specifically inside
          if verbroutine ~= &DoLookIn
          {
               return 1
          }
          else
          {
                return 0
          }
       }
    }

    object oysters "oysters"
    {
       noun "oysters"
       is plural
       in cauldron
    }
