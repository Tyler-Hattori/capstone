#!/bin/bash

function WHITE_TEXT {
  printf "\033[1;37m"
}
function NORMAL_TEXT {
  printf "\033[0m"
}
function GREEN_TEXT {
  printf "\033[1;32m"
}
function RED_TEXT {
  printf "\033[1;31m"
}

WHITE_TEXT
echo "########################################################################################"
echo "# Building Pixymon...                                                                  #"
echo "########################################################################################"
NORMAL_TEXT

uname -a

TARGET_BUILD_FOLDER=../build

mkdir $TARGET_BUILD_FOLDER
mkdir $TARGET_BUILD_FOLDER/pixymon/
mkdir $TARGET_BUILD_FOLDER/pixymon/src
mkdir $TARGET_BUILD_FOLDER/pixymon/src/host

echo "Creating build folder..."
cp -r ../src/common             $TARGET_BUILD_FOLDER/pixymon/src
cp -r ../src/host/pixymon       $TARGET_BUILD_FOLDER/pixymon/src/host
cp ../src/host/buildpixymon.sh  $TARGET_BUILD_FOLDER/pixymon/

echo "Starting build..."
cd $TARGET_BUILD_FOLDER/pixymon
rm ./PixyMon
chmod +x buildpixymon.sh
./buildpixymon.sh

if [ -f ./PixyMon ]; then
  GREEN_TEXT
  printf "SUCCESS "
else
  RED_TEXT
  printf "FAILURE "
fi
NORMAL_TEXT
echo ""
