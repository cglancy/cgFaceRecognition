QT += core

TARGET = cgFaceRecognition
CONFIG += dll warn_on debug_and_release debug_and_release_target
TEMPLATE = lib
VERSION	= 0.1.1

DEFINES += CGFACERECOGNITION_EXPORTS
INCLUDEPATH += $$(DLIBDIR)/include
QMAKE_CXXFLAGS_WARN_ON -= -w34100

CONFIG(debug, debug|release) {
	LIBS += -L$$(DLIBDIR)/lib -ldlib19.16.0_debug_64bit_msvc1900
}
else {
	LIBS += -L$$(DLIBDIR)/lib -ldlib19.16.0_release_64bit_msvc1900
}

HEADERS += cgfacerecognition.h \
	facedetection.h \
	face.h \
	face_p.h \
	facerecognition.h

SOURCES += facedetection.cpp \
	face.cpp \
	facerecognition.cpp
