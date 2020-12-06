#include <stdafx.h>
#include "FiltersFrame.h"


namespace
{
	using namespace ImageEditor;
	using namespace ImageEditor::Modules;

	class Control final: public IControl
	{
	public:
		Control::Control(Core::IFilterPtr filter, IEditableImagePtr image)
			: filter_(filter), image_(image)
		{
			core::return_if_check(!filter_);
			core::return_if_check(!image_);
		}

	public:
		/*virtual const std::string Tag() const override final
		{
			return Modules::Frames::FILTER_BUTTON_TAG;
		}*/

		virtual const  std::string Parameters() const override final
		{
			core::return_if_check(!filter_);
			return filter_->Description();
		}

		virtual void Activate(std::string paramerts) override final
		{
			core::return_if_check(!image_);
			core::return_if_check(!filter_);
			image_->UpdateImage(filter_->Apply(image_->Image(), paramerts));
		}

	private:
		const Core::IFilterPtr filter_;
		IEditableImagePtr image_;

	};
}

namespace ImageEditor::Modules
{
	FiltersFrame::FiltersFrame(Parameters parameters)
	{
		core::return_if_check(!parameters.image);

		controls_ = std::make_shared<IControlsMap>();
		for (auto& filter: parameters.filters)
		{
			core::return_if_check(!filter);
			IControlPtr control = std::make_shared<Control>(filter, parameters.image);
			controls_->emplace(std::make_pair(Modules::FILTER_BUTTON_TAG, std::move(control)));
		}
	}

	const IControlsMapPtr FiltersFrame::Controls() const
	{
		return controls_;
	}

}