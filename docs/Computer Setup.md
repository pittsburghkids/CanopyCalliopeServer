## Raspberry Pi Image

Use `Raspberry Pi OS Lite (64-bit)`

## Initial Setup

```
sudo apt-get -y update
sudo apt-get -y upgrade
```

## Install Software

```
sudo apt-get -y install cage chromium xwayland nginx git wlrctl
sudo chmod +s /usr/bin/cage
```

## Pull Repository

`git clone git@github.com:pittsburghkids/CanopyCalliopeServer.git`

## Link Configuration Files

```
sudo ln -s /home/pi/CanopyCalliopeServer/etc/systemd/system/cage@.service /etc/systemd/system/cage@tty1.service

sudo ln -s /home/pi/CanopyCalliopeServer/etc/pam.d/pi /etc/pam.d/pi

sudo ln -s /home/pi/CanopyCalliopeServer/etc/nginx/conf.d/canopycalliope.conf /etc/nginx/conf.d/canopycalliope.conf
```

## Start Services

```
sudo systemctl enable cage@tty1.service
sudo systemctl set-default graphical.target

sudo systemctl enable nginx
```

## Set Permissions

`sudo chmod -R 755 /home/pi`

## Enable Overlay

```
sudo raspi-config nonint do_overlayfs 0
sudo reboot

```
