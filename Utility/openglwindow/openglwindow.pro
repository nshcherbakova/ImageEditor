include(openglwindow.pri)

SOURCES += \
    main.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/openglwindow
INSTALLS += target

DISTFILES += \
    data/drops_filter.fs \
    data/filter.fs \
    data/filter.vs \
    data/test.jpeg

RESOURCES += \
    resource.qrc
