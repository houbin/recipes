#!/bin/bash

MY_DIR=$(dirname `readlink -f $0`)

cd ${MY_DIR}
cp -f root.conf /etc/init/
cp -f start-ttys.conf /etc/init/
