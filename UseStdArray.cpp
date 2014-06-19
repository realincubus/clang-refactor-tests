
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

typedef Fixture<UseStdArrayFixer,UseStdArrayTransform,MatcherProvider> UseStdArrayFixture;
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
    UseStdArrayFixture Test(cpp_input,cpp_output);
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
    UseStdArrayFixture Test(cpp_input,cpp_input);
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
    UseStdArrayFixture Test(cpp_input, cpp_output);
}
