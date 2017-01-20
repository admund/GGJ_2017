#!/bin/sh

RCC_FULL_PATH=$1/rcc
PROJECT_PATH=$2
GENERATED_FILES_PATH=$3

mkdir -p $GENERATED_FILES_PATH

echo UPDATING EXTERNAL RESOURCES...

$RCC_FULL_PATH -binary $PROJECT_PATH/assets/qml/_qml.qrc -o $GENERATED_FILES_PATH/qml.rcc
$RCC_FULL_PATH -binary $PROJECT_PATH/assets/fonts/_fonts.qrc -o $GENERATED_FILES_PATH/fonts.rcc
$RCC_FULL_PATH -binary $PROJECT_PATH/assets/translations/_translations.qrc -o $GENERATED_FILES_PATH/translations.rcc

$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/anySize/_images_x1.qrc -o $GENERATED_FILES_PATH/images_any_1.rcc
$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/anySize/_images_x2.qrc -o $GENERATED_FILES_PATH/images_any_2.rcc
$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/oneSize/_images_xx.qrc -o $GENERATED_FILES_PATH/images_one_x.rcc
$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/perSize/+tablet10/_images_x1.qrc -o $GENERATED_FILES_PATH/images_per_1_tablet10.rcc
#$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/perSize/+tablet7/_images_x1.qrc -o $GENERATED_FILES_PATH/images_per_1_tablet7.rcc # TODO Android
$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/perSize/_images_x1.qrc -o $GENERATED_FILES_PATH/images_per_1_phone.rcc
$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/perSize/+tablet10/_images_x2.qrc -o $GENERATED_FILES_PATH/images_per_2_tablet10.rcc
#$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/perSize/+tablet7/_images_x2.qrc -o $GENERATED_FILES_PATH/images_per_2_tablet7.rcc # TODO Android
$RCC_FULL_PATH -binary -no-compress $PROJECT_PATH/assets/images/perSize/_images_x2.qrc -o $GENERATED_FILES_PATH/images_per_2_phone.rcc

echo DONE UPDATING EXTERNAL RESOURCES.
