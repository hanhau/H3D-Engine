#include "stdafx.h"
#include "CppUnitTest.h"

#pragma comment(lib,"../../Release/H3D.lib")

#include "../../H3D/Vector.hpp"
#include "../../H3D/Window.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:		
		TEST_METHOD(WindowCreation)
		{
			h3d::Window(h3d::Vec2<unsigned int>(200, 200), L"Title", h3d::Style::Default);
			Assert::IsTrue(true);
		}

		TEST_METHOD(BasicTest)
		{
			h3d::Vec2<int> s(2, 2);
			Assert::IsTrue(true);
		}
	};
}