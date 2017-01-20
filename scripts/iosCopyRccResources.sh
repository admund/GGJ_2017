#!/bin/sh

PROJECT_PATH=$1
GENERATED_FILES_PATH=$2

echo [iOS] COPYING EXTERNAL IMAGES RCC RESOURCES...

cp $GENERATED_FILES_PATH/images_per_1_tablet10.rcc $PROJECT_PATH/deploy/ios/xcassets/Shared.xcassets/rcc_images_per_1.dataset/images_per_1_tablet10.rcc
cp $GENERATED_FILES_PATH/images_per_2_phone.rcc $PROJECT_PATH/deploy/ios/xcassets/Shared.xcassets/rcc_images_per_2.dataset/images_per_2_phone.rcc
cp $GENERATED_FILES_PATH/images_per_2_tablet10.rcc $PROJECT_PATH/deploy/ios/xcassets/Shared.xcassets/rcc_images_per_2.dataset/images_per_2_tablet10.rcc

echo [iOS] DONE COPYING EXTERNAL IMAGES RCC RESOURCES.
