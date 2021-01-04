---
title: Character Classes
permalink: /classes/character-classes/
categories: 
  - Classes
---

[Objlib](Objlib) defines the `character` and
`female_character` classes as such:

    class character
    {
        type character
        pronouns "he", "him", "his", "himself"
        capacity 50
        holding 0
        is living, transparent, static
    }

    class female_character
    {
        type female_character
        pronouns "she", "her", "her", "herself"
        capacity 50
        holding 0
        is living, transparent, static, female
    }
