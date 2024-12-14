//
// Created by tre3p on 14.12.2024.
//

#ifndef DUMMY_MEMORY_ALLOCATOR__ALLOCATOR_H_
#define DUMMY_MEMORY_ALLOCATOR__ALLOCATOR_H_

#include <stdlib.h>

void* mem_alloc(size_t);
void mem_dealloc(void*);

#endif //DUMMY_MEMORY_ALLOCATOR__ALLOCATOR_H_
