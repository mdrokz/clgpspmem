/*=========================================================

	PSP Memory Manager

=========================================================*/

#ifndef CLGPSPMEM_H
#define CLGPSPMEM_H

#include <pspkernel.h>
#include "../clgcommon/clg.h"

/*=========================================================
	マクロ
=========================================================*/
#ifdef __cplusplus
extern "C" {
#endif


/*=========================================================
	型宣言
=========================================================*/
/** PSPメモリパーティションID。 */
typedef enum ClgPspMemPartitionId {
	/** カーネル領域。(offset=0x88000000, size=0x300000(3MB), attr=0x0C) */
	CLGPSPMEM_KERN_HI  = 1,
	/** ユーザ領域。  (offset=0x08800000, size=0x1800000(24MB), attr=0x0F) */
	CLGPSPMEM_USER     = 2,
	/** カーネル領域。(offset=0x88300000, size=0x100000(1MB), attr=0x0C) */
	CLGPSPMEM_KERN_LO  = 4,
	/** カーネル領域。(offset=0x08400000, size=0x400000(4MB), attr=0x0F)
	  sceKernelVolatileMem*(Lock/TryLock/Unlock)でアクセスする?
	  全領域を使うか使わないかの二択で少しだけ使うとかはできないっぽい?
	  SCEの一部の公式ライブラリ(セーブロードダイアログやネットワーク関連)が、この領域を使用しているようなので、
	  ここを勝手に使うとフリーズの危険性があるかもしれない。 */
	CLGPSPMEM_VOLATILE = 5,
	/** PSP-2000以降の拡張領域。(offset=0x8A000000, size=0x1C00000(28MB), attr=0x0C)
	  PSP_LARGE_MEMORY=1付きでビルドする必要がある、のか? */
	CLGPSPMEM_EXTRA_1  = 8,
	/** PSP-2000以降の拡張領域。(offset=0x8BC00000, size=0x400000(4MB), attr=0x0C)
	  PSP_LARGE_MEMORY=1付きでビルドする必要がある、のか? */
	CLGPSPMEM_EXTRA_2  = 10,
} ClgPspMemPartitionId;

/** メモリの確保方法。*/
typedef enum ClgPspMemAllocType {
	/** メモリアドレスの前方から空きメモリを探す。*/
	CLGPSPMEM_LO   = PSP_SMEM_Low,
	/** メモリアドレスの後方から空きメモリを探す。*/
	CLGPSPMEM_HI   = PSP_SMEM_High,
	/** 指定アドレスからメモリを確保する。
	  指定したアドレスが使用されていた場合はエラー。 */
	CLGPSPMEM_ADDR = PSP_SMEM_Addr
} ClgPspMemAllocType;

/** メモリ確保時に使用できる詳細オプション。*/
typedef struct ClgPspMemOptParams
{
	/** メモリブロックに付ける名前。sceKernelSearchUIDByName()などで使用するらしいがよくわからない。*/
	ClgStr             Name; 
	/** 確保するパーティションID。*/
	int                Partition;
	/** メモリのアライメント。0で自動。*/
	unsigned int       Boundary;
	/** メモリの確保方法。*/
	ClgPspMemAllocType Type;
	/** TypeにCLGMEM_ADDRを指定した場合に指定。
	  確保したいアドレスを指定する。
	  それ以外ではNULLでよい。*/
	void               *Addr;
} ClgPspMemOptParams;


/*=========================================================
	関数
=========================================================*/

/**
 * メモリを確保。
 *
 * @param size - 確保するサイズ。
 * @param opt - 詳細オプションを指定した構造体。NULLで省略可。
 * @return NULL でエラー。
 * @see clgPspMemOptParams
 */
void *clgPspMemExalloc( SceSize size, ClgPspMemOptParams *opt );

/**
 * 簡易メモリ確保。
 *
 * @param size - 確保するメモリサイズ。
 * @return < 0 でエラー。
 */
#define clgPspMemAlloc( size ) clgPspMemExalloc( size, NULL )

/**
 * メモリを確保して領域をゼロクリア。
 *
 * @param count - 確保する要素数。
 * @param size - 一要素のサイズ。
 * @return NULLでエラー。
 */
void *clgPspMemCalloc( uint count, SceSize size );

/**
 * 指定バウンダリでアライメントされたメモリアドレスを確保。
 *
 * @param boundary - バウンダリ。
 * @param size - 確保するサイズ。
 * @return NULLでエラー。
 */
void *clgPspMemAlign( uint boundary, SceSize size );

/**
 * 確保したメモリを解放。
 *
 * @param ptr - 確保した領域のポインタ。
 */
void clgPspMemFree( void *ptr );

#ifdef __cplusplus
}
#endif

#endif
