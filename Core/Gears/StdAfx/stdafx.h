#include <cstddef>
#include <limits>
#include <optional>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QImage>
#include <QImageReader>
#include <QPushButton>
#include <QSettings>
#include <QtWidgets/QApplication>
#include <QtWidgets>

#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkAccessManager>
#include <QUrl>

#include <Core/Filters/FiltersModule.h>
#include <Core/Filters/IFilter.h>
#include <Core/Gears/Asserts.h>
#include <Core/Gears/Injector.h>
#include <Core/Image/IImage.h>
#include <Core/Image/ImageModule.h>
#include <Core/types.h>

#include <Modules/EditableImage/EditableImageModule.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/Frames/FramesModule.h>
#include <Modules/Frames/IControl.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/Tags.h>

#include <UI/QtConverts.h>
#include <UI/UIString.h>
#include <UI/Widgets/FiltersWidget.h>
#include <UI/Widgets/IWidget.h>
#include <UI/Widgets/WidgetsModule.h>
