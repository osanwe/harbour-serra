# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-serra

CONFIG += sailfishapp
QT += multimedia dbus

SOURCES += src/harbour-serra.cpp \
    src/yandexsearchhelper.cpp \
    src/googlesearchhelper.cpp \
    src/searchresultobject.cpp \
    src/yandexspeechkithelper.cpp \
    src/recorder.cpp

OTHER_FILES += qml/harbour-serra.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-serra.changes.in \
    rpm/harbour-serra.spec \
    rpm/harbour-serra.yaml \
    translations/*.ts \
    harbour-serra.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-serra-de.ts

DISTFILES += \
    qml/pages/SearchPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/AboutPage.qml \
    qml/views/SearchBox.qml

HEADERS += \
    src/yandexsearchhelper.h \
    src/googlesearchhelper.h \
    src/searchresultobject.h \
    src/yandexspeechkithelper.h \
    src/recorder.h

