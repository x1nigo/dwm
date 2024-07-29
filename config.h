/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMCLASS "St"
#define TERM "st"
#define BROWSER "firefox"
#define FILEMGR "fm"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "NotoColorEmoji:size=8" };
static const char normbgcolor[]     = "#111111";
static const char normbordercolor[] = "#200";
static const char normfgcolor[]     = "#ebdbb2";
static const char selfgcolor[]      = "#ebdbb2";
static const char selbordercolor[]  = "#500";
static const char selbgcolor[]      = "#121618";
static const unsigned int baralpha = 0xf0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*                fg           bg           border */
	[SchemeNorm]  = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]   = { selfgcolor,  selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
    /* class            instance      title           tags mask  isfloating isterminal noswallow  monitor */
    { BROWSER,          NULL,         NULL,           0,         0,         0,         0,         -1 },
    { TERMCLASS,        NULL,         NULL,           0,         0,         1,         0,         -1 },
    { TERMCLASS,        "termfloat",  NULL,           0,         1,         1,         0,         -1 },
    { NULL,             NULL,         "Event Tester", 0,         0,         0,         1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },

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

#include <X11/XF86keysym.h>
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          SHCMD(TERM) },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = (const char*[]){ TERM, "-n", "termfloat", "-g", "128x38", NULL } } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
	{ MODKEY,                       XK_r,      spawn,          {.v = (const char*[]){TERM, "-e", FILEMGR, NULL } } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ControlMask,           XK_b,      togglebar,      {0} },
	{ MODKEY|Mod1Mask,              XK_b,      toggleborder,   {0} },
	{ MODKEY,                       XK_b,      spawn,          SHCMD("bookmarker") },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
 	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_a,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_x,      spawn,          SHCMD("setwp -d") },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("setwp -x") },

	{ MODKEY|ControlMask,           XK_j,      setgaps,        {.i = -5 } },
	{ MODKEY|ControlMask,           XK_k,      setgaps,        {.i = +5 } },
	{ MODKEY|ControlMask,           XK_g,      setgaps,        {.i = GAP_RESET } },
	{ MODKEY,                       XK_g,      setgaps,        {.i = GAP_TOGGLE } },

	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
 	{ MODKEY|ControlMask,       	XK_comma,  cyclelayout,    {.i = -1 } },
 	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_apostrophe, spawn,      {.v = (const char*[]){TERM, "-n", "termfloat", "-g", "50x20", "-e", "bc", "-l", NULL} } },
	{ MODKEY,                       XK_Insert, spawn,          SHCMD("inserter") },
	{ MODKEY,                       XK_grave,  spawn,          SHCMD("dmenumoji") },
#ifndef __OpenBSD__
	{ 0, XF86XK_AudioMute,          spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle ; ref-bar") },
	{ 0, XF86XK_AudioMicMute,       spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+ ; ref-bar") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%- ; ref-bar") },
	{ 0, XF86XK_MonBrightnessUp,    spawn,     SHCMD("doas xblight -i ; ref-bar") },
	{ 0, XF86XK_MonBrightnessDown,  spawn,     SHCMD("doas xblight -d ; ref-bar") },
#else
	{ 0, XF86XK_AudioMute,          spawn,     SHCMD("ref-bar") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,     SHCMD("ref-bar") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,     SHCMD("ref-bar") },
#endif
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_F1,     spawn,          SHCMD("readme") },
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("fontwizard") },
	{ MODKEY,                       XK_F3,     spawn,          {.v = (const char*[]){TERM, "-e", "pulsemixer"} } },
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("selectdisplay") },
	{ MODKEY,                       XK_F12,    quit,           {0} },
	{ 0,                            XK_Print,  spawn,          SHCMD("printscreen") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkLtSymbol,          0,              Button3,        spawn,          SHCMD(TERM) },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

