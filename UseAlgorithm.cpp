
#include "CommonSingleFileTesting.hpp"
#include "UseAlgorithms/UseAlgorithms.h"
#include "UseAlgorithms/UseAlgorithmsActions.h"
#include "UseAlgorithms/UseAlgorithmsMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseAlgorithmsMatcher();
	}
};

typedef Fixture<UseAlgorithmsFixer,UseAlgorithmsTransform,MatcherProvider> LocalFixture;
}

TEST( UseAlgorithmsTest, Iota ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int arr[100];\n"
        "  for( int i = 0; i < 100; i++ ) arr[i] = i;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int arr[100];\n"
        "  std::iota(&arr[0], &arr[100], 0);\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}


TEST( UseAlgorithmsTest, Fill ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int arr[100];\n"
        "  for( int i = 0; i < 100; i++ ) arr[i] = 0;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int arr[100];\n"
        "  std::fill(&arr[0], &arr[100], 0);\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( UseAlgorithmsTest, Count ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int ctr = 5;\n"
	"  int arr[100];\n"
        "  for( int i = 0; i < 100; i++ ) if ( arr[i] == 5 ) ctr++;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int ctr = 5;\n"
	"  int arr[100];\n"
        "  ctr += std::count(&arr[0], &arr[100], 5);\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}
