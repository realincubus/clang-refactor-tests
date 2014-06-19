
#include "CommonSingleFileTesting.hpp"
#include "CollapsIfStatement/CollapseIfStatement.h"
#include "CollapsIfStatement/CollapseIfStatementActions.h"
#include "CollapsIfStatement/CollapseIfStatementMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeCollapseIfStatementMatcher();
	}
};

typedef Fixture<CollapseIfStatementFixer,CollapseIfStatementTransform,MatcherProvider> LocalFixture;
}

TEST( CollapsibleIfStatementTest, StandardCase ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  if ( true ) {\n"
        "    if ( false ) {\n"
	"    }\n"
	"  }\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  if ( true && false ) {\n"
	"    }\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( CollapsibleIfStatementTest, NegativeCase ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  if ( true ) {\n"
	"    int b;\n"
        "    if ( false ) {\n"
	"    }\n"
	"  }\n"
	"}\n"
    ;
    // since the first line after the first if might have sideffects 
    // its not possible to merge them
    LocalFixture Test(cpp_input,cpp_input);
}
