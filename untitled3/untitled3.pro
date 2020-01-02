QT       += core gui
QT       += multimedia
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    label_click.cpp \
    main.cpp \
    mainwindow.cpp \
    slider.cpp

HEADERS += \
    database.h \
    label_click.h \
    mainwindow.h \
    slider.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    ../../Pictures/Saved Pictures/16920916207_9dccf15ef1_o-1400x930.jpg \
    ../../Pictures/Saved Pictures/icon/folder-invoices.png \
    ../../Pictures/Saved Pictures/icon/folder-invoices.png \
    ../../Pictures/Saved Pictures/icon/icons8-1st-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-1st-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-end-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-end-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-n-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-n-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-pause-squared-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-pause-squared-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-play-button-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-play-button-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-replay-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-replay-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-shuffle-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-shuffle-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-singing-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-singing-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-skip-to-start-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-skip-to-start-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-wish-list-50.png \
    ../../Pictures/Saved Pictures/icon/icons8-wish-list-50.png \
    C:/Users/s7871/Pictures/Saved Pictures/16920916207_9dccf15ef1_o-1400x930.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/16920916207_9dccf15ef1_o-1400x930.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/43678226495_8fa7997ed0_o-1400x933.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/43678226495_8fa7997ed0_o-1400x933.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/46808914365_c7e3ab9153_o-1400x1049.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/46808914365_c7e3ab9153_o-1400x1049.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/DSC07827mm.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/DSC07827mm.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/StockSnap_2OFIOYTTWR-1400x904.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/StockSnap_2OFIOYTTWR-1400x904.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/binoculars-fog-foggy-1136815-1400x863.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/binoculars-fog-foggy-1136815-1400x863.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/dark-dirt-road-with-sign-1400x934.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/dark-dirt-road-with-sign-1400x934.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/gear-4606749_1280.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/gear-4606749_1280.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/hiking-icelands-fields_4460x4460-1400x933.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/hiking-icelands-fields_4460x4460-1400x933.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/maxime-staudenmann-122479.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/maxime-staudenmann-122479.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/woman-wanderer_4460x4460-1400x933.jpg \
    C:/Users/s7871/Pictures/Saved Pictures/woman-wanderer_4460x4460-1400x933.jpg
