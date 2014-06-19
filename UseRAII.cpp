
#include "CommonSingleFileTesting.hpp"
#include "UseRAII/UseRAII.h"
#include "UseRAII/UseRAIIActions.h"
#include "UseRAII/UseRAIIMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseRAIIMatcher();
	}
};

typedef Fixture<UseRAIIFixer,UseRAIITransform,MatcherProvider> LocalFixture;
}

TEST( UseRAIITest, InitalizeDouble ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  double val;\n"
        "  val = 123.45;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  double val = 123.45;\n"
	"  ;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( UseRAIITest, InitializeStatic ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  static double val;\n"
        "  val = 123.45;\n"
	"}\n"
    ;
    // must not work since it changes semantic
    LocalFixture Test(cpp_input,cpp_input);
}
