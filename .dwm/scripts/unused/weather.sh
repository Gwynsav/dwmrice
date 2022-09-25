#!/bin/sh
sleep 15.0; 

KEY=""
wttr=$(curl -sf "api.openweathermap.org/data/2.5/weather?lat=YOURLATITUDE&lon=YOURLONGITUDE&appid=$KEY&units=metric")
wdesc=$(echo $wttr | jq -r ".weather[0].main")
wtemp=$(echo $wttr | jq ".main.temp") && wtemp=${wtemp%%.*}
wfeel=$(echo $wttr | jq ".main.feels_like") && wfeel=${wfeel%%.*}
time=$(date '+%H')

if [ -z "$wdesc" ]; then
	echo " "
elif [ "$wdesc" = "Clouds" ]; then
	[ $time -gt 20 -o $time -lt 08 ] && wicon=" " || wicon=" "
elif [ "$wdesc" = "Clear" ]; then
	[ $time -gt 20 -o $time -lt 08 ] && wicon=" " || wicon=" "
elif [ "$wdesc" = "Rain" ]; then
	[ $time -gt 20 -o $time -lt 08 ] && wicon=" " || wicon=" "
fi

[ -z "$wtemp" ] && wtempd="n/a" || wtempd="$wtemp°C"
[ -z "$wtemp" ] && wfeeld="n/a" || wfeeld="$wfeel°C"

echo "$wicon $wtempd ($wfeeld)"

sleep 900.0;
