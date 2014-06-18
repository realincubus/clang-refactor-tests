

#include "gtest/gtest.h"
#include "UseStdArray/UseStdArray.h"
#include "UseStdArray/UseStdArrayActions.h"
#include "UseStdArray/UseStdArrayMatchers.h"
#include "clang/Frontend/FrontendActions.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Process.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringRef.h"
#include "Core/Transform.h"

using namespace clang;
using namespace clang::tooling;
using clang::ast_matchers::MatchFinder;

// TODO generalize this code

class UseStdArrayTest : public UseStdArrayTransform {

    public:
    UseStdArrayTest( const TransformOptions& Options ) :
	UseStdArrayTransform(Options)
    {
    }
   
    auto transform_and_compare() {
	TransformOptions Options;

	// setup all the files that we are going to need
	SmallString<128> CurrentDir;
	std::error_code EC = llvm::sys::fs::current_path(CurrentDir);
	assert(!EC);
	(void)EC;

	SmallString<128> SourceFile = CurrentDir;
	llvm::sys::path::append(SourceFile, "a.cc");

	tooling::FixedCompilationDatabase Compilations(CurrentDir.str(),
						     std::vector<std::string>());
	std::vector<std::string> Sources;
	Sources.push_back(SourceFile.str());

	ClangTool UseStdArrayTool(Compilations, Sources );

	// the text for the main cpp file
	std::string cpp_input = 
    		      "int a[100];\n"
		      "void fun() {\n"
		      "  a[50] = 10;\n"
		      "}\n"
	;

	// TODO find out how this can be compared
	// the text that i expect to get after the transformation
	std::string cpp_output = 
    		      "#include <array.h>"
    		      "std::array<int, 100> a;\n"
		      "void fun() {\n"
		      "  a[50] = 10;\n"
		      "}\n"
	;

	// Fill in some code that can be compiled in memory
        UseStdArrayTool.mapVirtualFile(SourceFile, cpp_input);

	unsigned AcceptedChanges = 0;

	MatchFinder Finder;
	UseStdArrayFixer Fixer(AcceptedChanges, *this );

	Finder.addMatcher(makeUseStdArrayMatcher(), &Fixer);

	// syntactic checks are done inside
	if (int result = UseStdArrayTool.run(createActionFactory(Finder))) {
	    llvm::errs() << "Error encountered during translation.\n";
	    return result;
	}

	return 0;
    }
};


TEST( UseCompoundOperatorTest, UseStdArrayTestCase ) {
    TransformOptions Options;
    UseStdArrayTest Test(Options);
    EXPECT_EQ(Test.transform_and_compare(), 0);
}
