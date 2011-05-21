/* clgPspMemAlign.c */

#include "clgpspmem_internal.h"

void *clgPspMemAlign( uint boundary, SceSize size )
{
	ClgPspMemOptParams params = { "CLGPSPMEM", CLGPSPMEM_USER, boundary, CLGMEM_LO, NULL };
	return clgPspMemExalloc( size, &params );
}
