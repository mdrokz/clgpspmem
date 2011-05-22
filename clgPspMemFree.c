/* clgPspMemFree.c */

#include "clgpspmem_internal.h"

void clgPspMemFree( void *ptr )
{
	SceUID mb_uid = *( (SceUID *)( (intptr_t)ptr - sizeof( SceUID ) ) );
	sceKernelFreePartitionMemory( mb_uid );
}
