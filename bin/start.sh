#!/bin/sh
/usr/bin/cage -s -- /usr/bin/chromium --kiosk http://localhost:8080/ &
sleep 3
export WAYLAND_DISPLAY=wayland-0
wlr-randr --output HDMI-A-1 --mode 3840x2160@60 || echo "start.sh: 4K60 unavailable, using EDID default"
wlrctl pointer move 4000 4000
wait
