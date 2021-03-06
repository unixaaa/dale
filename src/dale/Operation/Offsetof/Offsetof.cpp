#include "Offsetof.h"

#include <cstdio>

namespace dale
{
namespace Operation
{
static int
nameToIndex(Context *ctx,
            Type *type,
            const char *member_name)
{
    Struct *st = ctx->getStruct(type);
    assert(st);

    int index = st->nameToIndex(member_name);
    assert(index != -1);

    return index;
}

uint64_t
OffsetofGet(Unit *unit,
            Type *type,
            int index)
{
    Context *ctx = unit->ctx;
    llvm::Type *llvm_type = ctx->toLLVMType(type, NULL, false);
    if (!llvm_type) {
        return false;
    }
    std::vector<llvm::Value *> indices;
    indices.push_back(ctx->nt->getNativeInt(index));
    llvm::ArrayRef<llvm::Value *> indices_aref(indices);

    /* todo: When built against a debug build of 3.5.2, things fail at
     * this point, because the argument type to getIndexedOffset is
     * not a pointer type.  Making that change alone, though, causes
     * tests to fail, so this required further investigation. */
#if D_LLVM_VERSION_MINOR <= 4
    llvm::DataLayout data_layout(unit->module->getDataLayout());
    return data_layout.getIndexedOffset(llvm_type, indices_aref);
#else
    return unit->module->getDataLayout()
                       ->getIndexedOffset(llvm_type, indices_aref);
#endif
}

bool
Offsetof(Unit *unit,
         llvm::BasicBlock *block,
         Type *type,
         const char *member_name,
         ParseResult *pr)
{
    size_t size =
        OffsetofGet(unit, type, nameToIndex(unit->ctx, type, member_name));
    pr->set(block, unit->ctx->tr->type_size,
            llvm::ConstantInt::get(
                unit->ctx->toLLVMType(unit->ctx->tr->type_size,
                                      NULL, false),
                size
            ));
    return true;
}

size_t
OffsetofGetByIndex(Unit *unit,
                   Type *type,
                   int index)
{
    return OffsetofGet(unit, type, index);
}
}
}
