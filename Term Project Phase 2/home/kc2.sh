#!/bin/bash

make modules
make modules_install

cp arch/i386/boot/bzImage /boot/bzImage-2.4.27-10
cp System.map /boot/System.map-2.4.27-10
mkinitrd -o /boot/initrd-2.4.27-10 /lib/modules/2.4.27-10
reboot
