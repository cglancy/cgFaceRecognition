QT += core

TARGET = cgFaceRecognition
CONFIG += dll
TEMPLATE = lib
VERSION	= 0.1.1

INCLUDEPATH += ../. \
	../dlib/external/libpng \
	../dlib/external/libjpeg \
	../dlib/external/zlib

HEADERS += cgfacerecognition.h \
	facedetection.h

SOURCES += facedetection.cpp \
	../dlib/all/source.cpp \
	../dlib/external/libjpeg/jcapimin.cpp \
	../dlib/external/libjpeg/jcapistd.cpp \
	../dlib/external/libjpeg/jccoefct.cpp \
	../dlib/external/libjpeg/jccolor.cpp \
	../dlib/external/libjpeg/jcdctmgr.cpp \
	../dlib/external/libjpeg/jchuff.cpp \
	../dlib/external/libjpeg/jcinit.cpp \
	../dlib/external/libjpeg/jcmainct.cpp \
	../dlib/external/libjpeg/jcmarker.cpp \
	../dlib/external/libjpeg/jcmaster.cpp \
	../dlib/external/libjpeg/jcomapi.cpp \
	../dlib/external/libjpeg/jcparam.cpp \
	../dlib/external/libjpeg/jcphuff.cpp \
	../dlib/external/libjpeg/jcprepct.cpp \
	../dlib/external/libjpeg/jcsample.cpp \
	../dlib/external/libjpeg/jdapimin.cpp \
	../dlib/external/libjpeg/jdapistd.cpp \
	../dlib/external/libjpeg/jdatadst.cpp \
	../dlib/external/libjpeg/jdatasrc.cpp \
	../dlib/external/libjpeg/jdcoefct.cpp \
	../dlib/external/libjpeg/jdcolor.cpp \
	../dlib/external/libjpeg/jddctmgr.cpp \
	../dlib/external/libjpeg/jdhuff.cpp \
	../dlib/external/libjpeg/jdinput.cpp \
	../dlib/external/libjpeg/jdmainct.cpp \
	../dlib/external/libjpeg/jdmarker.cpp \
	../dlib/external/libjpeg/jdmaster.cpp \
	../dlib/external/libjpeg/jdmerge.cpp \
	../dlib/external/libjpeg/jdphuff.cpp \
	../dlib/external/libjpeg/jdpostct.cpp \
	../dlib/external/libjpeg/jdsample.cpp \
	../dlib/external/libjpeg/jerror.cpp \
	../dlib/external/libjpeg/jfdctflt.cpp \
	../dlib/external/libjpeg/jfdctfst.cpp \
	../dlib/external/libjpeg/jfdctint.cpp \
	../dlib/external/libjpeg/jidctflt.cpp \
	../dlib/external/libjpeg/jidctfst.cpp \
	../dlib/external/libjpeg/jidctint.cpp \
	../dlib/external/libjpeg/jidctred.cpp \
	../dlib/external/libjpeg/jmemmgr.cpp \
	../dlib/external/libjpeg/jmemnobs.cpp \
	../dlib/external/libjpeg/jquant1.cpp \
	../dlib/external/libjpeg/jquant2.cpp \
	../dlib/external/libjpeg/jutils.cpp \
	../dlib/external/libpng/png.c \
	../dlib/external/libpng/pngerror.c \
	../dlib/external/libpng/pngget.c \
	../dlib/external/libpng/pngmem.c \
	../dlib/external/libpng/pngpread.c \
	../dlib/external/libpng/pngread.c \
	../dlib/external/libpng/pngrio.c \
	../dlib/external/libpng/pngrtran.c \
	../dlib/external/libpng/pngrutil.c \
	../dlib/external/libpng/pngset.c \
	../dlib/external/libpng/pngtrans.c \
	../dlib/external/libpng/pngwio.c \
	../dlib/external/libpng/pngwrite.c \
	../dlib/external/libpng/pngwtran.c \
	../dlib/external/libpng/pngwutil.c \
	../dlib/external/zlib/adler32.c \
	../dlib/external/zlib/compress.c \
	../dlib/external/zlib/crc32.c \
	../dlib/external/zlib/deflate.c \
	../dlib/external/zlib/gzclose.c \
	../dlib/external/zlib/gzlib.c \
	../dlib/external/zlib/gzread.c \
	../dlib/external/zlib/gzwrite.c \
	../dlib/external/zlib/infback.c \
	../dlib/external/zlib/inffast.c \
	../dlib/external/zlib/inflate.c \
	../dlib/external/zlib/inftrees.c \
	../dlib/external/zlib/trees.c \
	../dlib/external/zlib/uncompr.c \
	../dlib/external/zlib/zutil.c

DEFINES += CGFACERECOGNITION_EXPORTS DLIB_NO_GUI_SUPPORT DLIB_JPEG_SUPPORT DLIB_PNG_SUPPORT USE_AVX_INSTRUCTIONS=ON