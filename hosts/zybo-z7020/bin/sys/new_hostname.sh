#!bin/bash

read -p "Enter new Hostname: " host_name

sudo hostnamectl set-hostname $host_name

echo hostname

echo "Please reboot your system"