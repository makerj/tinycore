#ifndef __UTIL_RING_H__
#define __UTIL_RING_H__

#include <stdio.h>

/**
 * @file
 * Ring buffer data structure for strings
 */

/**
 * Write string to the ring buffer.
 *
 * @param buf ring buffer
 * @param head ring buffer head
 * @param tail ring buffer tail
 * @param size ring buffer size
 * @param data string to write
 * @param len string length
 * @return written length
 */
ssize_t ring_write(char* buf, size_t head, volatile size_t* tail, size_t size, const char* data, size_t len);

/**
 * Read string from the ring buffer.
 *
 * @param buf ring buffer
 * @param head ring buffer head
 * @param tail ring buffer tail
 * @param size ring buffer size
 * @param data string bufffer to read
 * @param len string buffer length
 * @return read length
 */
ssize_t ring_read(char* buf, volatile size_t *head, size_t tail, size_t size, char* data, size_t len);

/**
 * Get written string length.
 *
 * @param head ring buffer head
 * @param tail ring buffer tail
 * @param size ring buffer size
 * @return written string length
 */
size_t ring_readable(size_t head, size_t tail, size_t size);

/**
 * Get available space to write.
 *
 * @param head ring buffer head
 * @param tail ring buffer tail
 * @param size ring buffer size
 * @return available space to write
 */
size_t ring_writable(size_t head, size_t tail, size_t size);

#endif /* __UTIL_RING_H__ */
