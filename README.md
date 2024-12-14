A teaching example of a very inefficient custom memory allocator. Current implementation uses fixed-size chunks of memory and for each chunk some metadata is stored(look at chunk struct in `allocator.c` for more details`).

To play with it:
1) Change code as you want in `example/usage_example.c`
2) Adjust parameters of `ALLOCATOR_MAX_SIZE_BYTES` and `ALLOCATOR_CHUNK_SIZE_BYTES` in `allocator.c`
3) Execute `make` command