#!/bin/sh

# Install the dependencies for compiling hiredis and rtpengine
yum install pkgconfig glib2 glib2-devel zlib zlib-devel openssl openssl-devel pcre pcre-devel xmlrpc-c xmlrpc-c-devel libpcap libpcap-devel libevent2 libevent2-devel -y
yum groupinstall 'Development Tools' -y

# Compile and install hiredis
unzip hiredis-master.zip
cd hiredis-master
sed -i 's/usr\/local/usr/g' Makefile
make && make install
cd ..

# Compile and install rtpengine
unzip rtpengine-master.zip
## Compile and install daemon
cd rtpengine-master/daemon
sed -i 's/-std=c99/-std=gnu99/g' Makefile
make
cp -v rtpengine /usr/sbin
cd ..
## Compile and install iptables-extension
cd iptables-extension
yum install iptables-devel -y
make
cp -v libxt_RTPENGINE.so /lib/xtables/
cd ..
## Compile and install kernel-module
cd kernel-module
yum install kernel-devel kernel-headers -y
updatever=$(rpm -q kernel-headers)
ln -svf /usr/src/kernels/${updatever:15}/ /lib/modules/$(uname -r)/build
make
cp -v xt_RTPENGINE.ko /lib/modules/$(uname -r)/updates
depmod -a
modprobe xt_RTPENGINE
cd ..


