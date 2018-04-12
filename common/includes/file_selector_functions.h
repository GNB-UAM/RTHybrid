#include "types.h"

FILE * __FS_files[32];
char * __FS_filenames[32];
unsigned short __FS_file_index;
pthread_mutex_t __FS_lock;


int init_file_selector ();

int destroy_file_selector ();

int add_file (char * filename, unsigned short * index);

int remove_file (unsigned short index);

unsigned short find_first_free_file ();

FILE * get_fd_by_index (unsigned short index);

unsigned short get_index_by_name (char * filename);