---
title: contains_desc
permalink: /properties/contains_desc/
categories: 
  - Properties
---

Text within an object's `contains_desc` property replaces the "Inside
the <container> is " or "<character> is holding " default text usually
provided by [WhatsIn](routines/whatsin/) (well, the &WhatsIn case
provided by the [Message](basics/messages/) routine, to be exact). It
also has the benefit of only being printed when there *are* items to be
listed. Here are some usage examples:

    object hook "coat hook"
    {
       article "the"
       adjective "coat"
       noun "hook"
       contains_desc
          "Hanging on the hook is"; ! notice the lack of space at the end (and the semicolon)
       is platform
       capacity 100
       holding 0
    }

Here is one from [the Hugo Book](hugo/hugo-book/):

    object woodcabinet "wooden cabinet"
    {
       in emptyroom
       article "a"
       nouns "cabinet", "shelf", "shelves", \
          "furniture", "doors", "door"
       adjectives "wooden", "wood", "fine", "mahogany"
       short_desc
          "A wooden cabinet sits along one wall."
       when_open
          "An open wooden cabinet sits along
          one wall."
       long_desc
          {
          "The cabinet is made of fine mahogany wood,
          hand-crafted by a master cabinetmaker. In
          front are two doors (presently ";
          if self is open
             print "open";
          else: print "closed";
          print ")."
          }
       contains_desc
          "Behind the open doors of the cabinet you
          can see"; ! note semicolon--
                    ! no line feed
       key_object cabinetkey ! a cabinetkey object
                             ! must also be created
       holding 0 ! starts off empty
       capacity 100
       before
          {
          object DoLookUnder
             {"Nothing there but dust."}
          object DoGet
             {"The cabinet is far too heavy
              to lift!"}
          }
       after
          {
          object DoLock
             {"With a twist of the key, you lock the
              cabinet up tight."}
          }
       is container, openable, not open
       is lockable, static
    }

So yeah, for containers, platforms, or characters, when you want that
extra bit of style, `contains_desc` is your guy!
