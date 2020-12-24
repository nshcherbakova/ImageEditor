HEADERS += ./UI/QtConverts.h \
    ./UI/types.h \
    ./UI/UIString.h \
    ./UI/MainWindow.h \
    ./UI/Widgets/IWidget.h \
    ./UI/Widgets/WidgetsModule.h \
    ./UI/Widgets/MenuDialog.h \
    ./UI/Widgets/FiltersWidget.h \
    ./Core/types.h \
    ./Core/Gears/Asserts.h \
    ./Core/Gears/Injector.h \
    ./Core/Gears/StdAfx/stdafx.h \
    ./Core/Filters/FilterBase.h \
    ./Core/Filters/SepiaFilter.h \
    ./Core/Filters/SmoothFilter.h \
    ./Core/Filters/GrayFilter.h \
    ./Core/Filters/TessFilter.h \
    ./Core/Filters/WatercolorFilter.h \
    ./Core/Filters/IFilter.h \
    ./Core/Filters/FiltersModule.h \
    ./Core/Image/Image.h \
    ./Core/Image/IImage.h \
    ./Core/Image/ImageModule.h \
    ./Modules/types.h \
    ./Modules/Frames/FiltersFrame.h \
    ./Modules/Frames/IControl.h \
    ./Modules/Frames/IFrame.h \
    ./Modules/Frames/FramesModule.h \
    ./Modules/Frames/Tags.h \
    ./Modules/EditableImage/EditableImage.h \
    ./Modules/EditableImage/IEditableImage.h \
    ./Modules/EditableImage/EditableImageModule.h
SOURCES += ./UI/QtConverts.cpp \
    ./UI/MainWindow..cpp \
    ./UI/main.cpp \
    ./UI/Widgets/FiltersWidget.cpp \
    ./UI/Widgets/MenuDialog.cpp \
    ./UI/Widgets/WidgetsModule.cpp \
    ./Core/Gears/StdAfx/stdafx.cpp \
    ./Core/Filters/FilterBase.cpp \
    ./Core/Filters/FiltersModule.cpp \
    ./Core/Filters/SepiaFilter.cpp \
    ./Core/Filters/SmoothFilter.cpp \
    ./Core/Filters/GrayFilter.cpp \
    ./Core/Filters/TessFilter.cpp \
    ./Core/Filters/WatercolorFilter.cpp \
    ./Core/Image/ImageModule.cpp \
    ./Core/Image/Image.cpp \
    ./Modules/Frames/FramesModule.cpp \
    ./Modules/Frames/FiltersFrame.cpp \
    ./Modules/EditableImage/EditableImageModule.cpp \
    ./Modules/EditableImage/EditableImage.cpp
FORMS += ./UI/ImageEditor.ui
RESOURCES += UI/ImageEditor.qrc
