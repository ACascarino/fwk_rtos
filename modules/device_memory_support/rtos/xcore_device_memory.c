// Copyright 2021 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include "xcore_device_memory.h"

#include <stddef.h>
#include <string.h>

#include <xcore/assert.h>
#include <xcore/port.h>
//#include <xcore/hwtimer.h>

#define WORDS_TO_BYTES(w) ((w) * sizeof(uint32_t))
#define BYTES_TO_WORDS(b) (((b) + sizeof(uint32_t) - 1) / sizeof(uint32_t))

#define WORD_TO_BYTE_ADDRESS(w) WORDS_TO_BYTES(w)
#define BYTE_TO_WORD_ADDRESS(b) ((b) / sizeof(uint32_t))

#if USE_SWMEM
#include <xcore/swmem_fill.h>

#include "rtos/drivers/qspi_flash/api/rtos_qspi_flash.h"
#include "rtos/drivers/swmem/api/rtos_swmem.h"

static rtos_qspi_flash_t *qspi_flash_ctx = NULL;

// void rtos_swmem_read_request(unsigned offset, uint32_t *buf)
// {
//     if (qspi_flash_ctx != NULL) {
//         rtos_qspi_flash_read(qspi_flash_ctx, (uint8_t *)buf, (unsigned)offset,
//                              WORDS_TO_BYTES(SWMEM_FILL_SIZE_WORDS));
//     }
// }

bool rtos_swmem_read_request_isr(unsigned offset, uint32_t *buf)
{
    if (qspi_flash_ctx != NULL) {
        qspi_flash_read(&qspi_flash_ctx->ctx, (uint8_t *)buf, (unsigned)offset,
                        WORDS_TO_BYTES(SWMEM_FILL_SIZE_WORDS));
    }
    return true;
}

void swmem_setup(rtos_qspi_flash_t *ctx, unsigned swmem_task_priority)
{
    qspi_flash_ctx = ctx;
    rtos_swmem_init(RTOS_SWMEM_READ_FLAG);
    rtos_swmem_start(swmem_task_priority);
}

size_t swmem_load(void *dest, const void *src, size_t size)
{
    xassert(IS_SWMEM(src));

    if (qspi_flash_ctx != NULL) {
        // rtos_printf(
        //         "BEFORE rtos_qspi_flash_read   dest=0x%x    src=0x%x    size=%d\n",
        //         dest, src, size);
        // uint32_t tic = get_reference_time();

        rtos_qspi_flash_read(qspi_flash_ctx, (uint8_t *)dest,
                             (unsigned)(src - XS1_SWMEM_BASE), size);
        // rtos_printf("AFTER rtos_qspi_flash_read   size=%d      duration=%lu\n",
        //             size,
        //             (get_reference_time() - tic) / PLATFORM_REFERENCE_MHZ);
        return size;
    }
    return 0;
}

#endif /* USE_SWMEM */
