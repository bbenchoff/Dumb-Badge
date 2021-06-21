// DOM-IGNORE-BEGIN
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */
// DOM-IGNORE-END

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "print.h"

extern int errno;
extern int _end;

/**
 * redirect the stdio output for printf
 */
void print_init(void) {
	/* set STDIO to unbuffered */
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
}

int _read(int file, char *ptr, int len) {
	int n = 0;

	if (file != 0) {
		return -1;
	}

	n = SERCOM0_read((char *)ptr, len);
	if (n < 0) {
		return -1;
	}

	return n;
}

int _write(int file, char *ptr, int len) {
	int n = 0;

	if ((file != 1) && (file != 2) && (file != 3)) {
		return -1;
	}

	n = SERCOM0_write((const char *)ptr, len);
	if (n < 0) {
		return -1;
	}

	return n;
}


/**
 * \brief Replacement of C library of _sbrk
 */
caddr_t _sbrk(int incr)
{
	static unsigned char *heap = NULL;
	unsigned char *       prev_heap;

	if (heap == NULL) {
		heap = (unsigned char *)&_end;
	}
	prev_heap = heap;

	heap += incr;

	return (caddr_t)prev_heap;
}

/**
 * \brief Replacement of C library of link
 */
int link(char *old, char *_new)
{
	(void)old, (void)_new;
	return -1;
}

/**
 * \brief Replacement of C library of _close
 */
int _close(int file)
{
	(void)file;
	return -1;
}

/**
 * \brief Replacement of C library of _fstat
 */
int _fstat(int file, struct stat *st)
{
	(void)file;
	st->st_mode = S_IFCHR;

	return 0;
}

/**
 * \brief Replacement of C library of _isatty
 */
int _isatty(int file)
{
	(void)file;
	return 1;
}

/**
 * \brief Replacement of C library of _lseek
 */
int _lseek(int file, int ptr, int dir)
{
	(void)file, (void)ptr, (void)dir;
	return 0;
}

/**
 * \brief Replacement of C library of _exit
 */
void _exit(int status)
{
	printf("Exiting with status %d.\n", status);

	for (;;)
		;
}

/**
 * \brief Replacement of C library of _kill
 */
void _kill(int pid, int sig)
{
	(void)pid, (void)sig;
	return;
}

/**
 * \brief Replacement of C library of _getpid
 */
int _getpid(void)
{
	return -1;
}



