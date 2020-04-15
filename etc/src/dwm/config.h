/* See LICENSE file for copyright and license details. */

/* for volume keys */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx    = 3;        /* border pixel of windows */
static const unsigned int snap        = 12;       /* snap pixel */
static unsigned int gappx       = 6;        /* pixel gap between clients */
static const int showbar              = 1;        /* 0 means no bar */
static const int topbar               = 1;        /* 0 means bottom bar */
static const int horizpadbar          = 6;        /* horizontal padding for statusbar */
static const int vertpadbar           = 7;        /* vertical padding for statusbar */
static const char *fonts[] = {
	"GoMono Nerd Font:size=11", 
	"Noto Sans Mono:size=9:antialias=true:autohint=true", 
	"Symbola:size=9:antialias=true:autohint=true", 
	"Monospace:size=9:antialias=true:autohint=true"
};
static const char dmenufont[]         = "GoMono Nerd Font:size=11";
/* bar opacity 
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xff; 
static const unsigned int borderalpha = OPAQUE;
#include "/home/randy/etc/cache/wal/colors-wal-dwm.h"
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
// static const char *tags[] = { "", "", "", "", "", "", "", "", "" };


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title        tags mask     isfloating   monitor */
	{ "Gimp",         NULL,      NULL,        0,            1,           -1 },
	{ "xst-256color", NULL,      "xst-float", 0,            1,           -1 },

	// { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERM(cmd) { .v = (const char*[]){ "xst", "-e", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]     = { "/bin/sh", "-c", "/home/randy/bin/dmen.sh", "-p", "Run:", NULL };
static const char *termcmd[]      = { "xst", NULL };
static const char *termfloatcmd[] = { "xst", "-T", "xst-float", NULL };
static const char *explorecmd[]   = { "dolphin", NULL };
static const char *surfcmd[]      = { "tabbed", "-c", "surf", "-pe", NULL };

/* volume */
static const char *mutecmd[]    = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volupcmd[]   = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };

static Key keys[] = {
	/* modifier             key        function        argument */
	{ MODKEY|ShiftMask,     XK_Return, spawn,          {.v = termfloatcmd } }, // spawn a floating terminal
	{ MODKEY,	        	XK_d,      spawn,	       {.v = dmenucmd } }, // start dmenu_run
	{ MODKEY,               XK_Return, spawn,          {.v = termcmd } }, // spawn a terminal
	{ MODKEY,	        	XK_e,	   spawn,	       {.v = explorecmd } }, // spawn file manager
	{ MODKEY,               XK_w,      spawn,          {.v = surfcmd } }, // spawn web browser

	{ MODKEY|ShiftMask,     XK_t,      spawn,          CMD("/home/randy/bin/todo") }, // run dmenu todo script
	{ MODKEY|ControlMask,   XK_0,      spawn,          CMD("/home/randy/bin/goodbye") }, // run dmenu shutdown script
	{ MODKEY,               XK_p,      spawn,          CMD("/home/randy/bin/screenshot") }, // run dmenu screenshot script
/* { MODKEY|ControlMask,   XK_c,      spawn,          TERM("/home/randy/bin/cfg") }, // edit configs */

    /* volume cmds */
    { 0,      XF86XK_AudioMute,        spawn,          { .v = mutecmd } },
    { 0,      XF86XK_AudioLowerVolume, spawn,          { .v = voldowncmd } },
    { 0,      XF86XK_AudioRaiseVolume, spawn,          { .v = volupcmd } },

	{ MODKEY,		        XK_minus,  setgaps,        { .i = -1 } }, // reduce gaps
	{ MODKEY,   	        XK_equal,  setgaps,        { .i = +1 } }, // increase gaps

	{ MODKEY,               XK_b,      togglebar,      {0} }, // toggle bar
	{ MODKEY|ShiftMask,     XK_j,      rotatestack,    {.i = +1 } }, // move window down stack
	{ MODKEY|ShiftMask,     XK_k,      rotatestack,    {.i = -1 } }, // move window up stack
	{ MODKEY,               XK_j,      focusstack,     {.i = +1 } }, // focus window below current
	{ MODKEY,               XK_k,      focusstack,     {.i = -1 } }, // focus window above current
	{ MODKEY,               XK_h,      setmfact,       {.f = -0.05} }, // resize <<-
	{ MODKEY,               XK_i,      setmfact,       {.f = +0.05} }, // resize ->>
	{ MODKEY|ControlMask,   XK_Return, zoom,           {0} }, // send window to master
	{ MODKEY|ShiftMask,     XK_c,      killclient,     {0} }, // close window
	{ MODKEY|ShiftMask,     XK_q,      killclient,     {0} }, // close window
	{ MODKEY|Mod1Mask,      XK_F4,     quit,	       {0} }, // quit dwm
    { MODKEY|ShiftMask,     XK_r,      quit,           {1} }, // reload/restart dwm
	// { MODKEY,               XK_i,      incnmaster,     {.i = +1 } },
	// { MODKEY,               XK_d,      incnmaster,     {.i = -1 } },
	// { MODKEY,               XK_Tab,    view,           {0} },

    /* Layout manipulation */
	{ MODKEY,               XK_Tab,    cyclelayout,    {.i = -1 } }, // cycle layouts
	{ MODKEY|ShiftMask,     XK_Tab,    cyclelayout,    {.i = +1 } }, // cycle layouts backwards
	{ MODKEY,               XK_space,  setlayout,      {0} }, // swap between last two layouts
	{ MODKEY|ShiftMask,     XK_space,  togglefloating, {0} }, // toggle float focused window

    /* Switch to specific layouts */
	{ MODKEY,               XK_t,      setlayout,      {.v = &layouts[0]} }, // switch to tiled ([]=) layout
	{ MODKEY,               XK_f,      setlayout,      {.v = &layouts[2]} }, // switch to monocole ([M]) layout
	{ MODKEY,               XK_m,      setlayout,      {.v = &layouts[2]} }, // switch to monocole ([M]) layout
	{ MODKEY,               XK_g,      setlayout,      {.v = &layouts[3]} }, // switch to grid (HHH) layout

	{ MODKEY,               XK_0,      view,           {.ui = ~0 } }, // show all windows on all workspaces
	{ MODKEY|ShiftMask,     XK_0,      tag,            {.ui = ~0 } }, // pin focused window to all workspaces
	
	TAGKEYS(                  XK_1,          0)
	TAGKEYS(                  XK_2,          1)
	TAGKEYS(                  XK_3,          2)
	TAGKEYS(                  XK_4,          3)
	TAGKEYS(                  XK_5,          4)
	TAGKEYS(                  XK_6,          5)
	TAGKEYS(                  XK_7,          6)
	TAGKEYS(                  XK_8,          7)
	TAGKEYS(                  XK_9,          8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} }, // swap between last two layouts
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} }, // switch to monocle ([M]) layout
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} }, // send window to master
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } }, // spawn a terminal
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} }, // move window
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} }, // toggle float focused window
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} }, // resize window
	{ ClkTagBar,       0,           Button1,        view,           {0} }, // view workspace
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} }, // add workspace to current view
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} }, // move window to workspace
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} }, // pin window to workspace
};

