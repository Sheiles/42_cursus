#!/bin/bash

echo "Downloading Unity testing framework..."

# Create unity directory if it doesn't exist
mkdir -p unity

# Download Unity files
curl -o unity/unity.c https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.c
curl -o unity/unity.h https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity.h
curl -o unity/unity_internals.h https://raw.githubusercontent.com/ThrowTheSwitch/Unity/master/src/unity_internals.h

echo "Unity framework downloaded successfully!"
