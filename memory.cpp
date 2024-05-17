#include "memory.h"

static char* ptr = &__heap_base;

void* malloc(size_t size) {
    ((size_t*)ptr)[0] = size;
    ptr += sizeof(size_t);
    void* ret = ptr;
    ptr += size;
    return ret ;
}

void free(void* d) {
    ptr -= ((size_t*)d)[-1];
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void* p) noexcept {
    return free(p);
}

