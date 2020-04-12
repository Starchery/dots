/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static int fuzzy = 1;                      /* -F  option; if 0, dmenu doesn't use fuzzy matching     */
// static int ignorecase = 1;		  /* -i option; if 0, dmenu doesn't ignore case */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"GoMono Nerd Font:size=11"
};

static char *name = "dmenu";   /* -n  option; */
static char *class = "Dmenu";  /* -c  option; */

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */

// static const char col_gray1[]       = "#222222";
// static const char col_gray1[]       = "#1e1e1e";
static const char col_gray1[]       = "#000000";
// static const char col_gray2[]       = "#444444";
static const char col_gray2[]       = "#0c0c0c";
static const char col_gray3[]       = "#aaaaaa";
// static const char col_gray3[]       = "#ffffff";
// static const char col_gray4[]       = "#eeeeee";
static const char col_gray4[]       = "#ffffff";
// static const char col_cyan[]        = "#005577";
static const char col_cyan[]        = "#cf6a4c";
// static const char col_cyan[]        = "#9b859d";
static const char col_black[]       = "#000000";
static const char col_aqua[]        = "#00ffff";

static const unsigned int baralpha = 0xd0;

static const char *colors[SchemeLast][2] = {
	/*                  fg          bg   */
	[SchemeNorm] = { col_gray4,  col_gray1},
	[SchemeSel]  = { col_gray1,  col_gray4},
	[SchemeSelHighlight] = {col_cyan, col_gray4},
	[SchemeNormHighlight] = {col_cyan, col_gray1},
	[SchemeOut]  = { col_black,  col_aqua },
	[SchemeMid] = { col_gray4, col_gray2 },
	[SchemeMidHighlight] = { col_cyan, col_gray2 },
};

static const unsigned int alphas[][2]      = {
	/*                 fg      bg   */
	[SchemeNorm] = { OPAQUE, OPAQUE },
	[SchemeSel]  = { OPAQUE, OPAQUE },
	[SchemeSelHighlight] = {OPAQUE, OPAQUE},
	[SchemeNormHighlight] = {OPAQUE, OPAQUE},
	[SchemeOut]  = { OPAQUE, OPAQUE },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;
static unsigned int lineheight = 25;         /* -h option; minimum height of a menu line     */

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";

/*
 * Use prefix matching by default; can be inverted with the -x flag.
 */
static int use_prefix = 1;
