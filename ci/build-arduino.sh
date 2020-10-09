#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Enable the globstar shell option
shopt -s globstar

# Make sure we are inside the github workspace
cd $GITHUB_WORKSPACE

# Create directories
mkdir -p $HOME/Arduino
mkdir -p $HOME/Arduino/libraries

# Provide local libraries from submodules
cp -r lib/* $HOME/Arduino/libraries

# Install python2.7 with pyserial (needed by the espressif toolchain)
apt-get install python python-pip -y
pip install pyserial

# Install Arduino IDE
export PATH=$PATH:$GITHUB_WORKSPACE/bin
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

arduino-cli config init --additional-urls https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json

arduino-cli core update-index
arduino-cli core install m5stack:esp32

# Finally compile the sketch
arduino-cli compile --fqbn m5stack:esp32:m5stack-core2:PSRAM=enabled,PartitionScheme=default,CPUFreq=240,UploadSpeed=921600,DebugLevel=info 