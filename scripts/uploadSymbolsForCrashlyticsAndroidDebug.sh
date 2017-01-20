#!/bin/sh

#TODO get <ANDROID_BUILD_FOLDER> parameter from input

cd ../build-GameDesire-Android_dla_armeabi_v7a_GCC_4_9_Qt_5_7_0-Debug/android-build
./gradlew crashlyticsUploadSymbolsDebug