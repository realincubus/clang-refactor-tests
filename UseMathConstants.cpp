
#include "CommonSingleFileTesting.hpp"
#include "UseMathConstants/UseMathConstants.h"
#include "UseMathConstants/UseMathConstantsActions.h"
#include "UseMathConstants/UseMathConstantsMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseMathConstantsMatcher();
	}
};

typedef Fixture<UseMathConstantsFixer,UseMathConstantsTransform,MatcherProvider> UseMathConstantsFixture;
}

TEST( UseMathConstantsTest, PI ) {
    // input for the transformation
    std::string cpp_input = 
	"double pi = 3.141592654;\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"double pi = M_PI;\n"
    ;
    UseMathConstantsFixture Test(cpp_input,cpp_output);
}

TEST( UseMathConstantsTest, SQRT2 ) {
    // input for the transformation
    std::string cpp_input = 
	"double pi = 1.41421356237;\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"double pi = M_SQRT2;\n"
    ;
    UseMathConstantsFixture Test(cpp_input,cpp_output);
}
