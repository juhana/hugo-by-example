---
title: Replace ParseError
permalink: /replacements/parseerror/
categories: 
  - Replacements
---

### What it fixes

1.  Changes a couple responses involving non-gendered NPCs (like animals
    or creatures that will be referred to as "it").
2.  Adds some [parse$](parse$)-printing code for HugoFix
    parser monitoring (see "[replace DoHugoFix](replace_DoHugoFix)").
3.  Has some code so some "You can't \[X\] multiple objects like that."
    messages sound better (like when the player uses an abbreviated
    command like **&gt;X** for **&gt;EXAMINE**.

### The code

    replace ParseError(errornumber, obj)
    {
    #ifset DEBUG
       if debug_flags & D_PARSE
       {
          local w, p
          Font(BOLD_ON)
          if (errornumber = 0,1,16,17)  ! cases where Parse hasn't been called
             {
             for (w=1; w<=words and word[w]~=""; w++)
                {
                print "[";
                if (word[w] ~= -1)
                   print word[w];
                else
                   {
                   print "\Iparse$";
                   if p
                      print number (p+1);"*";
                   p++
                   FONT(ITALIC_OFF)
                   }
                "] ";
                }
             print newline
             if (p>1)
                {
                "(* Not an \Iactual\i referable token.)"
                }
             }
          ! this section so we print parse$ only once
          if string(_temp_string,parse$) and
             not (parser_data[PARSER_STATUS] & 32)
             {
             print "[parse$ = \""; parse$; "\"]"
             parser_data[PARSER_STATUS] |= 32
             }
          Font(BOLD_OFF)
       }
    #endif
       local r
       r = NewParseError(errornumber, obj)
       if r
       {
          parser_data[PARSER_STATUS] = PARSER_RESET
          return r
       }

       if errornumber >= 100
       {
          CustomError(errornumber, obj)
          word[1] = ""            ! force ParseError(0)
          words = 0
          customerror_flag = true
          parser_data[PARSER_STATUS] = PARSER_RESET
          return true
       }
       if customerror_flag
       {
          customerror_flag = 0    ! CustomError already printed error
          parser_data[PARSER_STATUS] = PARSER_RESET
          return true
       }

       select errornumber

          case 1
             print CThe(player); \
                ! " can't use the word \""; \
                MatchPlural(player, "doesn't", "don't"); \
                " need to use the word \""; \
                parse$; ".\""

          case 3
             {
             local a, b
              select word[1]
                case "x" : {
                            a = "examine"
                            if word[2] ~= "~all"
                               b = word[2]
                           }
                case "l","look"
                            {
                            if word[2] = "~all"
                               a = "look at"
                            else
                               a = "look"
                            if word[2] ~= "~all"
                               b = word[2]
                            }
                case "sit","lie","go","walk","watch"
                            {
                            a = word[1]
                            if word[2] ~= "~all"
                               b = word[2]
                            }
                case "get", "step"
                            {
                            a = word[1]
                            if word[2] ~= "~all"
                               {
                               if (word[2] = "outof")
                                  {
                                  b = "out of"
                                  }
                               elseif word[2] = "offof"
                                  {
                                  b = "off of"
                                  }
                               else
                                  b = word[2]
                               }
                            }
                case else : a = parse$
             print CThe(actor); " can't "; a;
             if b
                print " "; b ;
                " multiple
                objects like that."
             }

          case 5
          {
             if VerbWord = "give", "offer", "hand", "show"
             {
                print "Not sure what you're referring to--try \""; \
                   VerbWord; " (something) \Ito\i (someone)\"."
             }
             else
             {
    !\
                print CThe(player); \
                   MatchPlural(player, "hasn't", "haven't");
                   print " seen any";
    #ifset OLD_STYLE_PRONOUNS
                   ! If we built an object phrase using
                   ! OLD_STYLE_PRONOUNS, avoid printing a
                   ! potential nonsense name:
                   if parser_data[PARSER_STATUS] & PRONOUNS_SET
                      print "thing like that";
                   else
    #endif
                      print " \""; parse$; "\"";
                   print ", nor"; IsorAre(player, true); " "; The(player); \
                   " likely to, even if such a thing exists."
    \!
                print CThe(player); \
                   MatchPlural(player, "hasn't", "haven't");
                   print " encountered any";
    #ifset OLD_STYLE_PRONOUNS
                if parser_data[PARSER_STATUS] & PRONOUNS_SET
                   print "thing like that";
                else
    #endif
                   print " \""; parse$; "\"";
                print ".";
                print "  (If you're sure you need to refer to that, try
                   putting it another way.)"
             }
          }
          case 6
             print "That doesn't make any sense."

          case 9
          {
             print "Nothing to ";
             if verbroutine
                print parse$; "."
             else:  print "do."
          }

          case 10
          {
             print CThe(player); \
             MatchPlural(player, "hasn't", "haven't");
             if &obj.long_desc
                " seen ";
             else
                " encountered ";
             if obj is living and not (parser_data[PARSER_STATUS] & FINDOBJECT_NONLIVING) and obj.pronoun #2 ~= "it"
                print "anybody";
             else: print "anything";
             print " like that";
    #ifset DEBUG
             if (debug_flags & D_OBJNUM)
                print " ; number obj; ?";
    #endif
             print "."
          }

          case 11
          {
             if not ParseError_ObjectIsKnown(obj)
             {
                ParseError(10, obj)
             }
             elseif obj is living
             {
    !\
                print CThe(obj); \
                   MatchPlural(obj, "isn't", "aren't"); " here."
    \!
                print CThe(actor); \
                   MatchPlural(actor, "doesn't", "don't"); \
                   " see";
                if (obj.pronouns #2)
                   print " "; obj.pronouns #2;
                elseif obj is plural
                   " them";
                elseif obj is female
                   " her";
                else
                   " him";
    #ifset DEBUG
                if (debug_flags & D_OBJNUM)
                   print " ["; number obj; "]";
    #endif
                print "."
             }
             else
             {
    #ifset USE_CHECKHELD
                if verbroutine = &DoDrop_CheckHeld, &DoPutIn_CheckHeld,
                   &DoPutonGround_CheckHeld
                {
                   ParseError(15, obj)
                }
                else
                {
    #endif
                   print CThe(actor); \
                      MatchPlural(actor, "doesn't", "don't"); \
                      " see that"; ! MatchPlural(obj, "that", "those");
    #ifset DEBUG
                   if (debug_flags & D_OBJNUM)
                      print " ["; number obj; "]";
    #endif
                   print "."
    #ifset USE_CHECKHELD
                }
    #endif
             }
          }

          case 12
          {
             if not ParseError_ObjectIsKnown(obj)
             {
                ParseError(10, obj)
             }
             else
             {
                print CThe(actor); \
                   " can't do that with "; TheOrThat(obj) ; "."
             }
          }
          case 13
             print "You'll have to be a little more specific."

          case 14
          {
             if not ParseError_ObjectIsKnown(obj)
             {
                ParseError(10, obj)
             }
             elseif xobject is living
             {
                print CThe(xobject); \
                   MatchPlural(xobject, "doesn't", "don't"); \
                   " have "; TheOrThat(obj); "."
             }
             else
             {
                print CThe(actor); \
                   MatchPlural(actor, "doesn't", "don't"); \
                   " see "; TheOrThat(obj); " there."
             }
          }

          case 15
          {
             if not ParseError_ObjectIsKnown(obj)
             {
                ParseError(10, obj)
             }
             elseif obj = player
             {
                ParseError(12, obj)
             }
             else
             {
                print CThe(actor); IsorAre(actor); " not
                   holding"; MatchPlural(obj, "that", "those"); "."
             }
          }

          case else
          {
             parser_data[PARSER_STATUS] = PARSER_RESET
             return false            ! print the default message
          }

       parser_data[PARSER_STATUS] = PARSER_RESET
       return true                             ! message already printed
    }
