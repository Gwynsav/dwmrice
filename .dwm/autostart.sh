#!/bin/dash
xsetroot -cursor_name left_ptr &
hsetroot -solid '#323949' &
killall dunst; dunst &
killall bardata; $HOME/.dwm/scripts/bardata &

killall openrgb; openrgb -p kizu &
