/* clgPspMemCalloc.c */

#include "clgpspmem_internal.h"

void *clgPspMemCalloc( uint count, SceSize size )
{
	void *ptr;
	SceSize total_size;
	
	if( ! count ) count = 1;
	if( ! size  ) size  = 1;
	
	total_size = count * size;
	
	/*
		サイズチェック
		
		count * sizeがSceSize型の最大値を超えた(オーバーフローした)場合、
		この式は偽となりNULLを返す。
	*/
	if( total_size / size != count ) return NULL;
	
	ptr = clgPspMemAlloc( total_size );
	if( ptr ) sceKernelMemset( ptr, 0, total_size );
	
	return ptr;
}
