#include "allocator.h"

#define ALLOCATOR_MAX_SIZE_BYTES 65536
#define ALLOCATOR_CHUNK_SIZE_BYTES 8

struct chunk {
  unsigned int is_initial_chunk : 1; // 1 - this chunk is initial in a row, 0 - this chunk is in middle of some bigger allocation unit
  unsigned int is_free : 1; // 1 - free, 0 - not free
  void *chunk_ptr; // actual chunk pointer
};

// Actual memory which will be managed
char heap[ALLOCATOR_MAX_SIZE_BYTES];

// Array of chunks metadata
struct chunk chunk_list[ALLOCATOR_MAX_SIZE_BYTES / ALLOCATOR_CHUNK_SIZE_BYTES] = { 0 };

// Helper function to initialize the allocator
static void init_allocator() {
  static int initialized = 0;
  if (initialized) return;

  size_t chunk_array_size = ALLOCATOR_MAX_SIZE_BYTES / ALLOCATOR_CHUNK_SIZE_BYTES;
  for (size_t i = 0; i < chunk_array_size; i++) {
    chunk_list[i].is_free = 1;
    chunk_list[i].is_initial_chunk = 0;
    chunk_list[i].chunk_ptr = &heap[i * ALLOCATOR_CHUNK_SIZE_BYTES];
  }
  initialized = 1;
}

void* mem_alloc(size_t size) {
  init_allocator(); // Initialize allocator if needed

  if (size == 0 || size > ALLOCATOR_MAX_SIZE_BYTES) {
    return NULL; // Incorrect amount of memory requested
  }

  size_t chunks_needed = (size + ALLOCATOR_CHUNK_SIZE_BYTES - 1) / ALLOCATOR_CHUNK_SIZE_BYTES;
  size_t chunk_array_size = sizeof(chunk_list) / sizeof(struct chunk);

  for(size_t start = 0; start < chunk_array_size; start++) {
    if (!chunk_list[start].is_free) {
      continue;
    }

    size_t free_chunks_count = 0;

    for(size_t end = start; end < chunk_array_size; end++) {
      if (!chunk_list[end].is_free) {
        break;
      }
      free_chunks_count++;

      if (free_chunks_count == chunks_needed) {
        for (size_t i = start; i <= end; i++) {
          chunk_list[i].is_initial_chunk = i == start;
          chunk_list[i].is_free = 0;
          chunk_list[i].chunk_ptr = &heap[i * ALLOCATOR_CHUNK_SIZE_BYTES];
        }

        return chunk_list[start].chunk_ptr;
      }
    }
  }

  // No space is found
  return NULL;
}

void mem_dealloc(void* ptr) {
  if (ptr == NULL) { return; }

  long heap_offset = (char*) ptr - heap;
  if (heap_offset < 0 || heap_offset > ALLOCATOR_MAX_SIZE_BYTES) {
    return; // Invalid pointer
  }

  size_t chunk_index = heap_offset / ALLOCATOR_MAX_SIZE_BYTES;
  size_t chunk_array_size = sizeof(chunk_list) / sizeof(struct chunk);

  for (size_t i = chunk_index; i < chunk_array_size; i++) {
    // If current chunk is already free or we met next initial chunk
    if (chunk_list[i].is_free || (i != chunk_index && chunk_list[i].is_initial_chunk)) {
      break;
    }

    chunk_list[i].is_free = 1;
  }
}