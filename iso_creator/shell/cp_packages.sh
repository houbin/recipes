#!/bin/bash

ISO_DIR=/mnt/create_iso/disk
RPM_LIST_FILE=rpm.list

mount | grep /mnt/cdrom
if [ $? -ne 0 ];
then
    echo "cdrom not mount"
    exit
fi

if [ ! -d ${ISO_DIR} ];then
    echo "mkdir iso dir not found"
    exit
fi

for i in $(cat ${RPM_LIST_FILE})
do
    cp /mnt/cdrom/Packages/${i}.rpm ${ISO_DIR}/Packages/
    [ $? != 0 ] && echo "copy ${i} failed"
done
