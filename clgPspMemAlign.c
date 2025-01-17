/* clgPspMemAlign.c */

#include "clgpspmem_internal.h"

void *clgPspMemAlign( unsigned int boundary, SceSize size )
{
	ClgPspMemOptParams params = { "CLGPSPMEM", CLGPSPMEM_USER, boundary, CLGPSPMEM_LO, NULL };
	return clgPspMemExalloc( size, &params );
}
