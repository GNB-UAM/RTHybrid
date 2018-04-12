#include "../includes/file_selector_functions.h"


int __FS_mutex_init (pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr) {
	#ifndef __XENO__
		return pthread_mutex_init(mutex, attr);
	#else /* __XENO__ */
		return __real_pthread_mutex_init(mutex, attr);
	#endif /* __XENO__ */
}


int __FS_mutex_destroy (pthread_mutex_t *mutex) {
	#ifndef __XENO__
		return pthread_mutex_destroy(mutex);
	#else /* __XENO__ */
		return __real_pthread_mutex_destroy(mutex);
	#endif /* __XENO__ */
}


int __FS_mutex_lock(pthread_mutex_t *mutex) {
	#ifndef __XENO__
		return pthread_mutex_lock(mutex);
	#else /* __XENO__ */
		return __real_pthread_mutex_lock(mutex);
	#endif /* __XENO__ */
}


int __FS_mutex_unlock(pthread_mutex_t *mutex) {
	#ifndef __XENO__
		return pthread_mutex_unlock(mutex);
	#else /* __XENO__ */
		return __real_pthread_mutex_unlock(mutex);
	#endif /* __XENO__ */
}


int init_file_selector () {
	int i;

	for (i = 0; i < 32; i++) {
		__FS_files[i] = NULL;
		__FS_filenames[i] = NULL;
	}

	__FS_file_index = 0;

	__FS_mutex_init(&__FS_lock, NULL);

	return OK;
}


int destroy_file_selector () {
	int i;

	for (i = 0; i < 32; i++) {
		if (remove_file(i) == ERR) return ERR;
	}

	__FS_mutex_destroy(&__FS_lock);

	return OK;
}


int add_file (char * filename, unsigned short * index) {
	if (filename == NULL || __FS_file_index >= 32) return ERR;

	__FS_mutex_lock(&__FS_lock);

	*index = get_index_by_name(filename);
	if (*index >= 32) {
		__FS_files[__FS_file_index] = fopen(filename, "a");
		asprintf(&(__FS_filenames[__FS_file_index]), "%s", filename);
		*index = __FS_file_index;

		__FS_file_index = find_first_free_file();
	}

	__FS_mutex_unlock(&__FS_lock);

	return OK;
}


int remove_file (unsigned short index) {

	 __FS_mutex_lock(&__FS_lock);

	if (__FS_files[index] != NULL) {
		fclose(__FS_files[index]);
		free(__FS_filenames[index]);
		__FS_files[index] = NULL;
		__FS_filenames[index] = NULL;

		if (__FS_file_index > index) __FS_file_index = index;
	}

	__FS_mutex_unlock(&__FS_lock);

	return OK;
}


unsigned short find_first_free_file () {
	unsigned short i;

	for (i = 0; i < 32; i++) {
		if (__FS_files[i] == NULL) break;
	}

	return i;
}


FILE * get_fd_by_index (unsigned short index) {
	return __FS_files[index];
}


unsigned short get_index_by_name (char * filename) {
	int i;

	for (i = 0; i < 32; i++) {
		if (__FS_files[i] != NULL) {
			if (strcmp(__FS_filenames[i], filename) == 0) {
				break;
			}
		}
	}

	return i;
}