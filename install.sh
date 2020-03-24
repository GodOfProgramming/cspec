#!/bin/sh

if [ "$EUID" == '0' ]; then			
    echo "Installing shared lib into '$LIB_INSTALL_DIR'"	
		if [ -d "$LIB_INSTALL_DIR" ]; then
			install -D "$SHARED_LIBRARY" "$LIB_INSTALL_DIR/$SHARED_LIBRARY"
		else
			echo "The library installation '$LIB_INSTALL_DIR' directory does not exist"
			exit 1
		fi

		echo "Installing headers into '$INCLUDE_INSTALL_DIR'"
		if [ -d "$INCLUDE_INSTALL_DIR" ]; then
			cp -r "$INCLUDE/cspec" "$INCLUDE_INSTALL_DIR"
		else
			echo "The header installation '$INCLUDE_INSTALL_DIR' directory does not exist"
			exit 1
		fi
else
    echo "You must have root access to install"
		echo "Alternatively, change the install dir to something you own and remove this if check";
		exit 1
fi

