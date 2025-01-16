#!/bin/bash

cd /usr/src/kernel-source-2.4.27/

make mrproper
make menuconfig
make dep
make clean
make bzImage
