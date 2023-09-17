/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMCLASS "st-256color"
#define TERMINAL "st"
#define BROWSER "firefox"
#define STATUSBAR "dwmblocks"
#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static unsigned int borderpx  = 3;        /* border pixel of windows */
static unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 20;       /* horiz inner gap between windows */
static unsigned int gappiv    = 10;       /* vert inner gap between windows */
static unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 30;       /* vert outer gap between windows and screen edge */
static int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int user_bh            = 0;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:size=8:antialias=true:autohint=true", "Noto Mono Nerd Font:size=9:antialias=true:autohint=true" };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#ebdbb2";
static char selfgcolor[]            = "#ebdbb2";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static const unsigned int baralpha = OPAQUE;
static const unsigned int borderalpha = OPAQUE;
static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor, selbordercolor   },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border     */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "  ", " 󰢩 ", "  ", "  ", " 󰨜 ", "  ", "  ", " 󰌢 ", "  " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class            instance      title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "Gimp",           NULL,         NULL,           0,         0,          0,           0,        -1 },
    { BROWSER,          NULL,         NULL,           0,         0,          0,          -1,        -1 },
    { TERMCLASS,        NULL,         NULL,           0,         0,          1,           0,        -1 },
    { TERMCLASS,        "termfloat",     NULL,           0,         1,          1,           0,        -1 },
    { NULL,             NULL,         "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },

	{ "[@]",      spiral },
	{ "[\\]",     dwindle },

	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },

	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },

	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },

	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* media controls */
static const char *volupcmd[]       = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; wpctl set-mute @DEFAULT_AUDIO_SINK@ 0; kill -44 $(pidof dwmblocks)", NULL };
static const char *voldowncmd[]     = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; wpctl set-mute @DEFAULT_AUDIO_SINK@ 0; kill -44 $(pidof dwmblocks)", NULL };
static const char *mutecmd[]        = { "sh", "-c", "wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)", NULL };
static const char *micupcmd[]       = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 5%+; wpctl set-mute @DEFAULT_AUDIO_SOURCE@ 0; kill -45 $(pidof dwmblocks)", NULL };
static const char *micdowncmd[]     = { "sh", "-c", "wpctl set-volume @DEFAULT_AUDIO_SOURCE@ 5%-; wpctl set-mute @DEFAULT_AUDIO_SOURCE@ 0; kill -45 $(pidof dwmblocks)", NULL };
static const char *micmutecmd[]     = { "sh", "-c", "wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle; kill -45 $(pidof dwmblocks)", NULL };

static const char *blightupcmd[]    = { "sh", "-c", "xbacklight -inc 5; kill -46 $(pidof dwmblocks)", NULL };
static const char *blightdowncmd[]  = { "sh", "-c", "xbacklight -dec 5; kill -46 $(pidof dwmblocks)", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"

/*
 * Xresources preferences to load at startup
 */
 ResourcePref resources[] = {
 		{ "normbgcolor",        STRING,  &normbgcolor },
 		{ "normbordercolor",    STRING,  &normbordercolor },
 		{ "normfgcolor",        STRING,  &normfgcolor },
 		{ "selbgcolor",         STRING,  &selbgcolor },
 		{ "selbordercolor",     STRING,  &selbordercolor },
 		{ "selfgcolor",         STRING,  &selfgcolor },
 		{ "borderpx",          	INTEGER, &borderpx },
 		{ "snap",          	INTEGER, &snap },
 		{ "showbar",          	INTEGER, &showbar },
 		{ "topbar",          	INTEGER, &topbar },
 		{ "nmaster",          	INTEGER, &nmaster },
 		{ "resizehints",       	INTEGER, &resizehints },
 		{ "mfact",      	FLOAT,   &mfact },
		{ "gappih",             INTEGER, &gappih },
		{ "gappiv",             INTEGER, &gappiv },
		{ "gappoh",             INTEGER, &gappoh },
		{ "gappov",             INTEGER, &gappov },
};


static Key keys[] = {
	/* modifier                     key        function        argument */
        /* { MODKEY|ShiftMask,             XK_Escape,       spawn,          SHCMD("") }, */
        /* { MODKEY,                       XK_Escape,       spawn,          SHCMD("") }, */
        /* { MODKEY|ShiftMask,             XK_grave,        spawn,          SHCMD("") }, */
        { MODKEY,                       XK_grave,        spawn,          SHCMD("dmenumoji") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_minus,              spawn,     {.v = voldowncmd } },
	{ MODKEY,                       XK_equal,              spawn,     {.v = volupcmd } },
	{ MODKEY|ShiftMask,             XK_equal,              spawn,     {.v = mutecmd } },
	{ MODKEY,                       XK_BackSpace,          spawn,     SHCMD("sysmenu") },
	/* { MODKEY|ShiftMask,             XK_BackSpace,          spawn,     SHCMD("") }, */

	{ MODKEY,                       XK_Tab,    view,           {0} },
	/* { MODKEY|ShiftMask,             XK_Tab,    spawn,          SHCMD("") }, */
	/* { MODKEY|ControlMask,           XK_Tab,    spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_q,      killclient,     {0} },
	/* { MODKEY|ShiftMask,             XK_q,      spawn,          {0} }, */
	/* { MODKEY|ControlMask,           XK_q,      spawn,          SHCMD(""), */
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
	/* { MODKEY|ShiftMask,             XK_w,      spawn,          SHCMD(""), */
	{ MODKEY,                       XK_e,      spawn,          {.v = (const char*[]){TERMINAL, "-e", "neomutt"} } },
        /* { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("") }, */
        /* { MODKEY|ControlMask,           XK_e,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_r,      spawn,          {.v = (const char*[]){TERMINAL, "-e", "lfrun"} } },
	/* { MODKEY|ShiftMask,             XK_r,      spawn,          SHCMD("") }, */
        /* { MODKEY|ControlMask,           XK_r,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[5]} },
        { MODKEY,                       XK_y,      setlayout,      {.v = &layouts[10]} },
        { MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[11]} },
        /* { MODKEY,                       XK_u,      spawn,          SHCMD("") }, */
        /* { MODKEY|ShiftMask,             XK_u,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_i,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_i,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_o,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_p,      spawn,          SHCMD("texfind") },
	/* { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_bracketleft,          spawn,     {.v = blightdowncmd } },
	/* { MODKEY|ShiftMask,             XK_bracketleft,          spawn,     SHCMD("") }, */
	{ MODKEY,                       XK_bracketright,         spawn,     {.v = blightupcmd } },
	/* { MODKEY|ShiftMask,             XK_bracketright,         spawn,     SHCMD("") }, */
        /* { MODKEY,                       XK_backslash,            spawn,     SHCMD("") }, */
        /* { MODKEY|ShiftMask,             XK_backslash,            spawn,     SHCMD("") }, */

        { MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
        /* { MODKEY|ShiftMask,             XK_a,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_s,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	/* { MODKEY|ShiftMask,             XK_d,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
    	{ MODKEY|Mod4Mask,              XK_g,      togglegaps,     {0} },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_g,      defaultgaps,    {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	/* { MODKEY|ShiftMask,             XK_h,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ControlMask,           XK_j,      incrgaps,       {.i = -2 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_k,      incrgaps,       {.i = +2 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	/* { MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("") }, */
        { MODKEY,                       XK_semicolon,            spawn,     SHCMD("notetaker") },
        /* { MODKEY|ShiftMask,             XK_semicolon,            spawn,     SHCMD("") }, */
        { MODKEY,                       XK_apostrophe,           spawn,     {.v = (const char*[]){TERMINAL, "-n", "termfloat", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL} } },
        /* { MODKEY|ShiftMask,             XK_apostrophe,           spawn,     SHCMD("") }, */
	{ MODKEY,                       XK_Return, spawn,          SHCMD(TERMINAL) },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = (const char*[]){ TERMINAL, "-n", "termfloat", "-g", "128x38" } } },
	/* { MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("") }, */

        /* { MODKEY,                       XK_z,      spawn,          SHCMD("") }, */
        /* { MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("") }, */
        { MODKEY,                       XK_x,      spawn,          SHCMD("setbg -s") },
	/* { MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("") }, */
	/* { MODKEY|ControlMask,           XK_x,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_c,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_c,      spawn,          SHCMD("") }, */
	/* { MODKEY,                       XK_v,      spawn,          SHCMD("") }, */
	/* { MODKEY|ShiftMask,             XK_v,      spawn,          SHCMD("") }, */
        /* { MODKEY,                       XK_b,      spawn,          SHCMD("") }, */
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
        { MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD("bookmarker") },
	{ MODKEY,                       XK_n,      spawn,          {.v = (const char*[]){TERMINAL, "-e", "newsboat"} } },
	/* { MODKEY|ShiftMask,             XK_n,      spawn,          SHCMD("") }, */
	/* { MODKEY|ControlMask,           XK_n,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_m,      spawn,          {.v = (const char*[]){TERMINAL, "-e", "ncmpcpp"} } },
	/* { MODKEY|ShiftMask,             XK_m,      spawn,          SHCMD("") }, */
	/* { MODKEY|ControlMask,           XK_m,      spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  spawn,          {.v = micdowncmd } },
	/* { MODKEY|ControlMask,           XK_comma,  spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, spawn,          {.v = micupcmd } },
	/* { MODKEY|ControlMask,           XK_period, spawn,          SHCMD("") }, */
        /* { MODKEY,                       XK_slash,  spawn,          SHCMD("") }, */
        { MODKEY|ShiftMask,             XK_slash,  spawn,          {.v = micmutecmd } },
        { MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
        { MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
        { MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	/* media controls */
	{ 0,             XF86XK_AudioRaiseVolume,      spawn,      {.v = volupcmd } },
	{ 0,             XF86XK_AudioLowerVolume,      spawn,      {.v = voldowncmd } },
	{ 0,             XF86XK_AudioMute,             spawn,      {.v = mutecmd } },
	{ ShiftMask,     XF86XK_AudioRaiseVolume,      spawn,      {.v = micupcmd } },
	{ ShiftMask,     XF86XK_AudioLowerVolume,      spawn,      {.v = micdowncmd } },
	{ 0,             XF86XK_AudioMicMute,          spawn,      {.v = micmutecmd } },
	{ 0,             XF86XK_MonBrightnessUp,       spawn,      {.v = blightupcmd } },
	{ 0,             XF86XK_MonBrightnessDown,     spawn,      {.v = blightdowncmd } },
	{ 0,             XF86XK_KbdBrightnessUp,       spawn,      SHCMD("keyblight inc") },
	{ 0,             XF86XK_KbdBrightnessDown,     spawn,      SHCMD("keyblight dec") },

        { MODKEY,                       XK_F1,         spawn,      SHCMD("groff -mom ~/.local/share/cios.mom -Tpdf | zathura -") },
        { MODKEY,                       XK_F2,         spawn,      SHCMD("fontwizard") },
        { MODKEY,                       XK_F3,         spawn,      {.v = (const char*[]){TERMINAL, "-e", "pulsemixer", NULL} } },
        { MODKEY,                       XK_F4,         spawn,      SHCMD("selectdisplay") },
        { MODKEY,                       XK_F5,         spawn,      {.v = (char const*[]){TERMINAL, "-e", "nmtui", NULL} } },
        { MODKEY,                       XK_F6,         spawn,      SHCMD("recorder") },
        /* { MODKEY,                       XK_F7,         spawn,      SHCMD("") }, */
        /* { MODKEY,                       XK_F8,         spawn,      SHCMD("") }, */
        { MODKEY,                       XK_F9,         spawn,      SHCMD("mounter") },
        { MODKEY,                       XK_F10,        spawn,      SHCMD("unmounter") },
        { MODKEY,                       XK_F11,        spawn,      SHCMD("mpv --untimed --no-cache --no-osc --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
        { MODKEY,                       XK_F12,        quit,       {1} },

	{ MODKEY,          XK_Insert,     spawn,         SHCMD("xdotool type $(cat ~/.local/share/bookmarks | dmenu -l 28 | cut -d' ' -f1)") },
	{ 0,               XK_Print,      spawn,         SHCMD("printscreen") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button3,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
        { ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
        { ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
        { ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 4} },
        { ClkStatusText,        ShiftMask,      Button3,        sigstatusbar,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

