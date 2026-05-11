QT       += core gui widgets

TARGET    = OnlineShop
TEMPLATE  = app

CONFIG   += c++11
CONFIG   -= console
CONFIG   += windows

SOURCES += \
    main.cpp \
    product.cpp \
    product_types.cpp \
    customer.cpp \
    order.cpp \
    warehouse.cpp \
    shop_manager.cpp \
    mainwindow.cpp

HEADERS += \
    shop_types.h \
    product.h \
    product_types.h \
    customer.h \
    order.h \
    warehouse.h \
    shop_manager.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Ogohlantirishlarni yoqish
QMAKE_CXXFLAGS += -Wall -Wextra
