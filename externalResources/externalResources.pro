TEMPLATE = aux

# create .ts files
createTranslationsFiles.commands = $$PWD/../scripts/createTranslationsFiles.sh $$[QT_HOST_BINS] $$PWD/../client

# create .qm files from .ts files
generateCompiledTranslations.commands = $$PWD/../scripts/generateCompiledTranslations.sh $$[QT_HOST_BINS] $$PWD/../client
generateCompiledTranslations.depends = createTranslationsFiles

# create .rcc files
createExternalResources.commands = $$PWD/../scripts/createExternalResources.sh $$[QT_HOST_BINS] $$PWD/../client $$PWD/generated/rcc
createExternalResources.depends = generateCompiledTranslations

ios {
    # iOS copy .rcc files into .xcassets bundle
    iosCopyRccResources.commands = $$PWD/../scripts/iosCopyRccResources.sh $$PWD/../client $$PWD/generated/rcc
    iosCopyRccResources.depends = createExternalResources

    first.depends = $(first) iosCopyRccResources createExternalResources generateCompiledTranslations createTranslationsFiles
    QMAKE_EXTRA_TARGETS += first iosCopyRccResources createExternalResources generateCompiledTranslations createTranslationsFiles
}
!ios {
    first.depends = $(first) createExternalResources generateCompiledTranslations createTranslationsFiles
    QMAKE_EXTRA_TARGETS += first createExternalResources generateCompiledTranslations createTranslationsFiles
}

QMAKE_CLEAN = $$PWD/generated/rcc/* \
    $$PWD/../poker/deploy/ios/xcassets/Shared.xcassets/rcc_images_per_1.dataset/*.rcc \
    $$PWD/../poker/deploy/ios/xcassets/Shared.xcassets/rcc_images_per_2.dataset/*.rcc
