
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

TEST( UseAlgorithmsTest, CountCommutativnessTest ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int ctr = 5;\n"
	"  int arr[100];\n"
        "  for( int i = 0; i < 100; i++ ) if ( 5 == arr[i] ) ctr++;\n"
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

TEST( UseAlgorithmsTest, CopyTest ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int arr[100];\n"
	"  int des[100];\n"
        "  for( int i = 0; i < 100; i++ ) des[i] = arr[i];\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int arr[100];\n"
	"  int des[100];\n"
        "  std::copy(&arr[0], &arr[100], &des[0]);\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( UseAlgorithmsTest, AccumulateTest ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int ctr = 5;\n"
	"  int arr[100];\n"
        "  for( int i = 0; i < 100; i++ ) ctr += arr[i];\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  int ctr = 5;\n"
	"  int arr[100];\n"
        "  ctr = std::accumulate(&arr[0], &arr[100], ctr);\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

#if 1
TEST( UseAlgorithmsTest, InsertTest ) {
    // input for the transformation
    std::string cpp_input = 
	"#include <vector>\n"
	"using namespace std;\n"
	"void fun() {\n"
	"  int arr[100];\n"
	"  vector<int> storage;\n"
        "  for( int i = 0; i < 100; i++ ) storage.push_back( arr[i] );\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"#include <vector>\n"
	"using namespace std;\n"
	"void fun() {\n"
	"  int arr[100];\n"
	"  vector<int> storage;\n"
        "  std::copy(&arr[0], &arr[100], std::back_inserter( &storage[0] ));\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

#endif
