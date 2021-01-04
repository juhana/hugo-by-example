---
title: Replace AssignPronoun
permalink: /replacements/assignpronoun/
categories: 
  - Replacements
---

### What it fixes

Normally, [AssignPronoun](parsing/assignpronoun/) gives non-gendered
living things like animals. This version will set the "it" pronoun
(assuming the animal object's [pronouns](properties/pronoun/) are set
correctly).

### The code

    replace AssignPronoun(obj)
    {
    #ifclear OLD_STYLE_PRONOUNS
        if obj >= it_object and obj <= them_object
            return
    #endif
        if parser_data[PARSER_STATUS] & PRONOUNS_SET:  return
        if obj = player:  return

        ! No use if you can't refer to it
        if not obj.#noun and not obj.#adjective
            return

        if obj is not living
        {
            if obj is not plural
                it_obj = obj
            else
                them_obj = obj
        }
        else
        {
            if obj is plural
                them_obj = obj
            elseif obj is female
                her_obj = obj
            elseif (obj.pronouns #2) = "it"
                it_obj = obj
            else
                him_obj = obj
        }
    }
