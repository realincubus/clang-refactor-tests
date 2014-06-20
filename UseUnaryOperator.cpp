
#include "CommonSingleFileTesting.hpp"
#include "UseUnaryOperator/UseUnaryOperator.h"
#include "UseUnaryOperator/UseUnaryOperatorActions.h"
#include "UseUnaryOperator/UseUnaryOperatorMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseUnaryOperatorMatcher();
	}
};

typedef Fixture<UseUnaryOperatorFixer,UseUnaryOperatorTransform,MatcherProvider> LocalFixture;
}

TEST( UseUnaryOperatorTest, PlusEqualToPrefixPlusPlus ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int a = 0;\n"
        "  a += 1;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int a = 0;\n"
	"  ++a;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( UseUnaryOperatorTest, PlusEqualToPrefixMinusMinus ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int a = 0;\n"
        "  a -= 1;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int a = 0;\n"
	"  --a;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}
