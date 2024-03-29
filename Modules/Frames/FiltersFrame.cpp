#include <stdafx.h>
#include "FiltersFrame.h"


namespace
{
	using namespace ImageEditor;
	using namespace ImageEditor::Modules;

	class Control final: public IControl
	{
	public:
		Control(Core::IFilterPtr filter, IEditableImagePtr image)
			: filter_(filter), image_(image)
		{
			UNI_ENSURE_RETURN(filter_);
			UNI_ENSURE_RETURN(image_);
		}

	public:
		virtual const  std::string Parameters() const override final
		{
			UNI_ENSURE_RETURN(filter_, std::string());
			return filter_->Description();
		}

		virtual void Activate(std::string paramerts) override final
		{
			UNI_ENSURE_RETURN(image_);
			UNI_ENSURE_RETURN(filter_);

            spdlog::info("Control activated", filter_->Description() );

			image_->UpdateImage(filter_->Apply(image_->OriginalImage(), paramerts));
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
		UNI_ENSURE_RETURN(parameters.image);

		controls_ = std::make_shared<IControlsMap>();
		for (auto& filter: parameters.filters)
		{
			UNI_ENSURE_RETURN(filter);
			IControlPtr control = std::make_shared<Control>(filter, parameters.image);
			controls_->emplace(std::make_pair(Modules::FILTER_BUTTON_TAG, std::move(control)));
		}
	}

	const IControlsMapPtr FiltersFrame::Controls() const
	{
		return controls_;
	}

}
