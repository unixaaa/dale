#ifndef DALE_ELEMENT_VARIABLE
#define DALE_ELEMENT_VARIABLE

#include "../Type/Type.h"

#include <string>
#include <cstdlib>

#include "../llvm_Module.h"
#include "../llvm_Function.h"
#include "llvm/PassManager.h"
#include "../llvm_CallingConv.h"
#include "../llvm_AnalysisVerifier.h"
#include "../llvm_AssemblyPrintModulePass.h"
#include "../llvm_IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

namespace dale
{
/*! Variable

    A class for storing the details of a variable.
*/
class Variable
{
public:
    /*! The variable's type. */
    Type *type;
    /*! The variable's name (unqualified, unmangled). */
    std::string name;
    /*! The variable's internal name (qualified, mangled). */
    std::string internal_name;
    /*! The variable's value. */
    llvm::Value *value;
    /*! For a variable with one of the extern linkages, this indicates
        whether space has been set aside for it (extern variables work
        in the same way here as they do in C). */
    int has_initialiser;
    /*! The once tag of the variable. */
    std::string once_tag;
    /*! The variable's index.  This is set by Namespace on variable
     *  insertion. */
    int index;
    /*! The variable's linkage. */
    int linkage;
    /*! Whether the variable should be serialised. */
    bool serialise;

    Variable();
    /*! Construct a new variable with the given name and type.
     *  @param name The variable's name (unqualified, unmangled).
     *  @param type The variable's type.
     *
     *  name is copied.  type is not copied.
     */
    Variable(const char *name, Type *type);

    ~Variable();

    /*! Check whether a variable is equal to another variable.
     *  @param var The other variable.
     *
     *  Two variables are considered equal if their types compare
     *  equal, as per dale::Type::isEqualTo.
     */
    bool isEqualTo(Variable *var);
};
}

#endif
