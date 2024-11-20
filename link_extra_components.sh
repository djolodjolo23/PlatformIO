#!/bin/bash

COMPONENTS_PATH="/home/dj/Documents/Developing-IoT-Projects-with-ESP32-2nd-edition-main-new/components" 

if [ -z "$1" ]; then
    echo "Usage: ./link_components.sh <path/to/lib>"
    exit 1
fi

LIB_PATH="$1"

mkdir -p "$LIB_PATH"


for dir in $COMPONENTS_PATH/*; do
    if [ -d "$dir" ]; then
        COMPONENT_NAME=$(basename "$dir")
        ln -sfn "$dir" "$LIB_PATH/$COMPONENT_NAME"
    fi
done

echo "All components have been linked!"
