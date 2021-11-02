#!/bin/bash

umount ./lofsdisk
[ -e lofs.img ] && rm lofs.img
[ ! -z "$device" ] && losetup --detach $device

sudo fallocate -l 50M lofs.img
sudo losetup -f lofs.img

device=$(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1)

sudo mkfs.ext4 $device
[ -d lofsdisk ] || mkdir lofsdisk
sudo mount $device ./lofsdisk

