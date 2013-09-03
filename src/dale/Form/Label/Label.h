#ifndef DALE_FORM_LABEL
#define DALE_FORM_LABEL

namespace dale
{
namespace Form
{
namespace Label
{
bool execute(Generator *gen,
             Element::Function *fn,
             llvm::BasicBlock *block,
             Node *node,
             bool get_address,
             bool prefixed_with_core,
             ParseResult *pr);
}
}
}

#endif