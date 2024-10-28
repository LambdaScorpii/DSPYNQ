#!/bin/bash
# Usage: bash create_venv.sh <name>
# Open the file and read the first line
read -r firstLine < venv_name.txt

# Store the line in a variable
venv_name="$firstLine"

# Function to activate virtual environment
activate_venv() {
    echo "Activating virtual environment located at $venv_name"
    source "$venv_name/bin/activate"
}

# Activate the virtual environment
activate_venv

# Check the pip executable path
echo "Using pip at $(which pip)"

# Install Requiremtns
pip install pip --upgrade
pip install -r requirements.txt

# Deactivate the virtual environment
deactivate

echo "Virtual environment deactivated. To activate continously type: source $venv_name/bin/activate"