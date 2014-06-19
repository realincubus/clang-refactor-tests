
#include "CommonSingleFileTesting.hpp"
#include "UseConst/UseConst.h"
#include "UseConst/UseConstActions.h"
#include "UseConst/UseConstMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseConstMatcher();
	}
};

typedef Fixture<UseConstFixer,UseConstTransform,MatcherProvider> UseConstFixture;
}

TEST( UseConstTest, PositivTest ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int a = 0;\n"
	"  int b = a;\n"
	"  b = 10;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  const int a = 0;\n"
	"  int b = a;\n"
	"  b = 10;\n"
	"}\n"
    ;
    UseConstFixture Test(cpp_input,cpp_output);
}

TEST( UseConstTest, NegativTest ) {
    // input for the transformation
    std::string cpp_input = 
	"int a = 0;\n"
	"void fun() {\n"
	"  a = 10;\n"
	"}\n"
    ;
    // nothing should change
    UseConstFixture Test(cpp_input,cpp_input);
}
