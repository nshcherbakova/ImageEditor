#include <cstddef>
#include <limits>
#include <optional>

#ifdef Q_OS_ANDROID
#include "spdlog/sinks/android_sink.h"
#else
#include <spdlog/sinks/stdout_sinks.h>
#endif
#include <spdlog/sinks/rotating_file_sink.h>

#include <spdlog/spdlog.h>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QImage>
#include <QImageReader>
#include <QPushButton>
#include <QRandomGenerator>
#include <QSettings>
#include <QSplashScreen>
#include <QStandardPaths>
#include <QVariant>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets>

#ifdef Q_OS_ANDROID
#include <QJniObject>
#include <QtCore/private/qandroidextras_p.h>
#include <jni.h>
#endif

#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include <Core/Filters/FiltersModule.h>
#include <Core/Filters/IFilter.h>
#include <Core/Gears/Asserts.h>
#include <Core/Gears/Injector.h>
#include <Core/Image/IImage.h>
#include <Core/Image/ImageModule.h>
#include <Core/shareutils/ShareUtilsCpp.h>
#include <Core/types.h>

#include <Modules/EditableImage/EditableImageModule.h>
#include <Modules/EditableImage/IEditableImage.h>
#include <Modules/Frames/FramesModule.h>
#include <Modules/Frames/IControl.h>
#include <Modules/Frames/IFrame.h>
#include <Modules/Frames/Tags.h>
#include <Modules/Network/INetwork.h>
#include <Modules/Network/NetworkModule.h>

#include <UI/QtConverts.h>
#include <UI/UIString.h>
#include <UI/Widgets/FiltersWidget.h>
#include <UI/Widgets/IWidget.h>
#include <UI/Widgets/SplashScreen.h>
#include <UI/Widgets/WidgetsModule.h>

#include <Core/Filters/GrayFilter.h>
#include <Core/Filters/OpenGL/OpenGLBlurFilter.h>
#include <Core/Filters/OpenGL/OpenGLDitheringFilter.h>
#include <Core/Filters/OpenGL/OpenGLDropsFilter.h>
#include <Core/Filters/OpenGL/OpenGLGrayFilter.h>
#include <Core/Filters/OpenGL/OpenGLSepiaFilter.h>
#include <Core/Filters/OpenGL/OpenGLTessFilter.h>
#include <Core/Filters/OpenGL/OpenGLWatercolorFilter.h>
#include <Core/Filters/SepiaFilter.h>
#include <Core/Filters/SmoothFilter.h>
#include <Core/Filters/TessFilter.h>
#include <Core/Filters/WatercolorFilter.h>
