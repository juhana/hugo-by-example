---
title: parse_rank
permalink: /properties/parse_rank/
categories: 
  - Properties
  - Parsing
---

**parse_rank** is a [property](property) defined by the
[standard library](standard_library).

## Explanation

The `parse_rank` property is one of the simpler
[object](object) properties, in that it only holds a number.
Among several objects with similar names, the one with the highest
`parse_rank` value will be automatically referred to if the player
enters an ambiguous command. On the other hand, if all `parse_rank`s are
equal, the player will get something like this:

>&gt;x field  
>Which field do you mean, the baseball field, the right fielder, or the
center fielder?
>
>&gt;

So, in the above example, we'd give the baseball field object a higher
`parse_rank`. Pretty simple, right? Players will still be able to refer
to these objects when they type out the full names; we're mainly worried
about short, ambiguous commands.

## Examples

We can fine-tune things even further by returning different values
depending on the [verbroutine](verbroutine) being used.

### *Kent Tessman's Guilty Bastards*

    room nationalblvd "National Boulevard"
    {
    !   nouns "blvd", "boulevard"
    !   adjectives "national"
        nouns "blvd", "boulevard", "apartment", "building", "complex"
        adjectives "national", "cindy", "painter's", "cindy's", "apartment"
        parse_rank
        {
            if verbroutine = &DoDriveTo
                return 5
            else
                return -1
        }
    !  ....  rest of object
    }

### *Christopher Tate's conversation library*

    ! here we have a Topic class that we only want referable when the player uses our
    ! "change topic" command
    class Topic
    {
        type topic
        is hidden, container, openable, not open
        is transparent                              ! so you can 'see' subtopics
        is known                                    ! so you can ask about it
        exclude_from_all true

        parse_rank
        {
            ! prefer Topic objects over similarly-named 'tangible'
                    ! objects when parsing >TOPIC obj
            if verbroutine = &DoTopic : return 1
            else : return -1          ! 0 is the default parse_rank;
                                              ! we defer to all non-topic objects like this
        }
    }
