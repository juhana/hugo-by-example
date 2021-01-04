---
title: Reserved Words
permalink: /basics/reserved-words/
categories: 
  - Basics
---

"Reserved words" are words already defined by the 
[Hugo engine](interpreters/he/) or the [standard library](library/);
therefore, they can't be used as
names of new objects or [variables](basics/variables/) or what have
you. One can get a basic idea of reserved words by looking at syntax
files for [text editors](tools/editors/), but this page
will try to provide a mostly-complete list.

### General reserved words

routine print return true false object property higher if and or not
parent sibling child younger youngest elder children in nearby move to
remove attribute alias object xobject class inherits replace global
local constant enumerate locate is number array string dict for select
case else elseif while do random break jump run event scriptdata
setscript nothing verb held notheld multiheld multinotheld word removal
punctuation synonym words \~and \~any \~all \~except \~oops verbroutine
window save restore writefile writeval readfile readval resource picture
sound music anything call capital cls color colour eldest hex input
multi parse$ pause playback printchar quit recordoff recordon restart
restore run runevents scriptoff scripton serial$ system text undo xverb

### Preprocessor commands

\#switches \#version \#include \#set \#clear \#if \#ifset \#endif
\#ifclear \#message \#else \#link \#elseif set clear $MAXDICTEXTEND

### Library classes

daemon fuse room door scenery vehicle character female_character
player_character component plural_class identical_class
remote_object plural_class component direction display

### Library properties

screenheight screenwidth linelength windowlines cursor_column
cursor_row statusline_height title_caption name before between after
timer tick noun adjective article nouns noun adjectives adjective
preposition prep pronoun pronouns react_before react_after short_desc
initial_desc long_desc found_in type size capacity holding reach
list_contents in_scope parse_rank exclude_from_all door_to n_to
ne_to e_to se_to s_to sw_to w_to nw_to u_to d_to in_to out_to
cant_go extra_scenery each_turn key_object when_open when_closed
ignore_response order_response contains_desc inv_desc desc_detail
misc

### Library attributes

known moved visited static plural living female openable open lockable
locked unfriendly light readable switchable switchedon clothing worn
mobile enterable container platform hidden quiet transparent workflag
already_listed special

### Library globals

self words player actor location verbroutine endflag prompt objects
system_status player_person MAX_SCORE FORMAT DEFAULT_FONT STATUSTYPE
UNDO_OFF counter score verbosity list_nest light_source event_flag
speaking old_location last_object obstacle list_count need_newline
override_indent best_parse_rank customerror_flag number_scripts
MAX_RANK it_obj them_obj him_obj her_obj general TEXTCOLOR BGCOLOR
SL_TEXTCOLOR SL_BGCOLOR INPUTCOLOR INVENTORY_MASK MENU_TEXTCOLOR
MENU_BGCOLOR MENU_SELECTCOLOR MENU_SELECTBGCOLOR defined undefined

### Library constants

INDENT_SIZE AFTER_PERIOD FILE_CHECK BOLD_ON BOLD_OFF ITALIC_ON
ITALIC_OFF UNDERLINE_ON UNDERLINE_OFF PROP_ON PROP_OFF UP_ARROW
DOWN_ARROW LEFT_ARROW RIGHT_ARROW ESCAPE_KEY ENTER_KEY MOUSE_CLICK
AND_WORD ARE_WORD HERE_WORD IN_WORD IS_WORD ON_WORD LIST_F
NORECURSE_F NOINDENT_F DESCFORM_F GROUPPLURALS_F NOPARENTHESES_F
INVENTORY_F FIRSTCAPITAL_F ISORARE_F ISORAREHERE_F USECHARNAMES_F
TEMPLIST_F PARSER_RESET PARSER_ACTIVE PRONOUNS_SET FINDOBJECT_KNOWN
FINDOBJECT_NONLIVING PERFORM_QUEUE BLACK BLUE GREEN CYAN RED MAGENTA
BROWN WHITE DARK_GRAY LIGHT_BLUE LIGHT_GREEN LIGHT_CYAN LIGHT_RED
LIGHT_MAGENTA YELLOW BRIGHT_WHITE MAX_WORDS BANNER HUGO_VERSION
PARSER_STATUS LAST_PARSER_STATUS BEST_PARSE_RANK PARSE_RANK_TESTS
LAST_SINGLE_OBJECT VERB_IS_XVERB MAX_SCRIPTS MAX_SCRIPT_STEPS
DEF_FOREGROUND DEF_BACKGROUND DEF_SL_FOREGROUND DEF_SL_BACKGROUND
MATCH_FOREGROUND