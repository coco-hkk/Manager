QT += core5compat network

# MinGW 64 可以使用通配符 *.cpp *.h 配置
# MSVC 不能使用通配符，报错: “无法解析的外部符号……”
SOURCES += $$PWD/imageviewer.cpp \
           $$PWD/networkImageModel.cpp \
           $$PWD/directoryTraverse.cpp

RESOURCES += $$PWD/imageviewer.qrc

HEADERS += \
           $$PWD/imageViewer.h \
           $$PWD/networkImageModel.h \
           $$PWD/networkImageModel_p.h \
           $$PWD/directoryTraverse.h

TRANSLATIONS += $$PWD/imageviewer_zh_CN.ts
