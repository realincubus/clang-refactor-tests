set(LLVM_LINK_COMPONENTS support)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${ClangReplaceLocation}
  )
SET( CMAKE_EXPORT_COMPILE_COMMANDS on )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y" )

get_filename_component(CLANG_MODERNIZE_SOURCE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/../../clang-refactor REALPATH)
get_filename_component(ClangReplaceLocation
  "${CMAKE_CURRENT_SOURCE_DIR}/../../clang-apply-replacements/include" REALPATH)
get_filename_component(CommonIncLocation
  "${CMAKE_CURRENT_SOURCE_DIR}/../include" REALPATH)
include_directories(
  ${CLANG_MODERNIZE_SOURCE_DIR}
  ${ClangReplaceLocation}
  ${CommonIncLocation}
  )



add_extra_unittest( ClangRefactorTests
    UseCompoundAssignOperator.cpp
    UseStdArray.cpp
    UseConst.cpp
    UseMathConstants.cpp
    UseRAII.cpp
    CollapsibleIfStatement.cpp
    UseVector.cpp
    UseUnaryOperator.cpp
    ForLoopStartFromZero.cpp
    #    ../../UseCompoundAssignOperator/UseCompoundAssignOperator.cpp
    #    ../../UseCompoundAssignOperator/UseCompoundAssignOperatorMatchers.cpp 
    #    ../../UseCompoundAssignOperator/UseCompoundAssignOperatorActions.cpp 
)

TARGET_LINK_LIBRARIES( ClangRefactorTests
    clangAST
    clangASTMatchers
    clangBasic
    clangFormat
    clangFrontend
    clangLex
    clangTooling
    refactorApp
)

