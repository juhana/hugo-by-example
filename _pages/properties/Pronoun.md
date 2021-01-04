---
title: pronoun
permalink: /properties/pronoun/
categories: 
  - Properties
---

`Pronouns` make general-purpose game responses for characters possible.
Take, for instance, the following response for `DoHit`:

        case &DoHit:  print "Venting "; player.pronoun #3; " frustrations
                on "; The(object); " won't accomplish much."

The word after "Venting" will be "your", "my", "his", "her", or "its",
depending on what person the game is told in (and which applicable set
of pronouns the player object has). The `pronoun` property is
[aliased](/basics/alias/) by the `pronouns` property.

A properly-filled pronoun property will have four elements:

## More examples

| Object                 | Pronoun Element \#1 | Pronoun Element \#2 | Pronoun Element \#3 | Pronoun Element \#4 |
|------------------------|---------------------|---------------------|---------------------|---------------------|
| player (first person)  | "I"                 | "me"                | "my"                | "myself"            |
| player (second person) | "you"               | "you"               | "your"              | "yourself"          |
| male character         | "he"                | "him"               | "his"               | "himself"           |
| female character       | "she"               | "her"               | "her"               | "herself"           |
| non-gendered character | "it"                | "it"                | "its"               | "itself"            |
