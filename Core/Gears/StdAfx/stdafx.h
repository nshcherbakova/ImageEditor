#include <cstddef>
#include <limits>
#include <optional>

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QImageReader>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QtWidgets>
#include <QtWidgets/QApplication>

#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>

#include <Core/types.h>
#include <Core/Image/IImage.h>
#include <Core/Image/ImageModule.h>
#include <Core/Gears/Injector.h>
#include <Core/Gears/Asserts.h>
#include <Core/Filters/IFilter.h>
#include <Core/Filters/FiltersModule.h>

#include <Modules/Frames/IControl.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/FramesModule.h>
#include <Modules/Frames/Tags.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/EditableImage/EditableImageModule.h>

#include <UI/UIString.h>
#include <UI/QtConverts.h>
#include <UI/Widgets/IWidget.h>
#include <UI/Widgets/WidgetsModule.h>
#include <UI/Widgets/FiltersWidget.h>
#include <UI/ImageProvider/IImageProvider.h>
#include <UI/ImageProvider/ImageProviderModule.h>

