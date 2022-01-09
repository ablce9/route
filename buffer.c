#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "buffer.h"
#include "region.h"


__buffer_t *create_chain_buffer(region_t *r, size_t size) {
    __buffer_t *buf;

    buf = calloc(1, sizeof(__buffer_t));
    if (buf == NULL) {
	return NULL;
    }

    r = ralloc(r, size);
    buf->start = (char *)(r + sizeof(region_t));
    if (buf->start == NULL) {
	return NULL;
    }

    buf->pos = buf->start;
    buf->end = buf->start + size;

    return buf;
}

__buffer_t *alloc_new_buffer(const char *buffer) {
    if (buffer[0] == '\0') {
	return NULL;
    }

    __buffer_t *buf = calloc(1, sizeof(__buffer_t));
    int buffer_size = 0;

    while ((buffer[buffer_size] != '\0')) {
	++buffer_size;
    }
    ++buffer_size;

    buf->bytes = calloc(buffer_size, sizeof(char));
    buf->start = buf->bytes;
    buf->pos = buf->start;
    buf->end = buf->bytes + buffer_size;
    buf->size = buffer_size;

    memcpy(buf->bytes, buffer, buffer_size);

    return buf;
}

__buffer_t *buffer_bytes_ncpy(const __buffer_t *src_buf, const size_t size) {
    __buffer_t *dst_buf = calloc(1, sizeof(__buffer_t));

    dst_buf->bytes = calloc(size, sizeof(char));
    dst_buf->size = size;
    memcpy(dst_buf->bytes, src_buf->bytes, size);
    dst_buf->end = dst_buf->bytes + size;

    return dst_buf;
}
