/* Author: Robbert van Renesse 2018
 *
 * The interface is as follows:
 *	reader_t reader_create(int fd);
 *		Create a reader that reads characters from the given file descriptor.
 *
 *	char reader_next(reader_t reader):
 *		Return the next character or -1 upon EOF (or error...)
 *
 *	void reader_free(reader_t reader):
 *		Release any memory allocated.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shall.h"

struct reader {
	int fd;
	char buffer[512];
	int size;
	int index; 

};

reader_t reader_create(int fd){
	reader_t reader = (reader_t) calloc(1, sizeof(*reader));
	reader->fd = fd;
	reader->index = 0; //start at first index 
	reader->size = 0; //initialize size to be zero
	return reader;
}

char reader_next(reader_t reader){
	//condition for if the index is one less than the size, or the size
	if(reader->index == reader->size)
	{
		//reset the index, get the size, return next character buffer or EOF 
		reader->index = 0;
		reader->size = read(reader->fd, &(reader->buffer), 512);
		//return first char of buffer if size is not zero
		//return EOF if size is zero
		return reader->size != 0 ? reader->buffer[0] : EOF;
	}
	else
	{
		//increment index, return next character
		reader->index = reader->index + 1;
		return reader->buffer[reader->index];
	}
}

void reader_free(reader_t reader){
	free(reader);
}
