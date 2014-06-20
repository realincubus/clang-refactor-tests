
#include "CommonSingleFileTesting.hpp"
#include "UseVector/UseVector.h"
#include "UseVector/UseVectorActions.h"
#include "UseVector/UseVectorMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseVectorMatcher();
	}
};

typedef Fixture<UseVectorFixer,UseVectorTransform,MatcherProvider> LocalFixture;
}

TEST( UseVectorTest, VLAToVector ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int vla_dim = 10;\n"
	"  double arr[vla_dim];\n"
        "  arr[10] = 123.45;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int vla_dim = 10;\n"
	"  std::vector<double> arr(vla_dim);\n"
	"  arr[10] = 123.45;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}


TEST( UseVectorTest, ConstExprToVectorNegative ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  constexpr int vla_dim = 10;\n"
	"  double arr[vla_dim];\n"
        "  arr[10] = 123.45;\n"
	"}\n"
    ;
    // constexpr sized arrays should be transformed to array
    LocalFixture Test(cpp_input,cpp_input);
}
