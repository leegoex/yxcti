#!/bin/sh

# Install the dependencies for compiling
yum groupinstall 'Development Tools' -y
yum install libevent2 libevent2-devel openssl openssl-devel python-devel libcurl libcurl-devel -y

# Compile and install hiredis
tar -xzvf hiredis-0.13.3.tar.gz
cd hiredis-0.13.3
sed -i 's/usr\/local/usr/g' Makefile
make
make install
cd ..

# Compile and install opus
tar -xzvf opus-1.1.4.tar.gz
cd opus-1.1.4
./configure --prefix=/usr
make
make install
cd ..

# Compile and install speex
tar -xzvf speex-1.2.0.tar.gz
cd speex-1.2.0
./configure --prefix=/usr
make
make install
cd ..

# Compile and install sems
tar -xzvf sems-1.6.0.tar.gz
cp -v AmAudio.cpp sems-1.6.0/core/
cd sems-1.6.0
make
make install
cd ..

cp -v sems.conf /usr/local/etc/sems
cp -v sbc.conf /usr/local/etc/sems/etc
cp -v symmetricrtp.sbcprofile.conf /usr/local/etc/sems/etc

mkdir -p /var/local/run

if [ -d "/usr/lib64" ]; then
  cp -vd /usr/lib/libopus.* /usr/lib64/
fi
