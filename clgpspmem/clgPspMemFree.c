/* clgPspMemFree.c */

#include "clgpspmem_internal.h"

void clgPspMemFree( void *ptr )
{
	SceUID mb_uid = *( (SceUID *)( (intptr)ptr - sizeof( SceUID ) ) );
	sceKernelFreePartitionMemory( mb_uid );
}
