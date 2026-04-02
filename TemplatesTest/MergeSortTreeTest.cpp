#include "pch.h"
#include "CppUnitTest.h"
#include "Templates\MergeSortTree.h"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TemplatesTest
{
	TEST_CLASS(MergeSortTreeTest)
	{
	public:
		
		TEST_METHOD(FindNumberOfGreaterElements_ReturnsCorrectCount)
		{
			std::vector<int> A = { 1, 5, 2, 4, 3 };
			
			MergeSortTree<int> T(A);
			
			Assert::AreEqual(3, T.FindNumberOfGreaterElements(2, 0, 4));
			Assert::AreEqual(0, T.FindNumberOfGreaterElements(5, 0, 4));
			Assert::AreEqual(5, T.FindNumberOfGreaterElements(0, 0, 4));
		}
	};
}
