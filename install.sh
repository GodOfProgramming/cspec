#!/bin/bash

if [[ "$EUID" -eq 0 ]]; then			
    echo "Installing into '$INSTALL_DIR'"	
    mkdir -p "$INSTALL_DIR"
    install "$SHARED_LIBRARY" "$INSTALL_DIR/$SHARED_LIBRARY"
    echo "Make sure to add '$INSTALL_DIR' to your path!"
else
    echo "You must have root access to install";
fi

