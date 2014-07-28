
#include "CommonSingleFileTesting.hpp"
#include "UseFullyQualifiedTypes/UseFullyQualifiedTypes.h"
#include "UseFullyQualifiedTypes/UseFullyQualifiedTypesActions.h"
#include "UseFullyQualifiedTypes/UseFullyQualifiedTypesMatchers.h"

namespace {
class MatcherProvider {
    protected:
	auto makeMatcher(){
	    return makeUseFullyQualifiedTypesMatcher();
	}
};

typedef Fixture<UseFullyQualifiedTypesFixer,UseFullyQualifiedTypesTransform,MatcherProvider> UseFullyQualifiedTypesFixture;
}

TEST( UseFullyQualifiedTypesTest, VectorToStdVector ) {
    // input for the transformation
    std::string cpp_input = 
	"#include <vector>\n"
	"using namespace std;\n"
	"void fun() {\n"
	"  vector<int> a;\n"
	"}\n"
    ;
    // the text that i expect to get after the transformation
    std::string cpp_output = 
	"#include <vector>\n"
	"using namespace std;\n"
	"void fun() {\n"
	"  std::vector<int> a;\n"
	"}\n"
    ;
    UseFullyQualifiedTypesFixture Test(cpp_input,cpp_output);
}

