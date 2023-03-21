#include <stdafx.h>
#include "MainWindow.h"
#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif

using namespace ImageEditor;
using namespace UI;

static const char* c_org_str = "natshch";
static const char* c_app_str = "ImageEditor";
static const char* c_font_str = ":/Fonts/buttons_font";

int main(int argc, char* argv[])
{
    QSurfaceFormat fmt;
    fmt.setSamples(16);
    QSurfaceFormat::setDefaultFormat(fmt);
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName(c_org_str);
	QCoreApplication::setApplicationName(c_app_str);
	
	QFontDatabase::addApplicationFont(c_font_str);

#ifdef Q_OS_ANDROID
	QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
	if (activity.isValid())
	{
		int orientation  = QAndroidJniObject::getStaticField<int>("android.content.pm.ActivityInfo", "SCREEN_ORIENTATION_PORTRAIT");
		activity.callMethod<void>
			("setRequestedOrientation" // method name
				, "(I)V" // signature
				, orientation);
	}
#endif
	MainWindow main_window;

	auto image = Modules::InitEditableImageModule().create<Modules::IEditableImagePtr>();
	auto filters = Core::InitFiltersModule().create<Core::IFilterPtrArr>();
	auto filters_frame = Modules::InitFramesModule(image, std::move(filters)).create<Modules::IFramePtr>();
	auto filters_widget = UI::InitWidgetsModule(main_window, std::move(filters_frame), std::move(image)).create<IWidget*>();

	main_window.show();
	filters_widget->onShow(true);

	return a.exec();
}
