TEMPLATE = app
CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    app.cpp \
    torneo.cpp \
    repositorio.cpp \
    simulador.cpp \
    medidor.cpp

HEADERS += \
    app.h \
    torneo.h \
    repositorio.h \
    simulador.h \
    medidor.h