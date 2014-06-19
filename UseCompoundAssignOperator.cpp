
#include "CommonSingleFileTesting.hpp"
#include "UseCompoundAssignOperator/UseCompoundAssignOperator.h"
#include "UseCompoundAssignOperator/UseCompoundAssignOperatorActions.h"
#include "UseCompoundAssignOperator/UseCompoundAssignOperatorMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseCompoundAssignOperatorMatcher();
	}
};

typedef Fixture<UseCompoundAssignOperatorFixer,UseCompoundAssignOperatorTransform,MatcherProvider> UseCompoundAssignOperatorFixture;
}

TEST( UseCompoundOperatorTest, UseCompoundAssignOperatorTestCase ) {
    std::string cpp_input = 
	"int a;\n"
	"void fun() {\n"
	"  a = a + 1;\n"
	"}\n"
    ;
    std::string cpp_output = 
	"int a;\n"
	"void fun() {\n"
	"  a += 1;\n"
	"}\n"
    ;
    UseCompoundAssignOperatorFixture Test(cpp_input,cpp_output);
}
