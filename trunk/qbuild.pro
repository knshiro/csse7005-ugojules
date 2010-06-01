# This is an application
TEMPLATE=app

# The binary name
TARGET=assignment5

# This app uses Qtopia
CONFIG+=qtopia

# This is the bluetooth comm library
QTOPIA*=comm audio

# Build this app as a quicklauncher plugin
# You need to be using the QTOPIA_ADD_APPLICATION/QTOPIA_MAIN macros or this will not work!
#CONFIG+=quicklaunch

# Build this project into the singleexec binary
#CONFIG+=singleexec

# These are the source files that get built to create the application
FORMS  = neoconnection.ui \
viewcontactform.ui \
	addcontactform.ui \
        selectcallform.ui \
        phonebookform.ui \
	audiodialogform.ui
HEADERS=protocols.h \
        neoconnection.h \
neophonebookentry.h \
        neophonebook.h \
	viewcontactdialog.h \
        addcontactdialog.h \
	selectcalldialog.h \
        accelthread.h \
        phonebookdialog.h \
	vibledthread.h \
	audiodialog.h \
        playaudiothread.h \
        custompushbutton.h \
	ringpattern.h
SOURCES=neoconnection.cpp \
        neophonebookentry.cpp \ 
        neophonebook.cpp \
	    viewcontactdialog.cpp \
        addcontactdialog.cpp \
        phonebookdialog.cpp \
	    selectcalldialog.cpp \
        accelthread.cpp \
	    vibledthread.cpp \
        playaudiothread.cpp \
	    ringpattern.cpp \
        audiodialog.cpp \
        custompushbutton.cpp \
        main.cpp

# SXE information
target.hint=sxe
target.domain=untrusted

# Desktop application icon
desktop.files=assignment5.desktop
desktop.path=/apps/Applications
desktop.hint=desktop

INSTALLS+=desktop

# Package creating details
pkg.name=assignment5
pkg.desc=Assignment 5 Client
pkg.domain=trusted

requires(enable_bluetooth)
