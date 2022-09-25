/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* pixels in between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9", "FontAwesome:size=9" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=9";
static const char col_nbg[]       = "#040c16";
static const char col_blk[]       = "#3d3e51";
static const char col_gry[]       = "#323949";
static const char col_wht[]       = "#cce9ea";
static const char col_acc[]       = "#aaf0c1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_wht, col_nbg, col_nbg },
	[SchemeSel]  = { col_nbg, col_acc, col_acc },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 7,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[ ]",      monocle },
	{ "|M|",      centeredmaster },
	{ "TTT",      bstack },
};

/* key definitions */
#define MODKEY Mod4Mask
#define NOMODK 0
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_nbg, "-nf", col_wht, "-sb", col_acc, "-sf", col_nbg, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_d,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_equal,  incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
  { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ControlMask,           XK_j,   	 moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_h,   	 moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_l,  		 moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask, 							XK_j,   	 moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask, 							XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask, 							XK_l,  		 moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask, 							XK_h,   	 moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY,                       XK_Tab,    zoom,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_F1,     setlayout,     {.v = &layouts[0]} },
	{ MODKEY,                       XK_F2,     setlayout,     {.v = &layouts[3]} },
	{ MODKEY,                       XK_F3,     setlayout,     {.v = &layouts[4]} },
	{ MODKEY,                       XK_m,      setlayout,     {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_s,      togglealwaysontop, {0} },
	{ MODKEY,					              XK_0,      setlayout,      		{0} },
	{ MODKEY,             					XK_s,      togglefloating, 		{0} },
	{ MODKEY,                       XK_f,      togglefullscr,  		{0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	{ MODKEY|ControlMask,           XK_r,      quit,           {0} },
    // these are all mine
	{ MODKEY,                       XK_e,      spawn,          SHCMD("st -e ranger") },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("st -e nvim") },
	{ MODKEY,                       XK_Escape, spawn,          SHCMD("st -e htop") },
	{ MODKEY,                       XK_b,      spawn,          SHCMD("sh ~/.dwm/scripts/binds/bluetooth.sh") },
	{ MODKEY,                       XK_u,      spawn,          SHCMD("sh ~/.dwm/scripts/binds/language.sh") },
	{ NOMODK,                       XF86XK_AudioRaiseVolume,   spawn, SHCMD("sh ~/.dwm/scripts/binds/sysVol up") },
	{ NOMODK,                       XF86XK_AudioLowerVolume,   spawn, SHCMD("sh ~/.dwm/scripts/binds/sysVol down") },
	{ NOMODK,                       XF86XK_AudioMute,          spawn, SHCMD("sh ~/.dwm/scripts/binds/sysVol mute") },
  { Mod1Mask,                     XF86XK_AudioRaiseVolume,   spawn, SHCMD("sh ~/.dwm/scripts/binds/songVol up") },
	{ Mod1Mask,                     XF86XK_AudioLowerVolume,   spawn, SHCMD("sh ~/.dwm/scripts/binds/songVol down") },
	{ NOMODK,                       XF86XK_AudioMute,          spawn, SHCMD("sh ~/.dwm/scripts/binds/sysVol mute") },
	{ NOMODK,                       XF86XK_AudioPlay,          spawn, SHCMD("sh ~/.dwm/scripts/binds/songPlay play") },
	{ NOMODK,                       XF86XK_AudioNext,          spawn, SHCMD("sh ~/.dwm/scripts/binds/songPlay next") },
	{ NOMODK,                       XF86XK_AudioPrev,          spawn, SHCMD("sh ~/.dwm/scripts/binds/songPlay prev") },
	{ NOMODK,                       XF86XK_MonBrightnessUp,    spawn, SHCMD("sh ~/.dwm/scripts/binds/brightness.sh up") },
	{ NOMODK,                       XF86XK_MonBrightnessDown,  spawn, SHCMD("sh ~/.dwm/scripts/binds/brightness.sh down") },
	{ NOMODK,                       XK_Print,            			 spawn, SHCMD("maim -s | xclip -selection clipboard -t image/png") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

