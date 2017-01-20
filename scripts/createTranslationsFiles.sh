#!/bin/sh

LUPDATE_FULL_PATH=$1/lupdate
PROJECT_PATH=$2

echo GENERATING TRANSLATION FILES...

$LUPDATE_FULL_PATH -recursive -noobsolete -locations none $PROJECT_PATH -ts $PROJECT_PATH/assets/translations/translation.ts

echo DONE GENERATING TRANSLATION FILES.
