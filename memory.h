#pragma once

#include <stddef.h>

extern char __data_end;
extern char __heap_base;

void* malloc(size_t size);
void free(void* ptr);

void* operator new[](size_t size);
void operator delete[](void* ptr) noexcept;
