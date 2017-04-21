TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += \
    main_real_1.cpp \
    main_real_2.cpp \
    main_real_3.cpp \
    main_real_3_new.cpp \
    main_real_5_new.cpp \
    main_real_5.cpp \
    main_real_6.cpp \
    main_real_5_new_2.cpp \
    main_example_2.cpp \
    main_example_1.cpp \
    main_real_4.cpp

include(deployment.pri)
qtcAddDeployment()

