#!/bin/bash

if [[ "$EUID" -eq 0 ]]; then			
    echo "Installing into '$INSTALL_DIR'"	
    mkdir -p "$INSTALL_DIR"
    install "$SHARED_LIBRARY" "$INSTALL_DIR/$SHARED_LIBRARY"
else
    echo "You must have root access to install";
fi

