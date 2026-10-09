#include <stdlib.h>
#include <stdio.h>

#include "loader.h"

void *ld_load_file(const char *path, unsigned int *out_size) {
  if (!path || !out_size) { return NULL; } 

  FILE *f = fopen(path, "rb");
  if (!f) { return NULL; }

  int size;
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);

  if (size <= 0) { goto func_err; }
  if (size > MAX_FILE_SIZE) { goto func_err; }

  void *buf = malloc(size);
  if (!buf) { goto func_err; }

  size_t b = fread(buf, 1, size, f);
  if (b != (size_t)size) { free(buf); return NULL; }

  *out_size = (unsigned int)size;
  return buf;

func_err:
  fclose(f);
  return NULL;
}

void ld_free_file(void *buf) {
  free(buf);
}