/* clgPspMemExalloc.c */

#include "clgpspmem_internal.h"

static ClgMemOptParams st_default_params = { "CLGPSPMEM", CLGPSPMEM_USER, 0, CLGMEM_LO, NULL };

void *clgPspMemExalloc( SceSize size, ClgPspMemOptParams *opt )
{
	SceUID mb_uid;
	void   *mb_head;
	
	/* オプションがNULLであれば、デフォルト値を使用 */
	if( ! opt ) opt = &st_default_params;
	
	/* 取得サイズが0であれば、最小値で確保 */
	if( ! size ) size = 1;
	
	/* パーティションにメモリを確保 */
	mb_uid = sceKernelAllocPartitionMemory( opt->Partition, opt->Name, opt->Type, sizeof( SceUID ) + size, opt->Addr );
	if( ! is_valid_uid( mb_uid ) ) return NULL;
	
	/* メモリアドレスを取得すると同時に、ブロックIDを記録するエリア分ずらす */
	mb_head = (void *)( (uintptr)sceKernelGetBlockHeadAddr( mb_uid ) + sizeof( SceUID ) );
	
	/* アライメントを調整 */
	if( align ){
		if( ! PSPMM_POWER_OF_TWO( align ) ){
			sceKernelFreePartitionMemory( mb_uid );
			return NULL;
		}
		mb_head = (void *)CLGPSPMEM_ALIGN_ADDR( align, mb_head );
	}
	
	/* 最終的に返すメモリアドレスから、ずらしたエリア分戻ってブロックIDを記録 */
	*( (SceUID *)( (uintptr)mb_head - sizeof( SceUID ) ) = mb_uid;
	
	return mb_head;
}
