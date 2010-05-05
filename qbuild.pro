# This is an application
TEMPLATE=app

# The binary name
TARGET=assignment4

# This app uses Qtopia
CONFIG+=qtopia

QTOPIA*=audio

# Build this app as a quicklauncher plugin
# You need to be using the QTOPIA_ADD_APPLICATION/QTOPIA_MAIN macros or this will not work!
#CONFIG+=quicklaunch

# Build this project into the singleexec binary
#CONFIG+=singleexec

# These are the source files that get built to create the application
FORMS  =viewcontactform.ui \
	addcontactform.ui \
        selectcallform.ui \
        phonebookform.ui
HEADERS=neophonebookentry.h \
        neophonebook.h \
	viewcontactdialog.h \
        addcontactdialog.h \
	selectcalldialog.h \
        phonebookdialog.h \
	vibledthread.h \
    playaudiothread.h \
	ringpattern.h
SOURCES=neophonebookentry.cpp \ 
        neophonebook.cpp \
	    viewcontactdialog.cpp \
        addcontactdialog.cpp \
        phonebookdialog.cpp \
	    selectcalldialog.cpp \
	    vibledthread.cpp \
        playaudiothread.cpp \
	    ringpattern.cpp \
        main.cpp

# SXE information
target.hint=sxe
target.domain=untrusted

