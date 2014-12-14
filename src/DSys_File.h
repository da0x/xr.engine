/*
-------------------------------------------
Daher Engine
------------

	$Author: Daher Alfawares $
	$Revision: 1.3 $
	$Date: 2004/07/31 19:22:02 $
	$Id: DSys_File.h,v 1.3 2004/07/31 19:22:02 Daher Alfawares Exp $
	$Name:  $

	Copyright (c) 2004, Daher Alfawares
-------------------------------------------
*/



#ifndef ___DFILE_H
#define ___DFILE_H

/*
TODO List:
- ...
*/


typedef int file_t;

file_t fs_open( const char *fname, const char *reason);
void fs_close( file_t& handle);
int fs_length( file_t handle);
int fs_load( char *buffer, file_t handle);
int fs_read( char *buffer, int size, file_t handle);
int fs_write( char *buffer, int size, file_t handle);
int fs_printf( file_t handle, char *fmt, ...);
int fs_scanf( file_t handle, char *fmt, ...);
bool fs_readln(char	*buffer, file_t handle);
bool fs_writeln(const char *fmt, file_t handle, ...);
void fs_flush(file_t handle);

#endif // ___DFILE_H