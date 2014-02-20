/*
 * Без имени.c
 * 
 * Copyright 2014 Lex <lex22@ubuntu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	/* read(), write(), close() */
#include <fcntl.h>	/* open(), O_RDONLY */
#include <sys/stat.h>	/* S_IRUSR */
#include <sys/types.h>	/* mode_t */

#define BUFFER_SIZE	64

int main (int argc, char ** argv)
{
	int fd, fd1;
	ssize_t read_bytes;
	ssize_t written_bytes;
	char buffer[BUFFER_SIZE];
	if (argc < 2)
	{
		fprintf (stderr, "Too few arguments\n");
		exit (1);
	}


	fd = open (argv[1], O_RDONLY);

	if (fd < 0)
	{
		fprintf (stderr, "Cannot open file\n");
		exit (1);
	}	
	
	
	
	fd1 = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0600);
	
	if (fd < 0)
	{
		fprintf (stderr, "Cannot open file\n");
		exit (1);
	}		
	
	while ((read_bytes = read (fd, buffer, BUFFER_SIZE)) > 0)
	{		
		/* 1 == stdout */
		written_bytes = write (fd1, buffer, read_bytes);
		if (written_bytes != read_bytes)
		{
			fprintf (stderr, "Cannot write\n");
			exit (1);
		}
	}

	if (read_bytes < 0)
	{
		fprintf (stderr, "myread: Cannot read file\n");
		exit (1);
	}
	close (fd);
	close(fd1);
	exit (0);
}
