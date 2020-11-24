#ifndef IMAGEEDITOR_FRAMES_ICONTROL_H
#define IMAGEEDITOR_FRAMES_ICONTROL_H

#include <map>
#include <QtCore/QObject>

namespace ImageEditor::Modules
{
	struct IControl;
	using IControlPtr = std::shared_ptr<IControl>;
	using IControlsMap = std::multimap<std::string, IControlPtr>;
	using IControlsMapPtr = std::shared_ptr<IControlsMap>;

	struct IControl : public QObject
	{
		Q_OBJECT

	public:
		virtual ~IControl() {}

	public:
		virtual std::string Tag() const = 0;
		virtual std::string Parameters() = 0;
		virtual void Activate(std::string paramerts) = 0;
	private:
	};
}

#endif // IMAGEEDITOR_FRAMES_ICONTROL_H
#pragma once
