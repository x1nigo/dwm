/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMCLASS "St"
#define TERM "st"
#define BROWSER "firefox" /* toggle between firefox, librewolf, and zen-browser */
#define FILEMGR "lfup"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 16;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 24;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "monospace:size=10:antialias=true",
	"NotoColorEmoji:size=8:antialias=true",
	"Mononoki Nerd Font:size=8:antialias=true" };
static const char normbgcolor[]     = "#21242b";
static const char normbordercolor[] = "#282828";
static const char normfgcolor[]     = "#d7d7d7";
static const char selfgcolor[]      = "#d7d7f7";
static const char selbgcolor[]      = "#370057";
static const char selbordercolor[]  = "#370057";
static const unsigned int baralpha = 0xef;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*                fg            bg           border */
	[SchemeNorm]  = { normfgcolor,  normbgcolor, normbordercolor },
	[SchemeSel]   = { selfgcolor,   selbgcolor,  selbordercolor  },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "󰼭", "", "󰈈", "", "", "󰣘" };

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
#define ALTKEY 0xffe9 // replace 0 with the keysym to activate holdbar

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

#include <X11/XF86keysym.h>
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          SHCMD(TERM) },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = (const char*[]){ TERM, "-n", "termfloat", "-g", "128x38", NULL } } },
	{ MODKEY,                       XK_w,      spawn,          SHCMD(BROWSER) },
	{ MODKEY,                       XK_r,      spawn,          {.v = (const char*[]){TERM, "-e", FILEMGR, NULL } } },
	{ MODKEY,                       XK_d,      spawn,          SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_b,      spawn,          SHCMD("dm-boomark") },
	{ MODKEY,                       XK_v,      spawn,          SHCMD("dm-videos") },
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
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_y,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_x,      spawn,          SHCMD("dm-wallpaper -d") },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          SHCMD("dm-wallpaper -x") },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

    { MODKEY|ControlMask,           XK_j,      incrgaps,       {.i = -1 } },
    { MODKEY|ControlMask,           XK_k,      incrgaps,       {.i = +1 } },
    { MODKEY,                       XK_g,      togglegaps,     {0} },
    { MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_apostrophe, spawn,      {.v = (const char*[]){TERM, "-n", "termfloat", "-f", "Monospace-16", "-g", "50x20", "-e", "bc", "-lq", NULL} } },
	{ MODKEY,                       XK_Insert, spawn,          SHCMD("dm-insert") },
	{ MODKEY,                       XK_grave,  spawn,          SHCMD("dm-emoji") },
	{ MODKEY,                       XK_BackSpace,    spawn,    SHCMD("dm-system") },
	/* Media Keys */
	{ 0, XF86XK_AudioMute,          spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioMicMute,       spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle") },
	{ 0, XF86XK_AudioRaiseVolume,   spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,   spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessUp,    spawn,     SHCMD("brightnessctl s 5%+; kill -46 $(pidof dwmblocks)") },
	{ 0, XF86XK_MonBrightnessDown,  spawn,     SHCMD("brightnessctl s 5%-; kill -46 $(pidof dwmblocks)") },
	/* Media Keys for "dwmstatus" -- "dwmkill" is used to update the bar. */
//	{ 0, XF86XK_AudioMute,          spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; dwmkill") },
//	{ 0, XF86XK_AudioMicMute,       spawn,     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle") },
//	{ 0, XF86XK_AudioRaiseVolume,   spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; dwmkill") },
//	{ 0, XF86XK_AudioLowerVolume,   spawn,     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; dwmkill") },
//	{ 0, XF86XK_MonBrightnessUp,    spawn,     SHCMD("brightnessctl s 5%+; dwmkill") },
//	{ 0, XF86XK_MonBrightnessDown,  spawn,     SHCMD("brightnessctl s 5%-; dwmkill") },
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
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("dm-fonts") },
	{ MODKEY,                       XK_F3,     spawn,          {.v = (const char*[]){TERM, "-e", "pulsemixer"} } },
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("dm-display") },
	{ MODKEY,                       XK_F12,    quit,           {0} },
	{ 0,                            XK_Print,  spawn,          SHCMD("dm-printscreen") },
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
 	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
 	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
 	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
 	{ ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 4} },
 	{ ClkStatusText,        ShiftMask,      Button3,        sigstatusbar,   {.i = 6} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

