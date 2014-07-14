#pragma once


#include "gtest/gtest.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Frontend/CompilerInstance.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/Process.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringRef.h"
#include "Core/Transform.h"
#include <list>

using namespace clang;
using namespace clang::tooling;
using clang::ast_matchers::MatchFinder;


template < typename FixerType, typename BaseClass, typename MatcherProvider>
class Fixture : public BaseClass, MatcherProvider {

    public:
    Fixture( 
	std::string input, 
	std::string expected_output,
	std::list<std::string> additional_args = std::list<std::string>()
    ) :
	BaseClass( TransformOptions() )
    {
	// setup the compilation database
	SmallString<128> CurrentDir;
	std::error_code EC = llvm::sys::fs::current_path(CurrentDir);
	assert(!EC);
	(void)EC;

	tooling::FixedCompilationDatabase Compilations(
	    CurrentDir.str(),
	    std::vector<std::string>()
	);

	// setup all the files that we are going to need
	SmallString<128> SourceFile = CurrentDir;
	llvm::sys::path::append(SourceFile, "a.cc");

	std::vector<std::string> Sources;
	Sources.push_back(SourceFile.str());

	unsigned AcceptedChanges = 0;

	MatchFinder Finder;
	FixerType Fixer(AcceptedChanges, *this );

	Finder.addMatcher(MatcherProvider::makeMatcher(), &Fixer);

	auto* action_factory = BaseClass::createActionFactory(Finder);

	std::vector<std::string> Args;
	Args.push_back("-std=c++1y");

	for( auto element : additional_args ){
	    Args.push_back( element );
	}

	EXPECT_EQ( tooling::runToolOnCodeWithArgs(action_factory->create(), input, Args, SourceFile.str()), true );

	// all replacements for all files 
	auto& tu_replacement_map = this->getAllReplacements();

	// if nothing was replaced the result is the input
	std::string result = input;

	// find the replacements for the specific file
	auto entry = tu_replacement_map.find(SourceFile);
	if ( entry != tu_replacement_map.end() ) {
	    // get all replacements
	    auto& tu_replacements = entry->getValue();
	    auto& Replacements = tu_replacements.Replacements;
	    // applyAllReplacements wants a set not a vector
	    std::set<clang::tooling::Replacement> ReplacementSet;
	    std::copy( Replacements.begin(),
		Replacements.end(),
	        std::inserter(ReplacementSet,ReplacementSet.begin())
	    );
	    result = tooling::applyAllReplacements(input, ReplacementSet);
	}

	llvm::errs() << result;
	EXPECT_EQ( expected_output.compare(result),0 );
    }
};

