TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L ./usr/lib/x86_64-linux-gnu/

SOURCES += \
        analyze.c \
        cgen.c \
        cms.tab.c \
        lex.yy.c \
        main.c \
        symtab.c \
        target.c \
        util.c

DISTFILES += \
    cms.output \
    gcd.cms \
    sort.cms

HEADERS += \
    analyze.h \
    cgen.h \
    cms.l \
    cms.tab.h \
    cms.y \
    globals.h \
    parse.h \
    scan.h \
    symtab.h \
    target.h \
    util.h
