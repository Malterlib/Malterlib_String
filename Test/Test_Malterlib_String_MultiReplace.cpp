// Copyright © 2021 Favro Holding AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Core/Core>

#include <Mib/Container/Map>
#include <Mib/Container/LinkedList>
#include <Mib/String/MultiReplace>

namespace
{
	using namespace NMib::NStr;
	class CMultiReplace_Tests : public NMib::NTest::CTest
	{
	public:

		template <bool tf_bCaseSensitive>
		void fp_DoTests()
		{
			TCMultiReplace<tf_bCaseSensitive> MultiReplace;

			MultiReplace.m_Replace = 
				{
					{"C:\\\\Program Files\\\\Go\\\\bin\\\\", ""}
					, {"C:/Program Files/Go/bin/", ""}
				}
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
		}
	};

	DMibTestRegister(CMultiReplace_Tests, Malterlib::String::Algorithm);
}
