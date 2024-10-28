#!/bin/bash
# Usage: bash create_venv.sh <name>
# Open the file and read the first line
read -r firstLine < venv_name.txt

# Store the line in a variable
venv_name="$firstLine"

echo "creating venv $1"
python3 -m venv $venv_name --system-site-packages
