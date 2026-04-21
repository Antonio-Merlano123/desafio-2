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
    medidor.cpp \
    equipo.cpp \
    jugador.cpp \
    partido.cpp

HEADERS += \
    app.h \
    torneo.h \
    repositorio.h \
    simulador.h \
    medidor.h \
    equipo.h \
    jugador.h \
    partido.h