#!/bin/dash
case $1 in
    "up") var="+" ;;
    "down") var="-" ;;
esac

ftc=$(brightnessctl -l) 
nam=${ftc#*\'} && nam=${nam%%\'*}
brightnessctl -d "$nam" set 5%$var

stt=$(brightnessctl -d "$nam") && stt=${stt##*(} && stt=${stt%%%*}
dunstify -h string:x-dunst-stack-tag:brightness \
    -i "$HOME/.local/share/icons/Reversal-dark/status/22/notification-display-brightness.svg" \
    "Display Brightness set to $stt%"
$HOME/.dwm/scripts/refbar
