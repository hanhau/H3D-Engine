#pragma once
#ifdef DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <string>
#include <sstream>

namespace gui {
	struct base_class_gui
	{
	public:
		virtual void update();
	};
	namespace Element {
		class Button
		{

		};
		class Checkbox
		{

		};
		class Slider
		{

		};
	}
	class Font
	{

	};
	class Text
	{

	};
	class Panel
	{

	};
}