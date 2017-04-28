#!/bin/sh
killall -9 turnserver
killall -9 rtpengine
killall -9 kamailio
# /home/CloudShare/sbin/rtpengine --interface=192.168.18.77!120.31.128.53 --listen-udp=2222 --listen-ng=2223 --tos=184 -m 16384 -M 20480 --pidfile=/var/run/rtpengine.pid -f --log-level=7 --log-stderr --foreground
/home/CloudShare/sbin/rtpengine --interface=192.168.18.77!120.31.128.53 --listen-udp=2222 --listen-ng=2223 --tos=184 -m 16384 -M 20480 --pidfile=/var/run/rtpengine.pid -f --log-level=7
# 启动turnserver时，使用的配置文件是/usr/local/etc/turnserver.conf
/usr/local/bin/turnserver &
# ...
/home/CloudShare/sbin/kamailio start
