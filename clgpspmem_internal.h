/* clgpspmem_internal.h                 */
/* 内部で使用。外から参照しない。 */

#include "clgpspmem.h"
#include <math.h>

/*=========================================================
	ローカルマクロ
=========================================================*/	
/* どこぞから拝借した、メモリアラインを調整するマクロ */
#define CLGPSPMEM_ALIGN_ADDR( align, addr ) ( ( (uintptr_t)( addr ) + ( align ) - 1 ) & ( ~( ( align ) - 1 ) ) )
#define CLGPSPMEM_POWER_OF_TWO( x ) ( ! ( ( x ) & ( ( x ) - 1 ) ) )
