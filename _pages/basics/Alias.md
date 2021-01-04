---
title: Alias
permalink: /basics/alias/
categories: 
  - Basics
  - Declarations
---

The **alias** parameter informs the compiler that a named
[property](properties/) or [attribute](attributes/) is
the same as another one, it is used to give an additional name for an
existing defined [identifier](definitions/identifier/).

Because of limits on the number of [attributes](attributes/)
(128) and [properties](properties/) (default 256), and because
the Hugo standard library uses more than 20 attributes, and more than 30
properties, the Hugo language includes the ability to make an *alias*
between a new attribute/property and an existing one. This allows you to
use a meaningful name in place of using a pre-defined attribute or
property in a non-standard way.

For example, the `visited` attribute is aliased to the `moved`
attribute. Both of these attributes are really the same one, as far as
the compiler is concerned. Objects may be moved, but rooms cannot, so
instead of taking up another attribute for *visited*, it is aliased (or
another name given) to *moved*.

To make an alias of your own, just use:

**`attribute`**` `<new attribute>` `**`alias`**` `<existing attribute>
for attributes and

**`property`**` `<new property>` `**`alias`**` `<existing property> for
properties.

Let's take a look at this in action. In this game, a
[character](characters/) can be a super hero or a normal
person. We'll create an attribute called **super**. If a character has
this attribute, they are a super hero, otherwise just a normal person.
Looking through the standard library, we can see the pre-defined
attributes. Now, we pick one to alias our **`super`** attribute to.
We'll use **`enterable`** in this case, because people generally are not
*enterable*. (that is, you usually do not enter a person \[except in
pornographic adventures, and we're not going to go there!\]).

    ! [code here]
    ! somewhere at the top of the file
    attribute super alias enterable

    ! [more code here]

    character seerman "The Seer"
    {
        names "seer", "man"
        adjectives "seer", "hero"

        is super
    !   [more character stuff here]

    }

See Also: [attribute](attributes/),
[property](properties/),
[declarations](declarations/), [keywords](guts/keywords/)
