#include "CommonSingleFileTesting.hpp"
#include "FuseToSimdVector/FuseToSimdVector.h"
#include "FuseToSimdVector/FuseToSimdVectorActions.h"
#include "FuseToSimdVector/FuseToSimdVectorMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeFuseToSimdVectorMatcher();
	}
};

typedef Fixture<FuseToSimdVectorFixer,FuseToSimdVectorTransform,MatcherProvider> LocalFixture;
}

TEST( FuseToSimdVectorTest, GCC_Simd_vector ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  float x,y,z;\n"
        "  x = 10;\n"
	"  y = 10;\n"
	"  z = 10;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  float __attribute__((vector_size(sizeof(float)*4))) default_name;\n"
        "  default_name[0] = 10;\n"
        "  default_name[1] = 10;\n"
        "  default_name[2] = 10;\n"
	"}\n"
    ;
    std::list<std::string> args;
    args.push_back("-new_name vec4");
    LocalFixture Test(cpp_input,cpp_output);
}


