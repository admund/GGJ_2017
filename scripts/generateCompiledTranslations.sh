#!/bin/sh

LRELEASE_FULL_PATH=$1/lrelease
PROJECT_PATH=$2

echo COMPILING TRANSLATION FILES...

$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+pl/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+cs/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+de/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+es/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+fr/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+it/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+pt/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+ru/translation.ts
$LRELEASE_FULL_PATH $PROJECT_PATH/assets/translations/+tr/translation.ts

echo DONE COMPILING TRANSLATION FILES.
