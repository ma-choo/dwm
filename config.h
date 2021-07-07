/* patches
 *  attachbottom
 *  bottomstack
 *  focusmaster
 *  fullgaps
 *  hide vacant tags
 *  inplacerotate
 *  pertag
 *  push
 *  bar height
 */ 

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 32;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { 
	"Fira Sans:style=Medium:pixelsize=16:antilias=true:autohint=true",
	"JetBrains Mono Nerd Font:pixelsize=18:antialias=true:autohint=true" };
static const char black[]           = "#000000";
static const char grey[]            = "#3b3b3b";
static const char white[]           = "#d9d9d9";
static const char *colors[][3]      = {
	/*                     fg           bg           border   */
	[SchemeNorm]       = { white,       black,       grey },
	[SchemeSel]        = { white,       grey,        white },
	[SchemeNormVacant] = { grey,        black,       black },
	[SchemeSelVacant]  = { black,       grey,        black }
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       2,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol           arrange function */
	{ "[tile]",         tile },    /* first entry is default */
	{ "[monocle]",      monocle },
	{ "[bstackhoriz]",  bstackhoriz },
	{ "[float]",        NULL },    /* no layout function means floating behavior */
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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]  = { "dmenu_run", NULL };
static const char term[] = "st";
static const char *termcmd[]  = { term, NULL };
static const char *rangercmd[]  = { term, "-e", "ranger", NULL };
static const char *scrotcmd[]  = { "scrot", "~/pictures/scrot.png", NULL };
static const char *amixermute[] = { "bar_amixer", "-mute" };
static const char *amixerdec[] = { "bar_amixer", "-dec", "5" };
static const char *amixerinc[] = { "bar_amixer", "-inc", "5" };
static const char *xbacklightdec[]  = { "xbacklight", "-dec", "10", NULL };
static const char *xbacklightinc[]  = { "xbacklight", "-inc", "10", NULL };

static Key keys[] = {
	/* commands */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = rangercmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = scrotcmd } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = amixermute } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = amixerdec } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = amixerinc } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = xbacklightdec } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = xbacklightinc } },

	/* clients */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY|ControlMask,           XK_j,      inplacerotate,  {.i = +2 } },
	{ MODKEY|ControlMask,           XK_k,      inplacerotate,  {.i = -2 } },
	{ MODKEY,                       XK_g,      focusmaster,    {0} },
	{ MODKEY|ShiftMask,             XK_g,      zoom,           {0} }, /* zoom client to master */
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	/* layouts */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /* tile */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} }, /* monocle */
	{ MODKEY,                       XK_b,      setlayout,      {.v = &layouts[2]} }, /* bstackhoriz */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} }, /* float */
	{ MODKEY,                       XK_space,  setlayout,      {0} }, /* previous layout */

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
	{ MODKEY,                       XK_Tab,    view,           {0} }, /* previous tag */

	/* other */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -2 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +2 } },
	{ MODKEY,                       XK_grave,  showscratchpad, {0} },
	{ MODKEY|ShiftMask,             XK_grave,  setscratchpad,  {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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

