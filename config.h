#include "patches.h"

#define ICONSIZE 20   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
static const unsigned int borderpx = 1;

static const unsigned int snap = 32;

static const int swallowfloating = 0;

static const char autostartblocksh[] = "autostart_blocking.sh";
static const char autostartsh[] = "autostart.sh";
static const char dwmdir[] = "dwm";
static const char localshare[] = ".local/share";

static const int showbar = 1;

static const int topbar = 1;

static const int statusmon = 'A';






static const char buttonbar[] = "<O>";


static const unsigned int systrayspacing = 2;
static const int showsystray = 1;


static int tagindicatortype = INDICATOR_TOP_LEFT_SQUARE;
static int tiledindicatortype = INDICATOR_NONE;
static int floatindicatortype = INDICATOR_TOP_LEFT_SQUARE;

static int fakefsindicatortype = INDICATOR_PLUS;
static int floatfakefsindicatortype = INDICATOR_PLUS_AND_LARGER_SQUARE;

static const char *fonts[] = {"monospace:size=10","Noto Color Emoji:pixelsize=10:antialias=true:autohint=true"};

static const char dmenufont[] = "Fira Code:size=14";

static char c000000[] = "#000000";



static char normfgcolor[] = "#bbbbbb";
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

static char *colors[][ColCount] = {


    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor, normfloatcolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor, selfloatcolor},
    [SchemeTitleNorm] = {titlenormfgcolor, titlenormbgcolor, titlenormbordercolor, titlenormfloatcolor},
    [SchemeTitleSel] = {titleselfgcolor, titleselbgcolor, titleselbordercolor, titleselfloatcolor},
    [SchemeTagsNorm] = {tagsnormfgcolor, tagsnormbgcolor, tagsnormbordercolor, tagsnormfloatcolor},
    [SchemeTagsSel] = {tagsselfgcolor, tagsselbgcolor, tagsselbordercolor, tagsselfloatcolor},
    [SchemeHidNorm] = {hidnormfgcolor, hidnormbgcolor, c000000, c000000},
    [SchemeHidSel] = {hidselfgcolor, hidselbgcolor, c000000, c000000},
    [SchemeUrg] = {urgfgcolor, urgbgcolor, urgbordercolor, urgfloatcolor},

};

static const char *layoutmenu_cmd = "layoutmenu.sh";



static const char *const autostart[] = {


    NULL
};



const char *spcmd1[] = {"alacritty", "--class", "spterm", NULL};
static Sp scratchpads[] = {

    {"spterm", spcmd1},
};

static char *tagicons[][NUMTAGS] = {
    [DEFAULT_TAGS] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"},
    [ALTERNATIVE_TAGS] = {"A", "B", "C", "D", "E", "F", "G", "H", "I"},
    [ALT_TAGS_DECORATION] = {"<1>", "<2>", "<3>", "<4>", "<5>", "<6>", "<7>", "<8>", "<9>"},
};

static const Rule rules[] = {






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

};

static const MonitorRule monrules[] = {

    {1, 2, -1, -1, -1, -1},
    {-1, 0, -1, -1, -1, -1},
};

static const BarRule barrules[] = {


    {-1, 0, BAR_ALIGN_LEFT, width_stbutton, draw_stbutton, click_stbutton, "statusbutton"},


    {0, 0, BAR_ALIGN_LEFT, width_pwrl_tags, draw_pwrl_tags, click_pwrl_tags, "powerline_tags"},

    {0, 0, BAR_ALIGN_RIGHT, width_systray, draw_systray, click_systray, "systray"},


    {-1, 0, BAR_ALIGN_LEFT, width_ltsymbol, draw_ltsymbol, click_ltsymbol, "layout"},






    {statusmon, 0, BAR_ALIGN_RIGHT, width_status2d, draw_status2d, click_statuscmd, "status2d"},

    {-1, 0, BAR_ALIGN_NONE, width_wintitle, draw_wintitle, click_wintitle, "wintitle"},

};


static const float mfact = 0.60;
static const int nmaster = 1;

static const int nstack = 0;

static const int resizehints = 0;

static const int decorhints = 1;

static const Layout layouts[] = {

    {"[]=", flextile, {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, TOP_TO_BOTTOM, 0, NULL}},
    {"><>", NULL, {0}},
    {"[M]", flextile, {-1, -1, NO_SPLIT, MONOCLE, MONOCLE, 0, NULL}},
    {"|||", flextile, {-1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL}},
    {">M>", flextile, {-1, -1, FLOATING_MASTER, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL}},
    {"[D]", flextile, {-1, -1, SPLIT_VERTICAL, TOP_TO_BOTTOM, MONOCLE, 0, NULL}},
    {"TTT", flextile, {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, LEFT_TO_RIGHT, 0, NULL}},
    {"===", flextile, {-1, -1, SPLIT_HORIZONTAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, 0, NULL}},
    {"|M|", flextile, {-1, -1, SPLIT_CENTERED_VERTICAL, LEFT_TO_RIGHT, TOP_TO_BOTTOM, TOP_TO_BOTTOM, NULL}},
    {"-M-", flextile, {-1, -1, SPLIT_CENTERED_HORIZONTAL, TOP_TO_BOTTOM, LEFT_TO_RIGHT, LEFT_TO_RIGHT, NULL}},
    {":::", flextile, {-1, -1, NO_SPLIT, GAPPLESSGRID, GAPPLESSGRID, 0, NULL}},
    {"[\\]", flextile, {-1, -1, NO_SPLIT, DWINDLE, DWINDLE, 0, NULL}},
    {"(@)", flextile, {-1, -1, NO_SPLIT, SPIRAL, SPIRAL, 0, NULL}},
    {"[T]", flextile, {-1, -1, SPLIT_VERTICAL, LEFT_TO_RIGHT, TATAMI, 0, NULL}},

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

static char dmenumon[2] = "0";

static const char *dmenucmd[] = {
    "dmenu_run",

    "-m", dmenumon,

    "-fn", dmenufont,
    "-nb", normbgcolor,
    "-nf", normfgcolor,
    "-sb", selbgcolor,
    "-sf", selfgcolor,



    NULL};
static const char *termcmd[] = {"kitty", NULL};







static const StatusCmd statuscmds[] = {
    {"notify-send Volume$BUTTON", 1},
    {"notify-send CPU$BUTTON", 2},
    {"notify-send Battery$BUTTON", 3},
};

static const char *statuscmd[] = {"", NULL};




static const char *firefoxcmd[] = {"brave", NULL};
static const char *slockcmd[] = {"slock", NULL};
static const char *symcmd[] = {"/bin/sh","-c", "~/.local/bin/symbols", NULL};
static Key on_empty_keys[] = {

    {0, XK_f, spawn, {.v = firefoxcmd}},
    {0, XK_d, spawn, {.v = {"discord", NULL}}}
};


static Key keys[] = {

    {Mod1Mask | ShiftMask, XK_l, spawn, {.v = slockcmd}},
    {Mod1Mask, XK_u, spawn, {.v = symcmd}},



    {Mod1Mask, XK_p, spawn, {.v = dmenucmd}},
    {Mod1Mask | ShiftMask, XK_Return, spawn, {.v = termcmd}},





    {Mod1Mask, XK_b, togglebar, {0}},

    {Mod1Mask, XK_j, focusstack, {.i = +1}},
    {Mod1Mask, XK_k, focusstack, {.i = -1}},

    {Mod1Mask, XK_i, incnmaster, {.i = +1}},
    {Mod1Mask, XK_d, incnmaster, {.i = -1}},

    {Mod1Mask | ControlMask, XK_i, incnstack, {.i = +1}},
    {Mod1Mask | ControlMask, XK_u, incnstack, {.i = -1}},

    {Mod1Mask, XK_h, setmfact, {.f = -0.05}},
    {Mod1Mask, XK_l, setmfact, {.f = +0.05}},






    {Mod1Mask | ControlMask | ShiftMask, XK_e, aspectresize, {.i = +24}},
    {Mod1Mask | ControlMask | ShiftMask, XK_r, aspectresize, {.i = -24}},

    {Mod1Mask, XK_x, transfer, {0}},

    {Mod1Mask, XK_Return, zoom, {0}},

    {Mod1Mask, XK_Tab, view, {0}},

    {Mod1Mask | ShiftMask, XK_c, killclient, {0}},

    {Mod1Mask | ShiftMask, XK_x, killunsel, {0}},


    {Mod1Mask | ShiftMask, XK_r, self_restart, {0}},

    {Mod1Mask | ShiftMask, XK_q, quit, {0}},

    {Mod1Mask | ControlMask | ShiftMask, XK_q, quit, {1}},

    {Mod1Mask, XK_t, setlayout, {.v = &layouts[0]}},
    {Mod1Mask, XK_f, setlayout, {.v = &layouts[1]}},
    {Mod1Mask, XK_m, setlayout, {.v = &layouts[2]}},

    {Mod1Mask, XK_c, setlayout, {.v = &layouts[3]}},


    {Mod1Mask | ControlMask, XK_t, rotatelayoutaxis, {.i = +1}},
    {Mod1Mask | ControlMask, XK_Tab, rotatelayoutaxis, {.i = +2}},
    {Mod1Mask | ControlMask | ShiftMask, XK_Tab, rotatelayoutaxis, {.i = +3}},
    {Mod1Mask | ControlMask | Mod1Mask, XK_Tab, rotatelayoutaxis, {.i = +4}},
    {Mod1Mask | Mod5Mask, XK_t, rotatelayoutaxis, {.i = -1}},
    {Mod1Mask | Mod5Mask, XK_Tab, rotatelayoutaxis, {.i = -2}},
    {Mod1Mask | Mod5Mask | ShiftMask, XK_Tab, rotatelayoutaxis, {.i = -3}},
    {Mod1Mask | Mod5Mask | Mod1Mask, XK_Tab, rotatelayoutaxis, {.i = -4}},
    {Mod1Mask | ControlMask, XK_Return, mirrorlayout, {0}},

    {Mod1Mask, XK_space, setlayout, {0}},
    {Mod1Mask | ShiftMask, XK_space, togglefloating, {0}},

    {Mod1Mask | ControlMask | ShiftMask, XK_h, togglehorizontalmax, {0}},
    {Mod1Mask | ControlMask | ShiftMask, XK_l, togglehorizontalmax, {0}},
    {Mod1Mask | ControlMask | ShiftMask, XK_j, toggleverticalmax, {0}},
    {Mod1Mask | ControlMask | ShiftMask, XK_k, toggleverticalmax, {0}},
    {Mod1Mask | ControlMask, XK_m, togglemax, {0}},





    {Mod1Mask, XK_grave, togglescratch, {.ui = 0}},
    {Mod1Mask | ControlMask, XK_grave, setscratch, {.ui = 0}},
    {Mod1Mask | ShiftMask, XK_grave, removescratch, {.ui = 0}},






    {Mod1Mask, XK_y, togglefullscreen, {0}},


    {Mod1Mask | ShiftMask, XK_y, togglefakefullscreen, {0}},


    {Mod1Mask | ShiftMask, XK_f, fullscreen, {0}},


    {Mod1Mask | ShiftMask, XK_s, togglesticky, {0}},






    {Mod1Mask, XK_0, view, {.ui = ~SPTAGMASK}},
    {Mod1Mask | ShiftMask, XK_0, tag, {.ui = ~SPTAGMASK}},




    {Mod1Mask, XK_comma, focusmon, {.i = -1}},
    {Mod1Mask, XK_period, focusmon, {.i = +1}},
    {Mod1Mask | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {Mod1Mask | ShiftMask, XK_period, tagmon, {.i = +1}},

    {Mod1Mask, XK_Left, viewtoleft, {0}},
    {Mod1Mask, XK_Right, viewtoright, {0}},
    {Mod1Mask | ShiftMask, XK_Left, tagtoleft, {0}},
    {Mod1Mask | ShiftMask, XK_Right, tagtoright, {0}},
    {Mod1Mask | ControlMask, XK_Left, tagandviewtoleft, {0}},
    {Mod1Mask | ControlMask, XK_Right, tagandviewtoright, {0}},


    {Mod1Mask | ShiftMask, XK_F1, tagall, {.v = "F1"}},
    {Mod1Mask | ShiftMask, XK_F2, tagall, {.v = "F2"}},
    {Mod1Mask | ShiftMask, XK_F3, tagall, {.v = "F3"}},
    {Mod1Mask | ShiftMask, XK_F4, tagall, {.v = "F4"}},
    {Mod1Mask | ShiftMask, XK_F5, tagall, {.v = "F5"}},
    {Mod1Mask | ShiftMask, XK_F6, tagall, {.v = "F6"}},
    {Mod1Mask | ShiftMask, XK_F7, tagall, {.v = "F7"}},
    {Mod1Mask | ShiftMask, XK_F8, tagall, {.v = "F8"}},
    {Mod1Mask | ShiftMask, XK_F9, tagall, {.v = "F9"}},
    {Mod1Mask | ControlMask, XK_F1, tagall, {.v = "1"}},
    {Mod1Mask | ControlMask, XK_F2, tagall, {.v = "2"}},
    {Mod1Mask | ControlMask, XK_F3, tagall, {.v = "3"}},
    {Mod1Mask | ControlMask, XK_F4, tagall, {.v = "4"}},
    {Mod1Mask | ControlMask, XK_F5, tagall, {.v = "5"}},
    {Mod1Mask | ControlMask, XK_F6, tagall, {.v = "6"}},
    {Mod1Mask | ControlMask, XK_F7, tagall, {.v = "7"}},
    {Mod1Mask | ControlMask, XK_F8, tagall, {.v = "8"}},
    {Mod1Mask | ControlMask, XK_F9, tagall, {.v = "9"}},

    {Mod1Mask, XK_KP_7, explace, {.ui = EX_NW}},
    {Mod1Mask, XK_KP_8, explace, {.ui = EX_N}},
    {Mod1Mask, XK_KP_9, explace, {.ui = EX_NE}},
    {Mod1Mask, XK_KP_4, explace, {.ui = EX_W}},
    {Mod1Mask, XK_KP_5, explace, {.ui = EX_C}},
    {Mod1Mask, XK_KP_6, explace, {.ui = EX_E}},
    {Mod1Mask, XK_KP_1, explace, {.ui = EX_SW}},
    {Mod1Mask, XK_KP_2, explace, {.ui = EX_S}},
    {Mod1Mask, XK_KP_3, explace, {.ui = EX_SE}},

    {Mod1Mask | ShiftMask, XK_KP_8, exresize, {.v = (int[]){0, 25}}},
    {Mod1Mask | ShiftMask, XK_KP_2, exresize, {.v = (int[]){0, -25}}},
    {Mod1Mask | ShiftMask, XK_KP_6, exresize, {.v = (int[]){25, 0}}},
    {Mod1Mask | ShiftMask, XK_KP_4, exresize, {.v = (int[]){-25, 0}}},
    {Mod1Mask | ShiftMask, XK_KP_5, exresize, {.v = (int[]){25, 25}}},
    {Mod1Mask | ShiftMask | ControlMask, XK_KP_5, exresize, {.v = (int[]){-25, -25}}},

    {Mod1Mask | ControlMask, XK_KP_6, togglehorizontalexpand, {.i = +1}},
    {Mod1Mask | ControlMask, XK_KP_3, togglehorizontalexpand, {.i = 0}},
    {Mod1Mask | ControlMask, XK_KP_4, togglehorizontalexpand, {.i = -1}},
    {Mod1Mask | ControlMask, XK_KP_8, toggleverticalexpand, {.i = +1}},
    {Mod1Mask | ControlMask, XK_KP_1, toggleverticalexpand, {.i = 0}},
    {Mod1Mask | ControlMask, XK_KP_2, toggleverticalexpand, {.i = -1}},
    {Mod1Mask | ControlMask, XK_KP_9, togglemaximize, {.i = -1}},
    {Mod1Mask | ControlMask, XK_KP_7, togglemaximize, {.i = +1}},
    {Mod1Mask | ControlMask, XK_KP_5, togglemaximize, {.i = 0}},

    {Mod1Mask | ControlMask, XK_comma, cyclelayout, {.i = -1}},
    {Mod1Mask | ControlMask, XK_period, cyclelayout, {.i = +1}},






    {Mod1Mask, XK_1, view, {.ui = 1 << 0}}, {Mod1Mask | ControlMask, XK_1, toggleview, {.ui = 1 << 0}}, {Mod1Mask | ShiftMask, XK_1, tag, {.ui = 1 << 0}}, {Mod1Mask | ControlMask | ShiftMask, XK_1, toggletag, {.ui = 1 << 0}},
        {Mod1Mask, XK_2, view, {.ui = 1 << 1}}, {Mod1Mask | ControlMask, XK_2, toggleview, {.ui = 1 << 1}}, {Mod1Mask | ShiftMask, XK_2, tag, {.ui = 1 << 1}}, {Mod1Mask | ControlMask | ShiftMask, XK_2, toggletag, {.ui = 1 << 1}},
            {Mod1Mask, XK_3, view, {.ui = 1 << 2}}, {Mod1Mask | ControlMask, XK_3, toggleview, {.ui = 1 << 2}}, {Mod1Mask | ShiftMask, XK_3, tag, {.ui = 1 << 2}}, {Mod1Mask | ControlMask | ShiftMask, XK_3, toggletag, {.ui = 1 << 2}},
                {Mod1Mask, XK_4, view, {.ui = 1 << 3}}, {Mod1Mask | ControlMask, XK_4, toggleview, {.ui = 1 << 3}}, {Mod1Mask | ShiftMask, XK_4, tag, {.ui = 1 << 3}}, {Mod1Mask | ControlMask | ShiftMask, XK_4, toggletag, {.ui = 1 << 3}},
                    {Mod1Mask, XK_5, view, {.ui = 1 << 4}}, {Mod1Mask | ControlMask, XK_5, toggleview, {.ui = 1 << 4}}, {Mod1Mask | ShiftMask, XK_5, tag, {.ui = 1 << 4}}, {Mod1Mask | ControlMask | ShiftMask, XK_5, toggletag, {.ui = 1 << 4}},
                        {Mod1Mask, XK_6, view, {.ui = 1 << 5}}, {Mod1Mask | ControlMask, XK_6, toggleview, {.ui = 1 << 5}}, {Mod1Mask | ShiftMask, XK_6, tag, {.ui = 1 << 5}}, {Mod1Mask | ControlMask | ShiftMask, XK_6, toggletag, {.ui = 1 << 5}},
                            {Mod1Mask, XK_7, view, {.ui = 1 << 6}}, {Mod1Mask | ControlMask, XK_7, toggleview, {.ui = 1 << 6}}, {Mod1Mask | ShiftMask, XK_7, tag, {.ui = 1 << 6}}, {Mod1Mask | ControlMask | ShiftMask, XK_7, toggletag, {.ui = 1 << 6}},
                                {Mod1Mask, XK_8, view, {.ui = 1 << 7}}, {Mod1Mask | ControlMask, XK_8, toggleview, {.ui = 1 << 7}}, {Mod1Mask | ShiftMask, XK_8, tag, {.ui = 1 << 7}}, {Mod1Mask | ControlMask | ShiftMask, XK_8, toggletag, {.ui = 1 << 7}},
                                    {Mod1Mask, XK_9, view, {.ui = 1 << 8}}, {Mod1Mask | ControlMask, XK_9, toggleview, {.ui = 1 << 8}}, {Mod1Mask | ShiftMask, XK_9, tag, {.ui = 1 << 8}}, {Mod1Mask | ControlMask | ShiftMask, XK_9, toggletag, {.ui = 1 << 8}},};

static Button buttons[] = {


    {ClkButton, 0, Button1, spawn, {.v = dmenucmd}},

    {ClkLtSymbol, 0, Button1, setlayout, {0}},

    {ClkLtSymbol, 0, Button3, layoutmenu, {0}},







    {ClkWinTitle, 0, Button2, zoom, {0}},





    {ClkStatusText, 0, Button1, spawn, {.v = statuscmd}},
    {ClkStatusText, 0, Button2, spawn, {.v = statuscmd}},
    {ClkStatusText, 0, Button3, spawn, {.v = statuscmd}},

    {ClkClientWin, Mod1Mask, Button1, movemouse, {0}},

    {ClkClientWin, Mod1Mask, Button2, togglefloating, {0}},
    {ClkClientWin, Mod1Mask, Button3, resizemouse, {0}},

    {ClkClientWin, Mod1Mask | ShiftMask, Button1, dragmfact, {0}},

    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, Mod1Mask, Button1, tag, {0}},
    {ClkTagBar, Mod1Mask, Button3, toggletag, {0}},



};





static Signal signals[] = {

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
};
