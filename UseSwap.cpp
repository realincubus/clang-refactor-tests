
#include "CommonSingleFileTesting.hpp"
#include "UseSwap/UseSwap.h"
#include "UseSwap/UseSwapActions.h"
#include "UseSwap/UseSwapMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseSwapMatcher();
	}
};

typedef Fixture<UseSwapFixer,UseSwapTransform,MatcherProvider> LocalFixture;
}

TEST( UseSwapTest, SwapTest ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int a,b,t;\n"
	"  t = a;\n"
	"  a = b;\n"
	"  b = t;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  std::swap(a, b);\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}
