QT += core testlib

TARGET = cgFaceRecognitionTest
CONFIG += testcase warn_on debug_and_release debug_and_release_target

TEMPLATE = app

HEADERS += facerecognitiontest.h
	
SOURCES += main.cpp \
	facerecognitiontest.cpp

INCLUDEPATH += ../src \
	../.

CONFIG(debug, debug|release) {
	LIBS += -L$$(DLIBDIR)/lib -ldlib19.16.0_debug_64bit_msvc1900
    LIBS += -L../src/debug -lcgFaceRecognition
    PRE_TARGETDEPS += ../src/debug/cgFaceRecognition.lib
}
else {
	LIBS += -L$$(DLIBDIR)/lib -ldlib19.16.0_release_64bit_msvc1900
    LIBS += -L../src/release -lcgFaceRecognition
    PRE_TARGETDEPS += ../src/release/cgFaceRecognition.lib
}

