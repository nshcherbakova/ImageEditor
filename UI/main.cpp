#include <stdafx.h>
#include "MainWindow.h"
#include <UI/Widgets/WidgetsModule.h>

using namespace ImageEditor;
using namespace UI;

static const char* c_org_str = "natshch";
static const char* c_app_str = "ImageEditor";
static const char* c_font_str = ":/Fonts/buttons_font";

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName(c_org_str);
	QCoreApplication::setApplicationName(c_app_str);
	
	QFontDatabase::addApplicationFont(c_font_str);
	//UNI_ASSERT(res != -1);

	//QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	MainWindow main_window;

	auto image = Modules::InitEditableImageModule().create<Modules::IEditableImagePtr>();
	auto filters = Core::InitFiltersModule().create<Core::IFilterPtrArr>();
	auto filters_frame = Modules::InitFramesModule(image, std::move(filters)).create<Modules::IFramePtr>();
	auto image_provider = UI::InitImageProviderModule().create<UI::IImageProviderPtr>();
	auto filters_widget = UI::InitWidgetsModule(main_window, std::move(filters_frame), std::move(image), std::move(image_provider)).create<IWidget*>();

	main_window.show();
	filters_widget->onShow(true);

	return a.exec();
}
