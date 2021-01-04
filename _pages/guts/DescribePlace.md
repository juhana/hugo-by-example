---
title: DescribePlace
permalink: /guts/describeplace/
categories: 
  - Hugo Guts
---

`DescribePlace` is a [hugolib.h](library/hugolib.h/)-defined
[routine](routines/) that describes a room and lists its
contents. It is called when the player types &gt;LOOK or enters a room
for the first time (if they aren't in SUPERBRIEF mode). Having some
familiarity with `DescribePlace` is important for understanding the
order of things listed (especially if you are looking to change that
order up).

## The code

    !----------------------------------------------------------------------------
    ! DescribePlace(location, [optional parameter])
    ! prints the location name, followed by the location description, if
    ! required
    !
    ! DescribePlace(location, true)
    ! forces a location description

    routine Describeplace(place, long)
    {
       local obj, count, notlisted, tempformat

       parser_data[PARSER_STATUS] &= ~PRONOUNS_SET

       ! Since, for example, a room description following entering via
       ! DoGo does not trigger before/after properties tied to looking
       ! around:
       !
    #ifclear NO_VERBS
       if verbroutine ~= &DoLookAround
       {
          if place is not visited and verbosity ~= 1
             return Perform(&DoLookAround)
          elseif long = true or verbosity = 2
             return Perform(&DoLookAround)
       }
    #endif

       if not light_source
       {
          Message(&DescribePlace, 1)     ! "It's too dark to see..."
          return
       }

       place is known

       ! Print the name of the location as a heading
       Font(BOLD_ON)
       print "\n"; capital place.name;

       ! Print ", in <something>" if necessary
       if location = place and player not in place
       {
          if parent(player).prep
             print ", "; parent(player).prep; " ";
          elseif parent(player) is platform
             print ", "; ON_WORD; " ";
          else
             print ", "; IN_WORD; " ";
          print Art(parent(player))
       }
       print newline

       Font(BOLD_OFF)
       override_indent = false

       if place is not visited and verbosity ~= 1
       {
          if &place.initial_desc or &place.long_desc
             Indent
          if not place.initial_desc
             run place.long_desc
       }
       elseif long = true or verbosity = 2
       {
          if &place.long_desc
             Indent
          run place.long_desc
       }

       if &place.list_contents and FORMAT & DESCFORM_F
          print ""        ! for double-space-after-heading formatting

       ! A location may contain an overriding listing routine, as may any
       ! parent, in the list_contents property
       !
       if not place.list_contents
       {
          list_nest = 0

          ! For double-space-after-heading formatting:
          if FORMAT & DESCFORM_F
          {
             for obj in place
             {
                if obj is not hidden and
                   (player not in obj or children(obj) > 1)
                {
                   print ""
                   break
                }
             }
          }

          ! List contents of chair, vehicle, etc. player is in
          if player not in location
          {
             list_nest = 1
             WhatsIn(Parent(player))
          }

          ! List all characters, if any
          count = 0
          for obj in place
          {
             if obj is hidden or obj is not living or
                player in obj
             {
                obj is already_listed
             }
             else
             {
                obj is not already_listed
             }
          }
          for obj in place
          {
             if obj is not already_listed
             {
                print newline
                ShortDescribe(obj)
                if obj is not already_listed
                   count++
             }
          }

          list_count = count
          count = 0

          if list_count           ! if characters are to be listed
          {
             tempformat = FORMAT
             FORMAT = FORMAT | FIRSTCAPITAL_F | ISORAREHERE_F
             FORMAT = FORMAT | USECHARNAMES_F
             if FORMAT & LIST_F
             {
                FORMAT = FORMAT & ~LIST_F       ! clear it
                FORMAT = FORMAT | TEMPLIST_F
             }
             Indent
             list_nest = 0
             ListObjects(place)
             FORMAT = tempformat
          }

          for obj in place
          {
    #ifset USE_ATTACHABLES
             ! Exclude all attachables for now (and characters)

             if obj is living or obj.type = attachable or
                player in obj
    #else
             if obj is living or player in obj
    #endif
                obj is already_listed
             else
                obj is not already_listed
          }

          for obj in place
          {
    #ifset USE_PLURAL_OBJECTS
             ! ...And don't list identical objects yet, either

             if (obj.identical_to).type = identical_class
             {
                if obj is not hidden
                   count++
             }
             elseif player not in obj
    #else
             if player not in obj
    #endif
             {
                if obj is not already_listed and
                   obj is not hidden
                {
                   ShortDescribe(obj)
                   if obj is not already_listed
                      notlisted++
                }
             }
          }

          if notlisted or count
          {
             list_count = notlisted + count
             tempformat = FORMAT
             FORMAT = FORMAT | FIRSTCAPITAL_F | ISORAREHERE_F
             if FORMAT & LIST_F
             {
                FORMAT = FORMAT & ~LIST_F       ! clear it
                FORMAT = FORMAT | TEMPLIST_F
             }
             Indent
             list_nest = 0
             ListObjects(place)
             FORMAT = tempformat
          }

    #ifclear NO_OBJLIB
    #ifset USE_ATTACHABLES
          for obj in place
          {
             ! Print attachables last
             if obj.type = attachable and obj is not hidden
             {
                ShortDescribe(obj)
                if obj is not already_listed
                   Message(&DescribePlace, 2, obj)
             }
          }
    #endif

          print newline
          override_indent = false

          ! Finally, list contents of scenery objects (unless we've
          ! already done so as the parent of the player)
          !
          for obj in place
          {
             if obj.type = scenery
             {
                obj is known
                if player not in obj and
                   (obj is open or obj is not openable)
                {
                   list_nest = 1
                   WhatsIn(obj)
                }
             }

             ! For scenery-derived objects that may change the type
             elseif obj is static, hidden
                obj is known
          }
    #endif  ! ifclear NO_OBJLIB

          print newline
          need_newline = false

       }
    }

## Hugo Homework

Generalizing here, but everyone comes to a point where they need to
tweak `DescribePlace` for something sometime. If you're dying to get in
on the action, try these things:

-   If the player has the game in SUPERBRIEF mode, room
    [initial_desc](properties/descriptions/#initial_desc) properties are skipped
    completely. This could be troublesome if important information is
    there. Tweak `DescribePlace` so they are run anyways.
-   Even in SUPERBRIEF mode, room contents' full
    [short_desc](properties/descriptions/) properties are printed. Tweak
    `DescribePlace` so it treats those objects like they have no
    `short_desc` property.
-   Robb Sherwin's characters never have `short_desc`. Tweak
    `DescribePlace` so characters without `short_desc`'s are listed
    last, after everything else.
