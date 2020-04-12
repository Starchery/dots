#!/bin/sh

# Import the colors
. "${XDG_CACHE_HOME}/wal/colors.sh"

dmenu_run -nb "$color0" -nf "$color15" -sb "$color1" -sf "$color15" -p "Run:"
