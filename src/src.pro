QT += core

TARGET = cgFaceRecognition
CONFIG += staticlib warn_on debug_and_release debug_and_release_target
TEMPLATE = lib
VERSION	= 0.1.1

DEFINES += CGFACERECOGNITION_EXPORTS
INCLUDEPATH += $$(DLIBDIR)/include
QMAKE_CXXFLAGS_WARN_ON -= -w34100

HEADERS += cgfacerecognition.h \
	facedetection.h \
	face.h \
	face_p.h \
	facerecognition.h

SOURCES += facedetection.cpp \
	face.cpp \
	facerecognition.cpp
