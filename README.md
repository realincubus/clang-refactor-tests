clang-refactor-tests
====================

optional tests for clang-refactor
this repository keeps the tests for clang-refactor.

### Installation


in a stable llvm+clang build do
```sh
git clone https://github.com/realincubus/clang-refactor-tests.git {LLVM_ROOT}/tools/clang/tools/extra/unittests/clang-refactor`
``` 

and add 

```cmake 
add_subdirectory( clang-refactor )
```

to tools/clang/tools/extra/unittests/CMakeLists.txt
this will register the tests in the llvm+clang testing framework

### Run Tests

llvm and clang use llvm-lit to run all tests.
go to `{LLVM_BUILD_DIR}/tools/clang/tools/extra/test` and run 

```sh
llvm-lit .
```
