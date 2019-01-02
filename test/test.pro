QT += core testlib

TARGET = cgFaceRecognitionTest
CONFIG += testcase 

TEMPLATE = app

HEADERS += facerecognitiontest.h
	
SOURCES += main.cpp \
	facerecognitiontest.cpp

INCLUDEPATH += ../src \
	../.

CONFIG(debug, debug|release) {
    LIBS += -L../src/debug -lcgFaceRecognition0
    PRE_TARGETDEPS += ../src/debug/cgFaceRecognition0.dll
}
else {
    LIBS += -L../src/release -lcgFaceRecognition0
    PRE_TARGETDEPS += ../src/release/cgFaceRecognition0.dll
}