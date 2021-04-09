#include <cstddef>
#include <optional>

//#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSettings>
#include <QtWidgets>
#include <QtWidgets/QApplication>

#include <Core/Image/ImageModule.h>
#include <Core/Filters/FiltersModule.h>
#include <Core/Gears/Injector.h>
#include <Core/Gears/Asserts.h>

#include <Modules/Frames/FramesModule.h>
#include <Modules/EditableImage/EditableImageModule.h>
#include <Modules/Frames/Tags.h>

#include <UI/Widgets/WidgetsModule.h>
#include <UI/ImageProvider/ImageProviderModule.h>
