// Copyright © 2021 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include <Mib/Container/Map>
#include <Mib/Container/LinkedList>
#include <Mib/String/MultiReplace>

namespace
{
	using namespace NMib;
	using namespace NMib::NStr;

	class CMultiReplace_Tests : public NMib::NTest::CTest
	{
	public:

		template <bool tf_bCaseSensitive>
		void fp_DoTests()
		{
			TCMultiReplace<tf_bCaseSensitive> MultiReplace
				(
					{
						{"C:\\\\Program Files\\\\Go\\\\bin\\\\", ""}
						, {"C:/Program Files/Go/bin/", ""}
					}
				)
			;

			CStr TestString = R"--(
				Compile
				{
					Custom_CommandLine `"C:\\Program Files\\Go\\bin\\go.exe" run util/all_tests.go -build-dir @("C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug"->MakeAbsolute()->EscapeHost()) && cd ssl/test/runner && "C:/Program Files/Go/bin/go.exe" test -shim-path @("C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug/ssl/test/bssl_shim.exe"->MakeAbsolute()->EscapeHost())`
					AllowNonExisting true
					Disabled false
					Custom_WorkingDirectory "C:/Dev/Hansoft/Qt6/External/boringssl"->MakeAbsolute()
					Custom_Outputs ["C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug/CMakeFiles/run_tests"->MakeAbsolute()]
					Custom_Inputs ["C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug/ssl/test/bssl_shim.exe"->MakeAbsolute()]
				}
			)--";

			CStr ExpectedString = R"--(
				Compile
				{
					Custom_CommandLine `"go.exe" run util/all_tests.go -build-dir @("C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug"->MakeAbsolute()->EscapeHost()) && cd ssl/test/runner && "go.exe" test -shim-path @("C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug/ssl/test/bssl_shim.exe"->MakeAbsolute()->EscapeHost())`
					AllowNonExisting true
					Disabled false
					Custom_WorkingDirectory "C:/Dev/Hansoft/Qt6/External/boringssl"->MakeAbsolute()
					Custom_Outputs ["C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug/CMakeFiles/run_tests"->MakeAbsolute()]
					Custom_Inputs ["C:/CompiledFiles/Qt6-b9ce2311/Hansoft/Generated/External_boringssl/Windows/x64/Debug/ssl/test/bssl_shim.exe"->MakeAbsolute()]
				}
			)--";
			DMibExpect(MultiReplace.f_Replace(TestString), ==, ExpectedString);
		}

		void f_DoTests()
		{
			DMibTestSuite("General")
			{
				{
					DMibTestPath("CaseSensitive");
					fp_DoTests<true>();
				}
				{
					DMibTestPath("CaseInsensitive");
					fp_DoTests<false>();
				}
			};
			DMibTestCategory("Bugs")
			{
				DMibTestSuite("2024-01-07")
				{
					using CStringMap = TCMultiReplace<true>::CStringMap;
					CStringMap StringMap =
						{
							{"/opt/CompiledFiles/QtUpdate-cb58ba2f/Hansoft/Generated/External_qt/macOS/arm64/Debug/qtbase/libexec/", "#(MalterlibQt_ToolsPath)/"}
							, {"/opt/CompiledFiles/QtUpdate-cb58ba2f/Hansoft/Generated/External_qt/macOS/arm64/Debug/qtbase/bin/", "#(MalterlibQt_ToolsPath)/"}
							, {"/opt/CompiledFiles/QtUpdate-cb58ba2f/Hansoft/Generated/External_qt/macOS/arm64/Debug/", "#(CMakeIntermediateDirectory)/"}
						}
					;

					TCMultiReplace<true> MultiReplace(fg_Move(StringMap));

					{
						DMibTestPath("ShortCase");
						CStr String = "/opt/CompiledFiles/QtUpdate-cb58ba2f/Hansoft/Generated/External_qt/macOS/arm64/Debug/qtdeclarative/src/quick/.qsb/scenegraph/shaders_ng/24bittextmask.frag.qsb</file>";
						CStr ReplacedString = MultiReplace.f_Replace(String);
						CStr ExpectedString = "#(CMakeIntermediateDirectory)/qtdeclarative/src/quick/.qsb/scenegraph/shaders_ng/24bittextmask.frag.qsb</file>";

						DMibExpect(ReplacedString, ==, ExpectedString);
					}
					{
						DMibTestPath("LongCase");
						CStr String = "/opt/CompiledFiles/QtUpdate-cb58ba2f/Hansoft/Generated/External_qt/macOS/arm64/Debug/qtbase/bin/test.binary</file>";
						CStr ReplacedString = MultiReplace.f_Replace(String);
						CStr ExpectedString = "#(MalterlibQt_ToolsPath)/test.binary</file>";

						DMibExpect(ReplacedString, ==, ExpectedString);
					}
				};
			};
		}
	};

	DMibTestRegister(CMultiReplace_Tests, Malterlib::String::Algorithm);
}
