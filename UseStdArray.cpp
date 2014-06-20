
#include "CommonSingleFileTesting.hpp"
#include "UseStdArray/UseStdArray.h"
#include "UseStdArray/UseStdArrayActions.h"
#include "UseStdArray/UseStdArrayMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseStdArrayMatcher();
	}
};

typedef Fixture<UseStdArrayFixer,UseStdArrayTransform,MatcherProvider> LocalFixture;
}

TEST( UseStdArrayTest, ConstantCArrayTransformation ) {
    // input for the transformation
    std::string cpp_input = 
	"int a[100];\n"
	"void fun() {\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"std::array<int,100> a;\n"
	"void fun() {\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( UseStdArrayTest, ConstantCArrayTransformationWithInitList ) {
    // input for the transformation
    std::string cpp_input = 
	"int a[5] = {1,2,3,4,5};\n"
	"void fun() {\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"std::array<int,5> a = {1,2,3,4,5};\n"
	"void fun() {\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}

TEST( UseStdArrayTest, VLACArrayTransformation ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  int vla_dim = 100;\n"
	"  int a[vla_dim];\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    // dont change something vla is not translatable to std::array
    LocalFixture Test(cpp_input,cpp_input);
}

TEST( UseStdArrayTest, ConstExprArray ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  constexpr int dim = 100;\n"
	"  int a[dim];\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    // TODO rightnow i can get the size of the constant size array just as a number 
    //      constexpr information is lost
    std::string cpp_output = 
	"void fun() {\n"
	"  constexpr int dim = 100;\n"
	"  std::array<int,100> a;\n"
	"  a[50] = 10;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input, cpp_output);
}

// TODO right now this does not work because clang does not detect
//      arr to be a incomplete array 
TEST( UseStdArrayTest, IncompleteToArray ) {
    // input for the transformation
    std::string cpp_input = 
	"void fun() {\n"
	"  double arr[] = { 0,1,2,3,4,5,6 };\n"
        "  arr[2] = 123.45;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"void fun() {\n"
	"  std::array<double,7> arr = { 0,1,2,3,4,5,6 };\n"
	"  arr[2] = 123.45;\n"
	"}\n"
    ;
    LocalFixture Test(cpp_input,cpp_output);
}
