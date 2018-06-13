#ifdef __cplusplus
extern "C" {
#endif

#ifndef FILE_SELECTOR_FUNCTIONS_H__
#define FILE_SELECTOR_FUNCTIONS_H__

#include "types.h"

extern FILE * __FS_files[32];
extern char * __FS_filenames[32];
extern unsigned short __FS_file_index;
extern pthread_mutex_t __FS_lock;


int init_file_selector ();

int destroy_file_selector ();

int add_file (char * filename, unsigned short * index);

int remove_file (unsigned short index);

unsigned short find_first_free_file ();

FILE * get_fd_by_index (unsigned short index);

unsigned short get_index_by_name (char * filename);

#endif // FILE_SELECTOR_FUNCTIONS_H__

#ifdef __cplusplus
}
#endif
