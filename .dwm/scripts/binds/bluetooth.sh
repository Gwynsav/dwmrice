#!/bin/dash
stt=$(bluetoothctl show | grep "Powered:") && stt=${stt##* }
[ "$stt" = "yes" ] && pwr="off" || pwr="on"
[ "$stt" = "yes" ] && txt="off" || txt="on"
bluetoothctl power "$pwr"
dunstify -h string:x-dunst-stack-tag:blue \
         -i "$HOME/.local/share/icons/Reversal-dark/devices/22/bluetooth.svg" \
         "Bluetooth is $txt"
$HOME/.dwm/scripts/refbar
