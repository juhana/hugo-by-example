---
title: remote_object
permalink: /scope/remote_object/
categories: 
  - Scope
  - Classes
---

A `remote_object` is a [class](Object_Classes) written by
Kent Tessman for his game, Future Boy! It is used for objects that can
be interacted with in one room but only seen from other rooms (like, for
instance, a flagpole). This code is shared according to the terms of
[its license](Future_Boy_Selected_Source_License).


    property real_object alias misc  ! object remote_object is the remote twin of

    scenery remote_object
    {
        type remote_object
        real_object nothing
        long_desc
            return self.real_object.long_desc
        before
        {
            object DoLook
            {
                return false
            }
            object DoGo
            {
                "Which way do you want to go?"
            }
            object
            {
                "You can't do that from here."
            }
            xobject
            {
                "You can't do that from here."
            }
        }
        parse_rank -1   ! a parse_rank of -1 puts it definitely out of the
                ! running unless there's no other possible object
                ! present
    }
