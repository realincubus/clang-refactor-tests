
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

// TODO right now this does not work because clang does not detect
//      arr to be a incomplete array 
TEST( UseVectorTest, IncompleteToVector ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  double arr[] = { 0,1,2,3,4,5,6 };\n"
        "  arr[2] = 123.45;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  std::vector<double> arr = { 0,1,2,3,4,5,6 };\n"
	"  arr[2] = 123.45;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}
