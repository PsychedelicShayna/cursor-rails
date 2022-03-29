TEMPLATE = app
QT += core gui widgets

CONFIG += c++17

QMAKE_CXXFLAGS += /std:c++17

TARGET = cursor-rails

# Include hotkey recorder widget.
INCLUDEPATH += qt-hotkey-recorder-widget/source/
SOURCES     += qt-hotkey-recorder-widget/source/hotkey_recorder_widget.cpp
HEADERS     += qt-hotkey-recorder-widget/source/hotkey_recorder_widget.hpp

# Include VKID table widget.
INCLUDEPATH += qt-vkid-table-widget/source
SOURCES     += qt-vkid-table-widget/source/vkid_table_widget.cpp
HEADERS     += qt-vkid-table-widget/source/vkid_table_widget.hpp

SOURCES += \
    source/main.cpp \
    source/main_window_dialog.cxx

HEADERS += \
    source/main_window_dialog.hxx

FORMS += \
    source/main_window_dialog.ui

LIBS += user32.lib
