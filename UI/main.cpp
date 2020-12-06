#include <stdafx.h>
#include "MainWindow.h"

using namespace ImageEditor;
using namespace UI;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow main_window;

	auto image = Modules::InitEditableImageModule().create<Modules::IEditableImagePtr>();
	auto filter = Core::InitFiltersModule().create<Core::IFilterPtr>();
	auto filters_frame = Modules::InitFramesModule(image, Core::IFilterPtrArr({filter})).create<Modules::IFramePtr>();
	auto filters_widget = InitWidgetsModule(main_window, std::move(filters_frame), image).create<IWidget*>();

	main_window.show();
	filters_widget->onShow(true);

	return a.exec();
}
