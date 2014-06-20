
#include "CommonSingleFileTesting.hpp"
#include "ForLoopStartFromZero/ForLoopStartFromZero.h"
#include "ForLoopStartFromZero/ForLoopStartFromZeroActions.h"
#include "ForLoopStartFromZero/ForLoopStartFromZeroMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeForLoopStartFromZeroMatcher();
	}
};

typedef Fixture<ForLoopStartFromZeroFixer,ForLoopStartFromZeroTransform,MatcherProvider> LocalFixture;
}

TEST( ForLoopStartFromZeroTest, SimpleCase ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int arr[10];\n"
	"  for( int i = 1; i <= 10; i++ ) {\n"
        "    arr[i-1] = 5;\n"
	"  }\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int arr[10];\n"
	"  for( int i = 0; i < 10; i++ ) {\n"
        "    arr[(i + 1)-1] = 5;\n"
	"  }\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

