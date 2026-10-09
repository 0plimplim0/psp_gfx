#ifndef LOADER_H
#define LOADER_H

#define MAX_FILE_SIZE (10 * 1024 * 1024)

void *ld_load_file(const char *path, unsigned int *out_size);
void ld_free_file(void *buf);

#endif