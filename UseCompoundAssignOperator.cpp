

#include "gtest/gtest.h"
#include "UseCompoundAssignOperator/UseCompoundAssignOperator.h"
#include "UseCompoundAssignOperator/UseCompoundAssignOperatorActions.h"
#include "UseCompoundAssignOperator/UseCompoundAssignOperatorMatchers.h"
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

class UseCompoundAssignOperatorTest : public UseCompoundAssignOperatorTransform {

    public:
    UseCompoundAssignOperatorTest( const TransformOptions& Options ) :
	UseCompoundAssignOperatorTransform(Options)
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
#if 0
	SmallString<128> HeaderFile = CurrentDir;
	llvm::sys::path::append(HeaderFile, "a.h");

	SmallString<128> HeaderBFile = CurrentDir;
	llvm::sys::path::append(HeaderBFile, "temp");
	llvm::sys::path::append(HeaderBFile, "b.h");
	StringRef ExcludeDir = llvm::sys::path::parent_path(HeaderBFile);

	IncludeExcludeInfo IncInfo;
	Options.ModifiableFiles.readListFromString(CurrentDir, ExcludeDir);
#endif

	tooling::FixedCompilationDatabase Compilations(CurrentDir.str(),
						     std::vector<std::string>());
	std::vector<std::string> Sources;
	Sources.push_back(SourceFile.str());

	ClangTool UseCompoundAssignOperatorTool(Compilations, Sources );

	// the text for the main cpp file
	std::string cpp_input = 
//		      "#include \"a.h\"\n"
//    		      "#include \"temp/b.h\"\n"
    		      "int a;\n"
		      "void fun() {\n"
		      "  a = a + 1;\n"
		      "}\n"
	;

	// TODO find out how this can be compared
	// the text that i expect to get after the transformation
	std::string cpp_output = 
//		      "#include \"a.h\"\n"
//    		      "#include \"temp/b.h\"\n"
    		      "int a;\n"
		      "void fun() {\n"
		      "  a += 1;\n"
		      "}\n"
	;

	// Fill in some code that can be compiled in memory
        UseCompoundAssignOperatorTool.mapVirtualFile(SourceFile, cpp_input);
        //UseCompoundAssignOperatorTool.mapVirtualFile(HeaderFile, "int b;");
        //UseCompoundAssignOperatorTool.mapVirtualFile(HeaderBFile, "int c;");

	unsigned AcceptedChanges = 0;

	MatchFinder Finder;
	UseCompoundAssignOperatorFixer Fixer(AcceptedChanges, *this );

	Finder.addMatcher(makeUseCompoundAssignOperatorMatcher(), &Fixer);

	// syntactic checks are done inside
	if (int result = UseCompoundAssignOperatorTool.run(createActionFactory(Finder))) {
	    llvm::errs() << "Error encountered during translation.\n";
	    return result;
	}

	return 0;
    }
};


TEST( UseCompoundOperatorTest, UseCompoundAssignOperatorTestCase ) {
    TransformOptions Options;
    UseCompoundAssignOperatorTest Test(Options);
    EXPECT_EQ(Test.transform_and_compare(), 0);
}