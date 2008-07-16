/* 
 *  Copyright 2008
 *  Texas Instruments Incorporated
 *
 *  All rights reserved.  Property of Texas Instruments Incorporated
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 * 
 */
/*
 *  ======== Memory.h ========
 */
/**
 *  @file       ti/sdo/ce/osal/Memory.h
 *
 *  @brief      The Codec Engine OSAL Memory interface.  Provides the user
 *              an OS-independent Memory abstraction.
 */
/**
 *  @defgroup   ti_sdo_ce_osal_Memory     Codec Engine OSAL - Memory
 */

#ifndef ti_sdo_ce_osal_Memory_
#define ti_sdo_ce_osal_Memory_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_sdo_ce_osal_MEMORY */
/*@{*/

/*
 *  ======== Memory_DEFAULTALIGNMENT ========
 */
#define Memory_DEFAULTALIGNMENT ((UInt)(-1))

/*
 *  ======== Memory_GTNAME ========
 */
#define Memory_GTNAME "OM"

/** @cond INTERNAL */

/**
 *  @brief      Statistics structure for a memory section.
 *
 *  @remarks    Applicable to BIOS only.
 */
typedef struct Memory_Stat {
    String name;     /**< Name of memory segment. */
    Uint32 base;     /**< Base of memory segment. */
    UInt size;       /**< Original size of segment. */
    UInt used;       /**< Number of bytes used in segment. */
    UInt length;     /**< Length of largest contiguous block. */
} Memory_Stat;

/** @endcond */

/**
 *  @brief      Enum values for Memory_AllocParams.type
 *
 *  @sa Memory_AllocParams
 */
typedef enum {
    Memory_MALLOC = 0,        /**< malloc()-based allocation */
    Memory_SEG = 1,           /**< DSP/BIOS segment-based allocation */
    Memory_CONTIGPOOL = 2,    /**< Contiguous, pool-based allocation */
    Memory_CONTIGHEAP =3      /**< Contiguous, heap-based allocation */
} Memory_type;

/**
 * @brief       Parameters for Memory_alloc() & Memory_free()
 *
 * @sa Memory_DEFAULTPARAMS
 */
typedef struct Memory_AllocParams {
    Memory_type type;   /**< Type of allocation.
                         *
                         *   @sa Memory_type
                         */
    UInt flags;         /**< Flags affecting allocation.
                         *
                         *   @sa Memory_CACHED
                         *   @sa Memory_NONCACHED
                         */
    UInt align;         /**< Alignment of allocation. */
    UInt seg;           /**< Segment for allocation. */
} Memory_AllocParams;


#define Memory_CACHED           0x00000000  /**< Cached allocation.
                                             *
                                             *   @sa Memory_AllocParams.flags
                                             */
#define Memory_NONCACHED        0x00000001  /**< Non-cached allocation.
                                             *
                                             *   @sa Memory_AllocParams.flags
                                             */
/** @cond INTERNAL */

#define Memory_CACHEDMASK       0x00000001  /**< mask to isolate cache flag.
                                             *
                                             *   @sa Memory_AllocParams.flags
                                             */
/** @endcond */

/**
 * @brief Default parameters for Memory_alloc() & Memory_free()
 *
 * @remarks Memory_DEFAULTPARAMS will be used when NULL is passed in the
 *          Memory_AllocParams parameter for Memory_alloc() &
 *          Memory_free().  When passing a non-NULL Memory_AllocParams
 *          parameter, you should first copy Memory_DEFAULTPARAMS to
 *          your structure and then modify individual elements as
 *          needed:
 *
 * @code
 *      Memory_AllocParams  myParams;
 *
 *      myParams = Memory_DEFAULTPARAMS;
 *      myParams.type = Memory_CONTIGHEAP;
 * @endcode
 *
 * @sa      Memory_alloc()
 * @sa      Memory_free()
 */
extern Memory_AllocParams Memory_DEFAULTPARAMS;

/*
 *  ======== Memory_alloc ========
 */
/**
 *  @brief      General memory allocation.
 *
 *  @param[in]  size    Number of bytes to allocate.
 *  @param[in]  params  Parameters controlling the allocation.
 *
 *  @retval     NULL     The memory request failed.
 *  @retval     non-NULL The pointer to a buffer containing the requested
 *                       memory.
 *
 *  @sa         Memory_free()
 *  @sa         Memory_contigAlloc()
 */
extern Ptr Memory_alloc(UInt size, Memory_AllocParams *params);

/*
 *  ======== Memory_cacheInv ========
 */
/**
 *  @brief      Invalidate a range of cache.
 *
 *  @param[in]  addr            Address of the beginning of the buffer
 *                               to invalidate.
 *  @param[in]  sizeInBytes     Size of the buffer to invalidate.
 *
 *  @remarks    In addition to application usage, this is often called by
 *              a skeleton implementor after it has received a shared memory
 *              buffer from another processor, and before it invokes an
 *              algorithm's interface which will operate on that shared
 *              memory buffer.
 *
 *  @sa         Memory_cacheWb()
 *  @sa         Memory_cacheWbInv()
 */
extern Void Memory_cacheInv(Ptr addr, Int sizeInBytes);


/*
 *  ======== Memory_cacheWb ========
 */
/**
 *  @brief      Write back cache.
 *
 *  @param[in]  addr            Address of the beginning of the buffer
 *                              to writeback.
 *  @param[in]  sizeInBytes     Size of the buffer to writeback.
 *
 *  @sa         Memory_cacheInv()
 *  @sa         Memory_cacheWbInv()
 */
extern Void Memory_cacheWb(Ptr addr, Int sizeInBytes);


/*
 *  ======== Memory_cacheWbInv ========
 */
/**
 *  @brief      Write back and invalidate cache.
 *
 *  @param[in]  addr            Address of the beginning of the buffer
 *                              to writeback and invalidate.
 *  @param[in]  sizeInBytes     Size of the buffer to writeback invalidate.
 *
 *  @sa         Memory_cacheInv()
 *  @sa         Memory_cacheWb()
 */
extern Void Memory_cacheWbInv(Ptr addr, Int sizeInBytes);


/*
 *  ======== Memory_contigAlloc ========
 */
/**
 *  @brief      Allocate physically contiguous blocks of memory.
 *
 *  @deprecated This function has been superceded by Memory_alloc() and will
 *              be removed in a future release.  Users are recommended to
 *              modify their applications to use the new, more flexible
 *              Memory_alloc() instead.
 *
 *  @param[in]  size    Size of the buffer to allocate.
 *  @param[in]  align   Alignment of the buffer; must be divisible by a power
 *                      of two.
 *
 *  @pre        @c align must be divisible by a power of two.
 *
 *  @retval     non-NULL Address of a physically contiguous buffer.
 *  @retval     NULL    Unable to obtain the requested buffer.
 *
 *  @remarks    This is commonly called by an application wishing to obtain
 *              a physically contiguous buffer which it must share with
 *              another processor.
 *
 *  @remarks    For portability reasons, applications commonly use
 *              this API even in environments which do not have virtual memory
 *              or an MMU (e.g. a single processor, DSP/BIOS based system).
 *              Doing so makes them portable to environments which <i>do</i>
 *              have to provide physically contiguous memory to remote
 *              processors.
 *
 *  @sa         Memory_alloc()
 *  @sa         Memory_contigFree()
 */
extern Ptr Memory_contigAlloc(UInt size, UInt align);


/*
 *  ======== Memory_contigFree ========
 */
/**
 *  @brief      Free memory allocated by Memory_contigAlloc()
 *
 *  @param[in]  addr    Address of a buffer allocated by Memory_contigAlloc()
 *  @param[in]  size    Size of the buffer to free.
 *
 *  @retval     TRUE    The buffer was freed and the memory pointed to by
 *                      @c addr is no longer valid.
 *  @retval     FALSE   The buffer couldn't be freed.
 *
 *  @pre        @c addr must be a valid address returned by
 *              Memory_contigAlloc()
 *
 *  @pre        @c size must be equivalent to the @c size passed in during the
 *              Memory_contigAlloc() allocation.
 *
 *  @sa         Memory_contigAlloc()
 */
extern Bool Memory_contigFree(Ptr addr, UInt size);


/** @cond INTERNAL */

/*
 *  ======== Memory_contigStat ========
 */
/**
 *  @brief      Obtain the memory usage statistics of the contiguous
 *              memory allocator.
 *
 *  @privateFxn
 *
 *  @param[out] statbuf Buffer to fill with statistics data.
 *
 *  @retval     TRUE    The statistics were captured, and @c statbuf has been
 *                      filled.
 *  @retval     FALSE   The statistics could not be obtained.
 *
 *  @pre        @c statbuf must be a pointer to memory of size
 *              <tt>sizeof(#Memory_Stat)</tt>.
 *
 *  @sa         Memory_contigAlloc()
 *  @sa         Memory_contigFree()
 */
extern Bool Memory_contigStat(Memory_Stat *statbuf);

/** @endcond  */


/*
 *  ======== Memory_free ========
 */
/**
 *  @brief      Free memory allocated with Memory_alloc().
 *
 *  @param[in]  addr    Address of a buffer allocated by Memory_alloc().
 *  @param[in]  size    Size of the buffer to free.
 *  @param[in]  params  Parameters controlling the free operation.
 *
 *  @retval     TRUE    The buffer was freed and the memory pointed to by
 *                      @c addr is no longer valid.
 *  @retval     FALSE   The buffer couldn't be freed.
 *
 *  @pre        @c addr must be a valid address returned by
 *              Memory_alloc().
 *
 *  @pre        @c size must be equivalent to the @c size passed in during the
 *              Memory_alloc() allocation.
 *
 *  @sa         Memory_alloc()
 */
extern Bool Memory_free(Ptr addr, UInt size, Memory_AllocParams *params);


/*
 *  ======== Memory_dumpKnownContigBufs ========
 */
/**
 *  @brief      Dumps the list of all translated/registered bufs.
 *
 *  @remarks    The list is printed using the tracing infrastructure at
 *              trace level 5 to tracemask #Memory_GTNAME.
 *
 *  @remarks    There are several mechanisms to enable this trace mask, one
 *              would be to do the following from your application:
 *  @code
 *    GT_set(Memory_GTNAME "+5");
 *  @endcode
 *
 *  @sa         Memory_registerContigBuf()
 *  @sa         Memory_unregisterContigBuf()
 */
extern Void Memory_dumpKnownContigBufsList(Void);


/*
 *  ======== Memory_getBufferPhysicalAddress ========
 */
/**
 *  @brief      Converts application virtual address to a physical address.
 *
 *  This API also checks verifies that the buffer is really contiguous.
 *
 *  @param[in]  virtualAddress  Address of a buffer.
 *  @param[in]  sizeInBytes     Size of the buffer.
 *  @param[out] isContiguous    Optional flag indicating whether the buffer
 *                              was physically contiguous or not.
 *
 *  @retval     0               Failure, the physical address could not
 *                              be obtained.
 *  @retval     non-zero        The physical address of the buffer.
 *
 *  @remarks    @c isContiguous is an optional parameter, and can be NULL if
 *              the caller doesn't want the results of this check.
 *              If @c isContiguous is NULL but the buffer is not contiguous,
 *              error trace will be generated.
 *
 *  @remarks    If a physically discontiguous buffer is provided in
 *              @c virtualAddress, zero will be returned.  And if
 *              @c isContiguous is non-null, it will be set to FALSE.
 *
 *  @remarks    This is typically called by a stub implementation to
 *              translate an application-side virtual address into a physical
 *              address usable by a remote skeleton and algorithm.
 *
 *  @remarks    To enable portable code, this is safe to call on systems
 *              without virtual memory.  In those cases, the returned
 *              physical buffer will be the same as the provided
 *              "virtual" buffer.
 *
 *  @sa         Memory_getBufferVirtualAddress()
 */
extern UInt32 Memory_getBufferPhysicalAddress(Ptr virtualAddress,
    Int sizeInBytes, Bool *isContiguous);


/** @cond INTERNAL */

#ifdef ti_sdo_ce_osal_Memory_USEDEPRECATEDAPIS

/*
 *  ======== Memory_getPhysicalAddress ========
 *  Convert user virtual address to physical address
 *  (returns the exact same value everywhere other than on Linux)
 *
 *  This function is deprecated -- everyone should be calling 
 *  Memory_getBufferPhysicalAddress() instead.
 */
static inline UInt32 Memory_getPhysicalAddress(Ptr virtualAddress)
{
    return(Memory_getBufferPhysicalAddress(virtualAddress, 4, NULL));
}

#endif

/** @endcond  */


/*
 *  ======== Memory_getBufferVirtualAddress ========
 */
/**
 *  @brief      Obtains the virtual address of a physically contiguous
 *              buffer.
 *
 *  @param[in]  physicalAddress Physical address of a buffer.
 *  @param[in]  sizeInBytes     Size of the buffer.
 *
 *  @retval     NULL            Failure, the virtual address could not
 *                              be obtained.
 *  @retval     non-zero        The virtual address of the buffer.
 *
 *  @remarks    If @c virtualAddress, was not acquired by
 *              Memory_getBufferPhysicalAddress(), no attempt is made to map the
 *              physically contiguous buffer into a the application's
 *              virtual memory space.
 *
 *  @remarks    This is typically called by a stub implementation to
 *              translate a buffer provided by a remote skeleton and/or
 *              algorithm into an application-usable, virtual address.
 *
 *  @remarks    To enable portable code, this is safe to call on systems
 *              without virtual memory.  In those cases, the returned
 *              "virtual" buffer will be the same as the provided
 *              physical buffer.
 *
 *  @sa         Memory_getBufferPhysicalAddress()
 */
extern Ptr Memory_getBufferVirtualAddress(UInt32 physicalAddress,
    Int sizeInBytes);

/** @cond INTERNAL */

/*
 *  ======== Memory_init ========
 */
extern Bool Memory_init(Void);


/*
 *  ======== Memory_exit ========
 */
extern Void Memory_exit(Void);


/*
 *  ======== Memory_redefine ========
 */
/**
 *  @brief Redefine the base and heap of a memory segment.
 *
 *  @privateFxn
 *
 *  @param[in]  segId   Segment ID of memory segment to redefine.
 *  @param[in]  base    New base address of memory segment.
 *  @param[in]  size    New size of memory segment.
 *
 *  @pre        @c base is aligned on an 8-byte boundary.
 *
 *  @retval     TRUE    Success
 *  @retval     FALSE   Failed to redefine heap base and size because either
 *                      @c segId was not a valid memory segment, or there is
 *                      memory currently allocated in the heap.
 */
extern Bool Memory_redefine(Int segId, Uint32 base, Uint32 size);

/** @endcond */

/*
 *  ======== Memory_registerContigBuf ========
 */
/**
 *  @brief      Register a physical buffer allocated without
 *              Memory_contigAlloc()
 *
 *  @param[in]  virtualAddress   Address of the buffer mapped into the
 *                               process space
 *  @param[in]  sizeInBytes      Size of the region
 *  @param[in]  physicalAddress  Physical address of the buffer
 *
 *  @remarks    A cache of "app-address to codec-address" mappings (e.g. virtual
 *              to physical address mappings in DM644x devices) is
 *              internally maintained in some environments (e.g. Linux).
 *              This is used, for example, by Memory_getBufferPhysicalAddress()
 *              and Memory_getBufferVirtualAddress().
 *              This lookup map is automatically updated
 *              when using Memory_contigAlloc() and Memory_contigFree().
 *              However, if the user acquires buffers independently, it must
 *              use Memory_registerContigBuf() and Memory_unregisterContigBuf()
 *              to ensure the lookup map is current.
 *
 *  @remarks    Individual sub-blocks of a buffer need not be
 *              registered; registering the entire buffer once will suffice.
 *
 *  @remarks    This API is typically only required for environments with
 *              virtual memory (e.g. Linux-based systems).
 *
 *  @sa         Memory_unregisterContigBuf()
 *  @sa         Memory_dumpKnownContigBufsList()
 */
extern Void Memory_registerContigBuf(UInt32 virtualAddress, UInt32 sizeInBytes,
    UInt32 physicalAddress);

/** @cond INTERNAL */

/*
 *  ======== Memory_segAlloc ========
 */
/**
 *  @brief      Allocate memory from a specific segment.
 *
 *  @privateFxn
 *
 *  @param[in]  segId   Segment ID to allocate the buffer from.
 *  @param[in]  size    Size of the buffer to allocate.
 *  @param[in]  align   Alignment of the buffer, must be divisible by a power
 *                      of two.
 *
 *  @retval     non-NULL Address of a physically contiguous buffer.
 *  @retval     NULL    Unable to obtain the requested buffer.
 *
 *  @sa         Memory_segFree()
 *  @sa         Memory_segStat()
 *  @sa         Memory_alloc()
 *  @sa         Memory_contigAlloc()
 */
extern Ptr Memory_segAlloc(Int segId, UInt size, UInt align);


/*
 *  ======== Memory_segFree ========
 */
/**
 *  @brief      Free memory allocated with Memory_segAlloc().
 *
 *  @privateFxn
 *
 *  @param[in]  segId   Segment the buffer to free was allocated from.
 *  @param[in]  addr    Address of a buffer allocated by Memory_segAlloc().
 *  @param[in]  size    Size of the buffer to free.
 *
 *  @retval     TRUE    The buffer was freed and the memory pointed to by
 *                      @c addr is no longer valid.
 *  @retval     FALSE   The buffer couldn't be freed.
 *
 *  @pre        @c segId must be equivalent to the @c segid passed in during the
 *              Memory_segAlloc() allocation.
 *
 *  @pre        @c addr must be a valid address returned by
 *              Memory_segAlloc().
 *
 *  @pre        @c size must be equivalent to the @c size passed in during the
 *              Memory_segAlloc() allocation.
 *
 *  @sa         Memory_segAlloc()
 *  @sa         Memory_segStat()
 */
extern Bool Memory_segFree(Int segId, Ptr addr, UInt size);


/*
 *  ======== Memory_segStat ========
 */
/**
 *  @brief      Obtain the memory usage statistics of a given memory segment
 *              allocator.
 *
 *  @privateFxn
 *
 *  @param[in]  segId   Segment ID to obtain statistics information for.
 *  @param[out] statbuf Buffer to fill with statistics data.
 *
 *  @retval     TRUE    The statistics were captured, and @c statbuf has been
 *                      filled.
 *  @retval     FALSE   The statistics could not be obtained.
 *
 *  @pre        @c statbuf must be a pointer to memory of size
 *              <tt>sizeof(#Memory_Stat)</tt>.
 *
 *  @sa         Memory_segAlloc()
 *  @sa         Memory_segFree()
 */
extern Bool Memory_segStat(Int segId, Memory_Stat *statbuf);

/** @endcond */

/*
 *  ======== Memory_unregisterContigBuf ========
 */
/**
 *  @brief      Unregisters a physical buffer allocated without
 *              Memory_contigAlloc().
 *
 *  @param[in]  virtualAddress   beginning address of the buffer mapped into the
 *                               process space
 *  @param[in]  sizeInBytes      size of the region
 *
 *  @remarks    This API <b>must</b> be used to unregister a buffer allocated
 *              outside of Memory_contigAlloc() if the buffer (or a portion
 *              of it) is passed on to VISA calls.  Segments of the buffer
 *              need not be individually unregistered.
 *
 *  @sa         Memory_registerContigBuf()
 *  @sa         Memory_dumpKnownContigBufsList()
 */
extern Void Memory_unregisterContigBuf(UInt32 virtualAddress,
    UInt32 sizeInBytes);


/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 1,267; 1-14-2008 09:55:33; /db/atree/library/trees/ce-g30x/src/
 */

