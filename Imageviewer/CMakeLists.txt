set(SOURCES
        Imageviewer/imageviewer.cpp
        Imageviewer/networkImageModel.cpp
        Imageviewer/directoryTraverse.cpp

        Imageviewer/imageViewer.h
        Imageviewer/networkImageModel.h
        Imageviewer/networkImageModel_p.h
        Imageviewer/directoryTraverse.h
)

qt_add_big_resources(SOURCES
        Imageviewer/imageviewer.qrc
)

#qt_add_lupdate(hkk TS_FILES Manager.ts)
#qt_add_lrelease(hkk
#        TS_FILES Manager.ts
#        QM_FILES_OUTPUT_VARIABLE qm_files)
#qt_add_resources(hkk "translations"
#        PREFIX "Imageview"
#        BASE "${CMAKE_CURRENT_BINARY_DIR}"
#        FILES "${qm_files}")

set(LINK_LIBRARIES
        Qt6::Network
        Qt6::Core5Compat
)

