QT += core

TARGET = cgFaceRecognition
CONFIG += dll
TEMPLATE = lib
VERSION	= 0.1.1

INCLUDEPATH += ../dlib \
	../dlib/dlib/external/libpng \
	../dlib/dlib/external/libjpeg \
	../dlib/dlib/external/zlib

HEADERS += cgfacerecognition.h \
	facedetection.h

SOURCES += facedetection.cpp \
	../dlib/dlib/all/source.cpp \
	../dlib/dlib/external/libjpeg/jcapimin.cpp \
	../dlib/dlib/external/libjpeg/jcapistd.cpp \
	../dlib/dlib/external/libjpeg/jccoefct.cpp \
	../dlib/dlib/external/libjpeg/jccolor.cpp \
	../dlib/dlib/external/libjpeg/jcdctmgr.cpp \
	../dlib/dlib/external/libjpeg/jchuff.cpp \
	../dlib/dlib/external/libjpeg/jcinit.cpp \
	../dlib/dlib/external/libjpeg/jcmainct.cpp \
	../dlib/dlib/external/libjpeg/jcmarker.cpp \
	../dlib/dlib/external/libjpeg/jcmaster.cpp \
	../dlib/dlib/external/libjpeg/jcomapi.cpp \
	../dlib/dlib/external/libjpeg/jcparam.cpp \
	../dlib/dlib/external/libjpeg/jcphuff.cpp \
	../dlib/dlib/external/libjpeg/jcprepct.cpp \
	../dlib/dlib/external/libjpeg/jcsample.cpp \
	../dlib/dlib/external/libjpeg/jdapimin.cpp \
	../dlib/dlib/external/libjpeg/jdapistd.cpp \
	../dlib/dlib/external/libjpeg/jdatadst.cpp \
	../dlib/dlib/external/libjpeg/jdatasrc.cpp \
	../dlib/dlib/external/libjpeg/jdcoefct.cpp \
	../dlib/dlib/external/libjpeg/jdcolor.cpp \
	../dlib/dlib/external/libjpeg/jddctmgr.cpp \
	../dlib/dlib/external/libjpeg/jdhuff.cpp \
	../dlib/dlib/external/libjpeg/jdinput.cpp \
	../dlib/dlib/external/libjpeg/jdmainct.cpp \
	../dlib/dlib/external/libjpeg/jdmarker.cpp \
	../dlib/dlib/external/libjpeg/jdmaster.cpp \
	../dlib/dlib/external/libjpeg/jdmerge.cpp \
	../dlib/dlib/external/libjpeg/jdphuff.cpp \
	../dlib/dlib/external/libjpeg/jdpostct.cpp \
	../dlib/dlib/external/libjpeg/jdsample.cpp \
	../dlib/dlib/external/libjpeg/jerror.cpp \
	../dlib/dlib/external/libjpeg/jfdctflt.cpp \
	../dlib/dlib/external/libjpeg/jfdctfst.cpp \
	../dlib/dlib/external/libjpeg/jfdctint.cpp \
	../dlib/dlib/external/libjpeg/jidctflt.cpp \
	../dlib/dlib/external/libjpeg/jidctfst.cpp \
	../dlib/dlib/external/libjpeg/jidctint.cpp \
	../dlib/dlib/external/libjpeg/jidctred.cpp \
	../dlib/dlib/external/libjpeg/jmemmgr.cpp \
	../dlib/dlib/external/libjpeg/jmemnobs.cpp \
	../dlib/dlib/external/libjpeg/jquant1.cpp \
	../dlib/dlib/external/libjpeg/jquant2.cpp \
	../dlib/dlib/external/libjpeg/jutils.cpp \
	../dlib/dlib/external/libpng/png.c \
	../dlib/dlib/external/libpng/pngerror.c \
	../dlib/dlib/external/libpng/pngget.c \
	../dlib/dlib/external/libpng/pngmem.c \
	../dlib/dlib/external/libpng/pngpread.c \
	../dlib/dlib/external/libpng/pngread.c \
	../dlib/dlib/external/libpng/pngrio.c \
	../dlib/dlib/external/libpng/pngrtran.c \
	../dlib/dlib/external/libpng/pngrutil.c \
	../dlib/dlib/external/libpng/pngset.c \
	../dlib/dlib/external/libpng/pngtrans.c \
	../dlib/dlib/external/libpng/pngwio.c \
	../dlib/dlib/external/libpng/pngwrite.c \
	../dlib/dlib/external/libpng/pngwtran.c \
	../dlib/dlib/external/libpng/pngwutil.c \
	../dlib/dlib/external/zlib/adler32.c \
	../dlib/dlib/external/zlib/compress.c \
	../dlib/dlib/external/zlib/crc32.c \
	../dlib/dlib/external/zlib/deflate.c \
	../dlib/dlib/external/zlib/gzclose.c \
	../dlib/dlib/external/zlib/gzlib.c \
	../dlib/dlib/external/zlib/gzread.c \
	../dlib/dlib/external/zlib/gzwrite.c \
	../dlib/dlib/external/zlib/infback.c \
	../dlib/dlib/external/zlib/inffast.c \
	../dlib/dlib/external/zlib/inflate.c \
	../dlib/dlib/external/zlib/inftrees.c \
	../dlib/dlib/external/zlib/trees.c \
	../dlib/dlib/external/zlib/uncompr.c \
	../dlib/dlib/external/zlib/zutil.c

DEFINES += CGFACERECOGNITION_EXPORTS DLIB_NO_GUI_SUPPORT DLIB_JPEG_SUPPORT DLIB_PNG_SUPPORT USE_AVX_INSTRUCTIONS=1