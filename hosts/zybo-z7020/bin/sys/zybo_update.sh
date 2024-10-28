#!/bin/bash
echo "Starting Zybo Z7 update and upgrade..."
sudo apt update
sudo apt full-upgrade
sudo apt autoremove
sudo apt clean
sudo reboot
echo "System update and upgrade complete. A reboot is recommended."