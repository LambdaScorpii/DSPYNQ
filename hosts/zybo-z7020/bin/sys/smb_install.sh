#!/bin/bash

# Define the shared directory and the Samba share name
SHARE_NAME="ZyboSwap"
SHARE_PATH="/home/py/swap"

echo "Installing Samba..."
sudo apt install -y samba samba-common-bin

echo "Creating shared directory at ${SHARE_PATH}..."
mkdir -p "${SHARE_PATH}"
chmod 0777 "${SHARE_PATH}"

echo "Configuring Samba..."
# Backup the original smb.conf file
sudo cp /etc/samba/smb.conf /etc/samba/smb.conf.backup

# Add the new share section at the end of the smb.conf file
echo "
[${SHARE_NAME}]
   comment = Pi Shared Folder
   path = ${SHARE_PATH}
   browseable = yes
   writeable = Yes
   only guest = no
   create mask = 0777
   directory mask = 0777
   public = yes
" | sudo tee -a /etc/samba/smb.conf > /dev/null

echo "Setting up a Samba password for the pi user..."
sudo smbpasswd -a pi  # Sets the Samba password

echo "Restarting Samba service..."
sudo systemctl restart smbd

echo "Samba setup complete. The share '${SHARE_NAME}' is accessible from the network."
