/* Copyright (C) 1991-2021 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */

/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */

/* See LICENSE file for copyright and license details. */

/* appearance */

#include <X11/XF86keysym.h>
#include "patches.h"

#define ICONSIZE 20   /* icon size */
#define ICONSPACING 5 /* space between icon and title */

#define SPWN(x) {.v = x}

#define STATUSBAR "dwmblocks"
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const unsigned int borderpx = 1; /* border pixel of windows */

static const unsigned int snap = 32; /* snap pixel */

static const int swallowfloating = 0; /* 1 means swallow floating windows by default */

static const char autostartblocksh[] = "autostart_blocking.sh";
static const char autostartsh[] = "autostart.sh";
static const char dwmdir[] = "dwm";
static const char localshare[] = ".local/share";

static const int showbar = 1; /* 0 means no bar */

static const int topbar = 1; /* 0 means bottom bar */

/* Status is to be shown on: -1 (all monitors), 0 (a specific monitor by index), 'A' (active monitor) */

static const int statusmon = 'A';

static const char buttonbar[] = "<O>";

static const unsigned int systrayspacing = 2; /* systray spacing */
static const int showsystray = 1;             /* 0 means no systray */

/* Indicators: see patch/bar_indicators.h for options */
static int tagindicatortype = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype = INDICATOR_NONE;
static int floatindicatortype = INDICATOR_TOP_LEFT_SQUARE;

static int fakefsindicatortype = INDICATOR_PLUS;
static int floatfakefsindicatortype = INDICATOR_PLUS_AND_LARGER_SQUARE;

static const char *fonts[] = {"monospace:size=10", "Noto Color Emoji:pixelsize=15:antialias=true:autohint=true"};

// static const char dmenufont[] = "Fira Code:size=14";

static char c000000[] = "#000000"; // placeholder value

static char normfgcolor[] = "#44475a"; 
static char normbgcolor[] = "#222222"; 
static char normbordercolor[] = "#444444"; 
static char normfloatcolor[] = "#db8fd9"; 

static char selfgcolor[] = "#eeeeee"; 
static char selbgcolor[] = "#005577"; 
static char selbordercolor[] = "#005577"; 
static char selfloatcolor[] = "#005577"; 

static char titlenormfgcolor[] = "#bbbbbb"; 
static char titlenormbgcolor[] = "#222222"; 
static char titlenormbordercolor[] = "#444444"; 
static char titlenormfloatcolor[] = "#db8fd9"; 

static char titleselfgcolor[] = "#eeeeee"; 
static char titleselbgcolor[] = "#005577"; 
static char titleselbordercolor[] = "#005577"; 
static char titleselfloatcolor[] = "#005577"; 

static char tagsnormfgcolor[] = "#bbbbbb"; 
static char tagsnormbgcolor[] = "#222222"; 
static char tagsnormbordercolor[] = "#444444"; 
static char tagsnormfloatcolor[] = "#db8fd9"; 

static char tagsselfgcolor[] = "#eeeeee"; 
static char tagsselbgcolor[] = "#005577"; 
static char tagsselbordercolor[] = "#005577"; 
static char tagsselfloatcolor[] = "#005577"; 

static char hidnormfgcolor[] = "#005577"; 
static char hidselfgcolor[] = "#227799"; 
static char hidnormbgcolor[] = "#222222"; 
static char hidselbgcolor[] = "#222222"; 

static char urgfgcolor[] = "#bbbbbb"; 
static char urgbgcolor[] = "#222222"; 
static char urgbordercolor[] = "#ff0000"; 
static char urgfloatcolor[] = "#db8fd9"; 

xrdb(NULL);

static char *colors[][ColCount] = {
    /*                       fg                bg             border                float */
    //{"#ff0000", "ffffff", "$00008F"},
    [SchemeNorm] = {normfgcolor, normbgcolor, selbgcolor, normfloatcolor},
    [SchemeSel] = {normfgcolor, selbgcolor, selbordercolor, selfloatcolor},
    [SchemeTitleNorm] = {normfgcolor, normbgcolor, normbordercolor, titlenormfloatcolor},
    [SchemeTitleSel] = {normfgcolor, selbgcolor, selbordercolor, titleselfloatcolor},
    [SchemeTagsNorm] = {selfgcolor, selfgcolor, normbordercolor, tagsnormfloatcolor},
    [SchemeTagsSel] = {selfgcolor, selfgcolor, selbordercolor, tagsselfloatcolor},
    [SchemeHidNorm] = {hidnormfgcolor, hidnormbgcolor, c000000, c000000},
    [SchemeHidSel] = {hidselfgcolor, hidselbgcolor, c000000, c000000},
    [SchemeUrg] = {urgfgcolor, urgbgcolor, urgbordercolor, urgfloatcolor},

};

static const char *layoutmenu_cmd = "layoutmenu.sh";

static const char *const autostart[] = {
    // "st", NULL,
    /* "brave", NULL, */
    NULL /* terminate */
};

const char *spcmd1[] = {"st", "-n", "spterm", NULL};
static Sp scratchpads[] = {
    /* name          cmd */
    {"spterm", spcmd1},
};

/* Tags
 * In a traditional dwm the number of tags in use can be changed simply by changing the number
 * of strings in the tags array. This build does things a bit different which has some added
 * benefits. If you need to change the number of tags here then change the NUMTAGS macro in dwm.c.
 *
 * Examples:
 *
 *  1) static char *tagicons[][NUMTAGS*2] = {
 *         [DEFAULT_TAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F", "G", "H", "I" },
 *     }
 *
 *  2) static char *tagicons[][1] = {
 *         [DEFAULT_TAGS] = { "•" },
 *     }
 *
 * The first example would result in the tags on the first monitor to be 1 through 9, while the
 * tags for the second monitor would be named A through I. A third monitor would start again at
 * 1 through 9 while the tags on a fourth monitor would also be named A through I. Note the tags
 * count of NUMTAGS*2 in the array initialiser which defines how many tag text / icon exists in
 * the array. This can be changed to *3 to add separate icons for a third monitor.
 *
 * For the second example each tag would be represented as a bullet point. Both cases work the
 * same from a technical standpoint - the icon index is derived from the tag index and the monitor
 * index. If the icon index is is greater than the number of tag icons then it will wrap around
 * until it an icon matches. Similarly if there are two tag icons then it would alternate between
 * them. This works seamlessly with alternative tags and alttagsdecoration patches.
*/ 
static char *tagicons[][NUMTAGS] = {
    [DEFAULT_TAGS] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"},
    [ALTERNATIVE_TAGS] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"},
    [ALT_TAGS_DECORATION] = {"<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>"},
};

/* There are two options when it comes to per-client rules:
 *  - a typical struct table or
 *  - using the RULE macro
 *
 * A traditional struct table looks like this:
 *    // class      instance  title  wintype  tags mask  isfloating  monitor
 *    { "Gimp",     NULL,     NULL,  NULL,    1 << 4,    0,          -1 },
 *    { "Firefox",  NULL,     NULL,  NULL,    1 << 7,    0,          -1 },
 *
 * The RULE macro has the default values set for each field allowing you to only
 * specify the values that are relevant for your rule, e.g.
 *
 *    RULE(.class = "Gimp", .tags = 1 << 4)
 *    RULE(.class = "Firefox", .tags = 1 << 7)
 *
 * Refer to the Rule struct definition for the list of available fields depending on
 * the patches you enable.
 */
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     *	WM_WINDOW_ROLE(STRING) = role
     *	_NET_WM_WINDOW_TYPE(ATOM) = wintype
     */
    RULE(.wintype = WTYPE "DIALOG", .isfloating = 1)
        RULE(.wintype = WTYPE "UTILITY", .isfloating = 1)
            RULE(.wintype = WTYPE "TOOLBAR", .isfloating = 1)
                RULE(.wintype = WTYPE "SPLASH", .isfloating = 1)
                    RULE(.class = "Gimp", .tags = 1 << 4)
                        RULE(.class = "Firefox", .tags = 1 << 7)
                            RULE(.class = "Zotero", .isfloating = 1)
                                RULE(.class = "zoom", .isfloating = 1)
                                    RULE(.class = "keepassxc", .isfloating = 1)
                                        RULE(.class = "discord", .tags = 1 << 1)

                                            RULE(.instance = "spterm", .tags = SPTAG(0), .isfloating = 1)
                                            RULE(.instance = "flt", .isfloating = 1)
                                            RULE(.instance = "btop", .isfloating = 1)

};

static const MonitorRule monrules[] = {
    /* monitor  layout  mfact  nmaster  showbar  topbar */
    {1, 2, -1, -1, -1, -1},  // use a different layout for the second monitor
    {-1, 0, -1, -1, -1, -1}, // default
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
static const BarRule barrules[] = {
    /* monitor   bar    alignment         widthfunc                drawfunc                clickfunc                name */

    {-1, 0, BAR_ALIGN_LEFT, width_stbutton, draw_stbutton, click_stbutton, "statusbutton"},

    {0, 0, BAR_ALIGN_LEFT, width_pwrl_tags, draw_pwrl_tags, click_pwrl_tags, "powerline_tags"},

    //#if BAR_TAGS_PATCH
    //    {-1, 0, BAR_ALIGN_LEFT, width_tags, draw_tags, click_tags, "tags"},
    //#endif // BAR_TAGS_PATCH

    {0, 0, BAR_ALIGN_RIGHT, width_systray, draw_systray, click_systray, "systray"},

    {-1, 0, BAR_ALIGN_LEFT, width_ltsymbol, draw_ltsymbol, click_ltsymbol, "layout"},

    {statusmon, 0, BAR_ALIGN_RIGHT, width_status2d, draw_status2d, click_statuscmd, "status2d"},

    {-1, 0, BAR_ALIGN_NONE, width_wintitle, draw_wintitle, click_wintitle, "wintitle"},

};

/* layout(s) */
static const float mfact = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */

static const int nstack = 0; /* number of clients in primary stack area */

static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */

static const int decorhints = 1; /* 1 means respect decoration hints */

static const Layout layouts[] = {
    /* symbol     arrange function, { nmaster, nstack, layout, master axis, stack axis, secondary stack axis, symbol func } */
    {"[]=", flextile, {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL}},                        // default tile layout
    {"><>", NULL, {0}},                                                                                        /* no layout function means floating behavior */
    {"[M]", flextile, {-1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL}},                                          // monocle
    {"|||", flextile, {-1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL}},                        // columns (col) layout
    {">M>", flextile, {-1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL}},                       // floating master
    {"[D]", flextile, {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL}},                              // deck
    {"TTT", flextile, {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL}},                      // bstack
    {"===", flextile, {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL}},                      // bstackhoriz
    {"|M|", flextile, {-1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, TOP_TO_BOTTOM, NULL}},   // centeredmaster
    {"-M-", flextile, {-1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT, LEFT_TO_RIGHT, NULL}}, // centeredmaster horiz
    {":::", flextile, {-1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL}},                                // gappless grid
    {"[\\]", flextile, {-1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL}},                                         // fibonacci dwindle
    {"(@)", flextile, {-1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL}},                                            // fibonacci spiral
    {"[T]", flextile, {-1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL}},                               // tatami mats

    {"[]=", tile, {0}},

    {"[M]", monocle, {0}},

    {"TTT", bstack, {0}},

    {"===", bstackhoriz, {0}},

    {"|M|", centeredmaster, {0}},

    {">M>", centeredfloatingmaster, {0}},

    {"|||", col, {0}},

    {"[D]", deck, {0}},

    {"(@)", spiral, {0}},

    {"[\\]", dwindle, {0}},

    {"HHH", grid, {0}},

    {NULL, NULL, {0}},

};

/* key definitions */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */

/* commands */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[] = {
    "dmenu_run",

    "-m", dmenumon,

    "-nb", normbgcolor,
    "-nf", normfgcolor,
    "-sb", selbgcolor,
    "-sf", selfgcolor,

    NULL};
static const char *termcmd[] = {"st", NULL};

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
/* test the above with: xsetroot -name "$(printf '\x01Volume |\x02 CPU |\x03 Battery')" */
static const char *statuscmd[] = {"", NULL};

static const char *firefoxcmd[] = {"brave", NULL};
static const char *slockcmd[] = {"slock", NULL};
static const char *symcmd[] = {"symbols", NULL};
static const char *volupcmd[] = {"vol", "+5%", NULL};
static const char *voldowncmd[] = {"vol", "-5%", NULL};
static const char *dmenuemoji[] = {"dmenuemoji", NULL};
static const char *sigdwmblocks[] = {"signaldwmblocks", NULL};
static Key on_empty_keys[] = {
    /* modifier key            function                argument */
    {0, XK_f, spawn, {.v = firefoxcmd}},
    {0, XK_d, spawn, {.v = {"discord", NULL}}}};

static Key keys[] = {
    /* modifier                     key            function                argument */
    {0, XF86XK_AudioRaiseVolume, spawn, SPWN(volupcmd)},
    {0, XF86XK_AudioLowerVolume, spawn, SPWN(voldowncmd)},
    
    {Mod4Mask | ShiftMask, XK_l, spawn, {.v = slockcmd}},
    {Mod4Mask, XK_u, spawn, SPWN(dmenuemoji)},
    {Mod4Mask | ShiftMask, XK_u, spawn, SPWN(symcmd)},

    {Mod4Mask, XK_p, spawn, {.v = dmenucmd}},
    {Mod4Mask | ShiftMask, XK_Return, spawn, {.v = termcmd}},

    {Mod4Mask, XK_b, togglebar, {0}},
    {Mod4Mask | ShiftMask, XK_b, spawn, SPWN(sigdwmblocks)},

    {Mod4Mask | ShiftMask, XK_F5, xrdb, {.v = NULL}},

    {Mod4Mask, XK_j, focusstack, {.i = +1}},
    {Mod4Mask, XK_k, focusstack, {.i = -1}},

    {Mod4Mask, XK_i, incnmaster, {.i = +1}},
    {Mod4Mask, XK_d, incnmaster, {.i = -1}},

    {Mod4Mask | ControlMask, XK_i, incnstack, {.i = +1}},
    {Mod4Mask | ControlMask, XK_u, incnstack, {.i = -1}},

    {Mod4Mask, XK_h, setmfact, {.f = -0.05}},
    {Mod4Mask, XK_l, setmfact, {.f = +0.05}},

    {Mod4Mask | ControlMask | ShiftMask, XK_e, aspectresize, {.i = +24}},
    {Mod4Mask | ControlMask | ShiftMask, XK_r, aspectresize, {.i = -24}},

    {Mod4Mask, XK_x, transfer, {0}},

    {Mod4Mask, XK_Return, zoom, {0}},

    {Mod4Mask, XK_Tab, view, {0}},

    {Mod4Mask | ShiftMask, XK_c, killclient, {0}},

    {Mod4Mask | ShiftMask, XK_x, killunsel, {0}},

    {Mod4Mask | ShiftMask, XK_r, self_restart, {0}},

    {Mod4Mask | ShiftMask, XK_q, quit, {0}},

    {Mod4Mask | ControlMask | ShiftMask, XK_q, quit, {1}},

    {Mod4Mask, XK_t, setlayout, {.v = &layouts[0]}},
    {Mod4Mask, XK_f, setlayout, {.v = &layouts[1]}},
    {Mod4Mask, XK_m, setlayout, {.v = &layouts[2]}},

    {Mod4Mask, XK_c, setlayout, {.v = &layouts[3]}},

    {Mod4Mask | ControlMask, XK_t, rotatelayoutaxis, {.i = +1}},               /* flextile, 1 = layout axis */
    {Mod4Mask | ControlMask, XK_Tab, rotatelayoutaxis, {.i = +2}},             /* flextile, 2 = master axis */
    {Mod4Mask | ControlMask | ShiftMask, XK_Tab, rotatelayoutaxis, {.i = +3}}, /* flextile, 3 = stack axis */
    {Mod4Mask | ControlMask | Mod4Mask, XK_Tab, rotatelayoutaxis, {.i = +4}},  /* flextile, 4 = secondary stack axis */
    {Mod4Mask | Mod5Mask, XK_t, rotatelayoutaxis, {.i = -1}},                  /* flextile, 1 = layout axis */
    {Mod4Mask | Mod5Mask, XK_Tab, rotatelayoutaxis, {.i = -2}},                /* flextile, 2 = master axis */
    {Mod4Mask | Mod5Mask | ShiftMask, XK_Tab, rotatelayoutaxis, {.i = -3}},    /* flextile, 3 = stack axis */
    {Mod4Mask | Mod5Mask | Mod4Mask, XK_Tab, rotatelayoutaxis, {.i = -4}},     /* flextile, 4 = secondary stack axis */
    {Mod4Mask | ControlMask, XK_Return, mirrorlayout, {0}},                    /* flextile, flip master and stack areas */

    {Mod4Mask, XK_space, setlayout, {0}},
    {Mod4Mask | ShiftMask, XK_space, togglefloating, {0}},

    {Mod4Mask | ControlMask | ShiftMask, XK_h, togglehorizontalmax, {0}},
    {Mod4Mask | ControlMask | ShiftMask, XK_l, togglehorizontalmax, {0}},
    {Mod4Mask | ControlMask | ShiftMask, XK_j, toggleverticalmax, {0}},
    {Mod4Mask | ControlMask | ShiftMask, XK_k, toggleverticalmax, {0}},
    {Mod4Mask | ControlMask, XK_m, togglemax, {0}},

    {Mod4Mask, XK_grave, togglescratch, {.ui = 0}},
    {Mod4Mask | ControlMask, XK_grave, setscratch, {.ui = 0}},
    {Mod4Mask | ShiftMask, XK_grave, removescratch, {.ui = 0}},

    {Mod4Mask, XK_y, togglefullscreen, {0}},

    {Mod4Mask | ShiftMask, XK_y, togglefakefullscreen, {0}},

    {Mod4Mask | ShiftMask, XK_f, fullscreen, {0}},

    {Mod4Mask | ShiftMask, XK_s, togglesticky, {0}},

    {Mod4Mask, XK_0, view, {.ui = ~SPTAGMASK}},
    {Mod4Mask | ShiftMask, XK_0, tag, {.ui = ~SPTAGMASK}},

    {Mod4Mask, XK_comma, focusmon, {.i = -1}},
    {Mod4Mask, XK_period, focusmon, {.i = +1}},
    {Mod4Mask | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {Mod4Mask | ShiftMask, XK_period, tagmon, {.i = +1}},

    {Mod4Mask, XK_Left, viewtoleft, {0}},   // note keybinding conflict with focusdir
    {Mod4Mask, XK_Right, viewtoright, {0}}, // note keybinding conflict with focusdir
    {Mod4Mask | ShiftMask, XK_Left, tagtoleft, {0}},
    {Mod4Mask | ShiftMask, XK_Right, tagtoright, {0}},
    {Mod4Mask | ControlMask, XK_Left, tagandviewtoleft, {0}},
    {Mod4Mask | ControlMask, XK_Right, tagandviewtoright, {0}},

    {Mod4Mask | ShiftMask, XK_F1, tagall, {.v = "F1"}},
    {Mod4Mask | ShiftMask, XK_F2, tagall, {.v = "F2"}},
    {Mod4Mask | ShiftMask, XK_F3, tagall, {.v = "F3"}},
    {Mod4Mask | ShiftMask, XK_F4, tagall, {.v = "F4"}},
    {Mod4Mask | ShiftMask, XK_F5, tagall, {.v = "F5"}},
    {Mod4Mask | ShiftMask, XK_F6, tagall, {.v = "F6"}},
    {Mod4Mask | ShiftMask, XK_F7, tagall, {.v = "F7"}},
    {Mod4Mask | ShiftMask, XK_F8, tagall, {.v = "F8"}},
    {Mod4Mask | ShiftMask, XK_F9, tagall, {.v = "F9"}},
    {Mod4Mask | ControlMask, XK_F1, tagall, {.v = "1"}},
    {Mod4Mask | ControlMask, XK_F2, tagall, {.v = "2"}},
    {Mod4Mask | ControlMask, XK_F3, tagall, {.v = "3"}},
    {Mod4Mask | ControlMask, XK_F4, tagall, {.v = "4"}},
    {Mod4Mask | ControlMask, XK_F5, tagall, {.v = "5"}},
    {Mod4Mask | ControlMask, XK_F6, tagall, {.v = "6"}},
    {Mod4Mask | ControlMask, XK_F7, tagall, {.v = "7"}},
    {Mod4Mask | ControlMask, XK_F8, tagall, {.v = "8"}},
    {Mod4Mask | ControlMask, XK_F9, tagall, {.v = "9"}},

    {Mod4Mask, XK_KP_7, explace, {.ui = EX_NW}}, /* XK_KP_Home,  */
    {Mod4Mask, XK_KP_8, explace, {.ui = EX_N}},  /* XK_KP_Up,    */
    {Mod4Mask, XK_KP_9, explace, {.ui = EX_NE}}, /* XK_KP_Prior, */
    {Mod4Mask, XK_KP_4, explace, {.ui = EX_W}},  /* XK_KP_Left,  */
    {Mod4Mask, XK_KP_5, explace, {.ui = EX_C}},  /* XK_KP_Begin, */
    {Mod4Mask, XK_KP_6, explace, {.ui = EX_E}},  /* XK_KP_Right, */
    {Mod4Mask, XK_KP_1, explace, {.ui = EX_SW}}, /* XK_KP_End,   */
    {Mod4Mask, XK_KP_2, explace, {.ui = EX_S}},  /* XK_KP_Down,  */
    {Mod4Mask, XK_KP_3, explace, {.ui = EX_SE}}, /* XK_KP_Next,  */

    {Mod4Mask | ShiftMask, XK_KP_8, exresize, {.v = (int[]){0, 25}}},                  /* XK_KP_Up,    */
    {Mod4Mask | ShiftMask, XK_KP_2, exresize, {.v = (int[]){0, -25}}},                 /* XK_KP_Down,  */
    {Mod4Mask | ShiftMask, XK_KP_6, exresize, {.v = (int[]){25, 0}}},                  /* XK_KP_Right, */
    {Mod4Mask | ShiftMask, XK_KP_4, exresize, {.v = (int[]){-25, 0}}},                 /* XK_KP_Left,  */
    {Mod4Mask | ShiftMask, XK_KP_5, exresize, {.v = (int[]){25, 25}}},                 /* XK_KP_Begin, */
    {Mod4Mask | ShiftMask | ControlMask, XK_KP_5, exresize, {.v = (int[]){-25, -25}}}, /* XK_KP_Begin, */

    {Mod4Mask | ControlMask, XK_KP_6, togglehorizontalexpand, {.i = +1}}, /* XK_KP_Right, */
    {Mod4Mask | ControlMask, XK_KP_3, togglehorizontalexpand, {.i = 0}},  /* XK_KP_Next,  */
    {Mod4Mask | ControlMask, XK_KP_4, togglehorizontalexpand, {.i = -1}}, /* XK_KP_Left,  */
    {Mod4Mask | ControlMask, XK_KP_8, toggleverticalexpand, {.i = +1}},   /* XK_KP_Up,    */
    {Mod4Mask | ControlMask, XK_KP_1, toggleverticalexpand, {.i = 0}},    /* XK_KP_End,   */
    {Mod4Mask | ControlMask, XK_KP_2, toggleverticalexpand, {.i = -1}},   /* XK_KP_Down,  */
    {Mod4Mask | ControlMask, XK_KP_9, togglemaximize, {.i = -1}},         /* XK_KP_Prior, */
    {Mod4Mask | ControlMask, XK_KP_7, togglemaximize, {.i = +1}},         /* XK_KP_Home,  */
    {Mod4Mask | ControlMask, XK_KP_5, togglemaximize, {.i = 0}},          /* XK_KP_Begin, */

    {Mod4Mask | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {Mod4Mask | ControlMask, XK_period, cyclelayout, {.i = +1}},

    {Mod4Mask, XK_1, view, {.ui = 1 << 0}},
    {Mod4Mask | ControlMask, XK_1, toggleview, {.ui = 1 << 0}},
    {Mod4Mask | ShiftMask, XK_1, tag, {.ui = 1 << 0}},
    {Mod4Mask | ControlMask | ShiftMask, XK_1, toggletag, {.ui = 1 << 0}},
    {Mod4Mask, XK_2, view, {.ui = 1 << 1}},
    {Mod4Mask | ControlMask, XK_2, toggleview, {.ui = 1 << 1}},
    {Mod4Mask | ShiftMask, XK_2, tag, {.ui = 1 << 1}},
    {Mod4Mask | ControlMask | ShiftMask, XK_2, toggletag, {.ui = 1 << 1}},
    {Mod4Mask, XK_3, view, {.ui = 1 << 2}},
    {Mod4Mask | ControlMask, XK_3, toggleview, {.ui = 1 << 2}},
    {Mod4Mask | ShiftMask, XK_3, tag, {.ui = 1 << 2}},
    {Mod4Mask | ControlMask | ShiftMask, XK_3, toggletag, {.ui = 1 << 2}},
    {Mod4Mask, XK_4, view, {.ui = 1 << 3}},
    {Mod4Mask | ControlMask, XK_4, toggleview, {.ui = 1 << 3}},
    {Mod4Mask | ShiftMask, XK_4, tag, {.ui = 1 << 3}},
    {Mod4Mask | ControlMask | ShiftMask, XK_4, toggletag, {.ui = 1 << 3}},
    {Mod4Mask, XK_5, view, {.ui = 1 << 4}},
    {Mod4Mask | ControlMask, XK_5, toggleview, {.ui = 1 << 4}},
    {Mod4Mask | ShiftMask, XK_5, tag, {.ui = 1 << 4}},
    {Mod4Mask | ControlMask | ShiftMask, XK_5, toggletag, {.ui = 1 << 4}},
    {Mod4Mask, XK_6, view, {.ui = 1 << 5}},
    {Mod4Mask | ControlMask, XK_6, toggleview, {.ui = 1 << 5}},
    {Mod4Mask | ShiftMask, XK_6, tag, {.ui = 1 << 5}},
    {Mod4Mask | ControlMask | ShiftMask, XK_6, toggletag, {.ui = 1 << 5}},
    {Mod4Mask, XK_7, view, {.ui = 1 << 6}},
    {Mod4Mask | ControlMask, XK_7, toggleview, {.ui = 1 << 6}},
    {Mod4Mask | ShiftMask, XK_7, tag, {.ui = 1 << 6}},
    {Mod4Mask | ControlMask | ShiftMask, XK_7, toggletag, {.ui = 1 << 6}},
    {Mod4Mask, XK_8, view, {.ui = 1 << 7}},
    {Mod4Mask | ControlMask, XK_8, toggleview, {.ui = 1 << 7}},
    {Mod4Mask | ShiftMask, XK_8, tag, {.ui = 1 << 7}},
    {Mod4Mask | ControlMask | ShiftMask, XK_8, toggletag, {.ui = 1 << 7}},
    {Mod4Mask, XK_9, view, {.ui = 1 << 8}},
    {Mod4Mask | ControlMask, XK_9, toggleview, {.ui = 1 << 8}},
    {Mod4Mask | ShiftMask, XK_9, tag, {.ui = 1 << 8}},
    {Mod4Mask | ControlMask | ShiftMask, XK_9, toggletag, {.ui = 1 << 8}},
};

/* button definitions */

/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */

static Button buttons[] = {
    /* click                event mask           button          function        argument */

    {ClkButton, 0, Button1, spawn, {.v = dmenucmd}},

    {ClkLtSymbol, 0, Button1, setlayout, {0}},

    {ClkLtSymbol, 0, Button3, layoutmenu, {0}},

    {ClkWinTitle, 0, Button2, zoom, {0}},

    /* {ClkStatusText, 0, Button1, spawn, {.v = statuscmd}}, */
    /* {ClkStatusText, 0, Button2, spawn, {.v = statuscmd}}, */
    /* {ClkStatusText, 0, Button3, spawn, {.v = statuscmd}}, */

    {ClkClientWin, Mod4Mask, Button1, movemouse, {0}},

    {ClkClientWin, Mod4Mask, Button2, togglefloating, {0}},
    {ClkClientWin, Mod4Mask, Button3, resizemouse, {0}},

    {ClkClientWin, Mod4Mask | ShiftMask, Button1, dragmfact, {0}},

    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, Mod4Mask, Button1, tag, {0}},
    {ClkTagBar, Mod4Mask, Button3, toggletag, {0}},
    {ClkStatusText, 0, Button1, sigstatusbar, {.i = 1}},
    {ClkStatusText, 0, Button2, sigstatusbar, {.i = 2}},
    {ClkStatusText, 0, Button3, sigstatusbar, {.i = 3}},
    {ClkStatusText, ShiftMask, Button3, sigstatusbar, {.i = 4}},

};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum                    function */
    {"focusstack", focusstack},
    {"setmfact", setmfact},
    {"togglebar", togglebar},
    {"incnmaster", incnmaster},
    {"togglefloating", togglefloating},
    {"focusmon", focusmon},

    {"viewtoleft", viewtoleft},
    {"viewtoright", viewtoright},
    {"tagtoleft", tagtoleft},
    {"tagtoright", tagtoright},
    {"tagandviewtoleft", tagandviewtoleft},
    {"tagandviewtoright", tagandviewtoright},

    {"incnstack", incnstack},
    {"rotatelayoutaxis", rotatelayoutaxis},
    {"setlayoutaxisex", setlayoutaxisex},
    {"mirrorlayout", mirrorlayout},

    {"explace", explace},
    {"togglehorizontalexpand", togglehorizontalexpand},
    {"toggleverticalexpand", toggleverticalexpand},
    {"togglemaximize", togglemaximize},

    {"transfer", transfer},

    {"tagmon", tagmon},
    {"zoom", zoom},

    {"view", view},
    {"viewall", viewallex},
    {"viewex", viewex},
    {"toggleview", toggleview},

    {"self_restart", self_restart},

    {"togglesticky", togglesticky},

    {"cyclelayout", cyclelayout},

    {"toggleviewex", toggleviewex},
    {"tag", tag},
    {"tagall", tagallex},
    {"tagex", tagex},
    {"toggletag", toggletag},
    {"toggletagex", toggletagex},

    {"togglefullscreen", togglefullscreen},

    {"togglefakefullscreen", togglefakefullscreen},

    {"fullscreen", fullscreen},

    {"togglehorizontalmax", togglehorizontalmax},
    {"toggleverticalmax", toggleverticalmax},
    {"togglemax", togglemax},

    {"togglescratch", togglescratch},

    {"killclient", killclient},

    {"quit", quit},
    {"setlayout", setlayout},
    {"setlayoutex", setlayoutex},
    {"xrdb", xrdb},
};
