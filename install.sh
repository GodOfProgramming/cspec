#!/bin/sh

# $1 = shared_library
# $2 = static_library
# $3 = lib directory
# $4 = include directory

shared_lib="$1"
static_lib="$2"
lib_dir="$3"
include_dir="$4"

if [ ! "$EUID" = '0' ]; then
  echo "You must have root access to install"
  echo "Alternatively, change the install dir to something you own and remove this if check";
  exit 1
fi

echo "Installing shared lib into '$lib_dir'"
if [ ! -d "$lib_dir" ]; then
  makedir -p "$lib_dir"
fi

install -D "bin/$shared_lib" "$lib_dir/$shared_lib"

echo "Installing headers into '$include_dir'"
if [ ! -d "$include_dir" ]; then
  mkdir -p "$include_dir"
fi

cp -r "include/cspec" "$include_dir"

ldconfig
