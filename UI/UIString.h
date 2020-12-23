#pragma once
#ifndef IMAGEEDITOR_UI_UISTRING_H
#define IMAGEEDITOR_UI_UISTRING_H
#include <QString>

namespace ImageEditor::UI
{
	inline QString UIString(const std::string& text)
	{
		return QString::fromStdString(text);
	}
};
#endif // IMAGEEDITOR_UI_UISTRING_H
