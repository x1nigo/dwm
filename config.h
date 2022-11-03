/* See LICENSE file for copyright and license details. */

#define BROWSER "firefox"
#define FILEMANAGER "lfrun"
#define STATUSBAR "dwmblocks"
#define MPDClient "ncmpcpp"
#define RSSReader "newsboat"
#define TERMCLASS "st-256color"
#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 18;       /* vert inner gap between windows */
static const unsigned int gappoh    = 12;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 28;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

/* fonts */
static const char *fonts[]          = { "Bitstream Vera Sans Mono:regular:pixelsize=14:antialias=true:autohint=true",
                                        "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true" };
/* colors */
static const char norm_bg[]         = "#121218";
static const char norm_br[]         = "#000";
static const char font_norm[]       = "#eee";
static const char font_sel[]        = "#000";
static const char main_bg[]         = "#008080";
static const char main_br[]         = "#008080";
static const unsigned int baralpha = 0xdf;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { font_norm, norm_bg,   norm_br   },
	[SchemeSel]  = { font_sel,  main_bg,   main_br   },
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border     */
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
    /* class            instance      title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "Gimp",           NULL,         NULL,           0,         0,          0,           0,        -1 },
    { BROWSER,          NULL,         NULL,           0,         0,          0,          -1,        -1 },
    { TERMCLASS,        NULL,         NULL,           0,         0,          1,           0,        -1 },
    { TERMCLASS,        "stFLOAT",    NULL,           0,         1,          1,           0,        -1 },
    { NULL,             NULL,         "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
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

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2]           = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "dmenu_run", NULL };
static const char *termcmd[]      = { "st", NULL };
static const char *termfloatcmd[] = { "st", "-n", "stFLOAT", NULL };

/* media controls */
static const char *volupcmd[]       = { "sh", "-c", "pamixer -i 5 -u ; pkill -RTMIN+10 dwmblocks", NULL };
static const char *voldowncmd[]     = { "sh", "-c", "pamixer -d 5 -u ; pkill -RTMIN+10 dwmblocks", NULL };
static const char *mutecmd[]        = { "sh", "-c", "pamixer -t ; pkill -RTMIN+10 dwmblocks", NULL };
static const char *micupcmd[]       = { "sh", "-c", "pamixer --default-source -i 5 -u ; pkill -RTMIN+1 dwmblocks", NULL };
static const char *micdowncmd[]     = { "sh", "-c", "pamixer --default-source -d 5 -u ; pkill -RTMIN+1 dwmblocks", NULL };
static const char *micmutecmd[]     = { "sh", "-c", "pamixer --default-source -t ; pkill -RTMIN+1 dwmblocks", NULL };
static const char *blightupcmd[]    = { "sh", "-c", "screenbrightness inc ; pkill -RTMIN+12 dwmblocks", NULL };
static const char *blightdowncmd[]  = { "sh", "-c", "screenbrightness dec ; pkill -RTMIN+12 dwmblocks", NULL };
static const char *kbd_blightup[]   = { "sh", "-c", "kbdbrightness inc", NULL };
static const char *kbd_blightdown[] = { "sh", "-c", "kbdbrightness dec", NULL };

/* other */
static const char *browsercmd[] = { BROWSER, NULL };
static const char *sysmcmd[]    = { "sh", "-c", "systemmenu", NULL };
static const char *scrotcmd[]   = { "sh", "-c", "screenshot", NULL };
static const char *lfcmd[]      = { "st", "-e", FILEMANAGER, NULL };
static const char *texcmd[]     = { "sh", "-c", "texfind", NULL };
static const char *recordcmd[]  = { "sh", "-c", "recordscreen", NULL };
static const char *killrecord[] = { "sh", "-c", "killrecording", NULL };
static const char *emojicmd[]   = { "sh", "-c", "dmenumoji", NULL };
static const char *webcamcmd[]  = { "st", "-n", "stFLOAT", "-e", "sh", "-c", "webcam", NULL };
static const char *musiccmd[]   = { "st", "-e", MPDClient, NULL };
static const char *newscmd[]    = { "st", "-e", RSSReader, NULL };
static const char *bgcmd[]      = { "sh", "-c", "setwallpaper -s", NULL };
static const char *bmkcmd[]     = { "sh", "-c", "get-bookmark", NULL };
static const char *addbmkcmd[]  = { "sh", "-c", "bookmark-it", NULL };

#include <X11/XF86keysym.h>
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
        { MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
        { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
        { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
        { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
    	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
    	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
    	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
    	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
    	{ MODKEY|Mod4Mask,              XK_g,      togglegaps,     {0} },
    	{ MODKEY|Mod4Mask|ShiftMask,    XK_g,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* media controls */
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0,                            XF86XK_AudioMute,        spawn, {.v = mutecmd } },
	{ ShiftMask,                    XF86XK_AudioRaiseVolume, spawn, {.v = micupcmd } },
	{ ShiftMask,                    XF86XK_AudioLowerVolume, spawn, {.v = micdowncmd } },
	{ 0,                            XF86XK_AudioMicMute,     spawn, {.v = micmutecmd } },
	{ 0,                            XF86XK_MonBrightnessUp,  spawn, {.v = blightupcmd } },
	{ 0,                            XF86XK_MonBrightnessDown, spawn, {.v = blightdowncmd } },
	{ 0,                            XF86XK_KbdBrightnessUp,  spawn, {.v = kbd_blightup } },
	{ 0,                            XF86XK_KbdBrightnessDown, spawn, {.v = kbd_blightdown } },
	/* alternative media controls */
	{ MODKEY,                       XK_minus,                spawn, {.v = volupcmd } },
	{ MODKEY|ShiftMask,             XK_minus,                spawn, {.v = voldowncmd } },
	{ MODKEY,                       XK_equal,                spawn, {.v = mutecmd } },
	{ MODKEY|ShiftMask,             XK_equal,                spawn, {.v = micmutecmd } },
	{ MODKEY,                       XK_BackSpace,            spawn, {.v = micupcmd } },
	{ MODKEY|ShiftMask,             XK_BackSpace,            spawn, {.v = micdowncmd } },
	{ MODKEY,                       XK_bracketright,         spawn, {.v = blightupcmd } },
	{ MODKEY,                       XK_bracketleft,          spawn, {.v = blightdowncmd } },
	{ MODKEY|ShiftMask,             XK_d,                    spawn, {.v = killrecord } },
	/* user-added controls */
	{ MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_q,      spawn,          {.v = sysmcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = scrotcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = lfcmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = texcmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = recordcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = termfloatcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emojicmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = webcamcmd } },
	{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = musiccmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = newscmd } },
        { MODKEY,                       XK_x,      spawn,          {.v = bgcmd } },
        { MODKEY,                       XK_b,      spawn,          {.v = bmkcmd } },
        { MODKEY|ControlMask,           XK_b,      spawn,          {.v = addbmkcmd } },
	/* tags */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
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

