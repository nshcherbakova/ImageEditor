#pragma once
#ifndef IMAGEEDITOR_UI_UISTRING_H
#define IMAGEEDITOR_UI_UISTRING_H
#include <QString>

namespace ImageEditor::UI
{
	QString UIString(const std::string& text)
	{
		return QString::fromStdString(text);
	}
};
#endif //