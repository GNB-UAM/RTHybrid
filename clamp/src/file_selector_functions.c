#include <stdio.h>
#include <stdlib.h>



char * files[32];
unsigned short file_index;


int init_file_selector () {
	int i;

	for (i = 0; i < 32; i++) {
		files[i] = NULL;
	}

	file_index = 0;

	return OK;
}


int destroy_file_selector () {
	int i;

	for (i = 0; i < 32; i++) {
		if (remove_file(i) == ERR) return ERR;
	}

	return OK;
}


int add_file (char * filename, unsigned short * index) {
	if (filename == NULL || file_index == 32) return ERR;

	if (asprintf(files[file_index], "%s", filename) < 0) return ERR;
	*index = file_index;

	file_index = find_first_free_file();

	return OK;
}


int remove_file (unsigned short index) {
	free_pointers(1, &(files[index]));

	if (file_index > index) file_index = index; 

	return OK;
}


unsigned short find_first_free_file () {
	unsigned short i;

	for (i = 0; i < 32; i++) {
		if (files[i] == NULL) return i;
	}

	return i;
}

char * get_file (unsigned short index) {
	return files[index];
}