#!/bin/bash
echo "Updating Repository"
sudo apt update

echo "Installing Build dependencies"

sudo apt install -y build-essential zlib1g-dev libncurses5-dev libgdbm-dev \
libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev libbz2-dev liblzma-dev \
tk-dev uuid-dev

echo "creating tmp folder and download source"

mkdir tmp
cd tmp
wget https://www.python.org/ftp/python/3.12.3/Python-3.12.3.tar.xz

echo "extracting source"

tar -xf Python-3.12.3.tar.xz
cd Python-3.12.3

echo "configure and install"

./configure --enable-optimizations --enable-shared --prefix=/usr/local
make -j 4
sudo make altinstall



echo "Making available systemwide"

export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH
echo "export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH" >> ~/.bashrc
source ~/.bashrc
echo "/usr/local/lib" | sudo tee -a /etc/ld.so.conf.d/local_libs.conf
sudo ldconfig


# export PATH="/usr/local/bin:$PATH"
# source ~/.bashrc

echo "veryfying"

python3.12 --version

echo "cleaning up"

cd ../
sudo rm -rf Python-3.12.3 Python-3.12.3.tar.xz
cd ../
