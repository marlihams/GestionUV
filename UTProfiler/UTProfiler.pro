#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T19:02:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTProfiler
TEMPLATE = app


SOURCES += main.cpp\
        mainutprofiler.cpp \
    uvadddialog.cpp \
    dialogupdatedeleteuv.cpp \
    formationdialog.cpp \
    updatedeleteformation.cpp \
    uv_formationdialog.cpp \
    UTProfiler.cpp \
    dossier.cpp \
    Iinscription.cpp \
    ConsultDossier.cpp \
    AutoCompletionAlgo.cpp \
    UVsAsTableView.cpp \
    ViewFormationTable.cpp

HEADERS  += mainutprofiler.h \
    uvadddialog.h \
    dialogupdatedeleteuv.h \
    formationdialog.h \
    updatedeleteformation.h \
    uv_formationdialog.h \
    UTProfiler.h \
    dossier.h \
    Inscription.h \
    ConsultDossier.h \
    AutoCompletionAlgo.h \
    UVsAsTableView.h \
    ViewFormationTable.h

FORMS    += mainutprofiler.ui \
    uvadddialog.ui \
    dialogupdatedeleteuv.ui \
    formationdialog.ui \
    updatedeleteformation.ui \
    uv_formationdialog.ui \
    dossier.ui \
    Inscription.ui \
    ConsultDossier.ui \
    AutoCompletionAlgo.ui \
    UVsAsTableView.ui \
    ViewFormationTable.ui

RESOURCES += \
    UTProfiler.qrc
