#include <stdafx.h>
#include "MainWindow.h"

using namespace ImageEditor;
using namespace UI;

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow main_window;

	auto image_injector = Modules::InitEditableImageModule();
	auto image = image_injector.create<Modules::IEditableImagePtr>();
	
	auto filters_injector = Core::InitFiltersModule();
	auto filter = filters_injector.create<Core::IFilterPtr>();
	
	auto filters_container = filters_injector.create<Core::IFiltersContainerPtr>();
	filters_container->AddFilter(std::move(filter));
	
	auto frame_injector = Modules::InitFramesModule(std::move(image), std::move(filters_container));
	auto filters_frame = frame_injector.create<Modules::IFramePtr>();

	auto widget_injector = InitWidgetsModule(main_window, std::move(filters_frame));
	auto filters_widget = widget_injector.create<IWidget*>();

	main_window.show();
	filters_widget->onShow(true);

	return a.exec();
}
