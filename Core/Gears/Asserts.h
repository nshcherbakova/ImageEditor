#pragma once
#ifndef IMAGEEDITOR_CORE_GEARS_ASSERTS_H
#define IMAGEEDITOR_CORE_GEARS_ASSERTS_H
#include <iostream>

namespace ImageEditor::Core::Gears
{
	inline void return_if_check(bool statement, const char* message = nullptr)
	{
		std::cout << "Error";
	}
}
namespace core = ImageEditor::Core::Gears;

#endif //IMAGEEDITOR_CORE_GEARS_ASSERTS_H

