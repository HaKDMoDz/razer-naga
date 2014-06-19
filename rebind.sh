#!/bin/sh

rmmod hid-generic
rmmod naga
insmod naga.ko

for i in /sys/bus/usb/drivers/usbhid/1-*; do
    name=$(basename $i)
    echo $name
    echo $name > /sys/bus/usb/drivers/usbhid/unbind 
    echo $name > /sys/bus/usb/drivers/usbhid/bind 
done
