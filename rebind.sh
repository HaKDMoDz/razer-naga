#!/bin/sh

if [[ $EUID -ne 0 ]]; then
   echo "You are not root."
   exit 1
fi

rmmod hid-generic
rmmod naga
insmod naga.ko

base=/sys/bus/usb/drivers/usbhid/

check_id() {
    for i in $1/*; do
	if [[ $i =~ 1532:0040\.[0-9]{4} ]]; then
	    return 0
	fi
    done
    return 1
}

for i in $base/*; do
    name=$(basename $i)
    if [[ $name =~ ^[0-9]\- ]]; then
	if check_id $i; then
	    echo "Naga: $name"
	fi
	echo $name > /sys/bus/usb/drivers/usbhid/unbind 
	echo $name > /sys/bus/usb/drivers/usbhid/bind 
    fi
done
