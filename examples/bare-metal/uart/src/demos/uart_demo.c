// Copyright 2022 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

/* System headers */
#include <platform.h>
#include <xs1.h>

/* SDK headers */
#include "soc.h"
#include "xcore_utils.h"
#include "uart.h"

/* App headers */
#include "app_conf.h"
#include "app_demos.h"

void uart_demo(uart_tx_device_t* device_ctx)
{
    uint32_t in_buf = 0;
    uint32_t out_buf = 0;

    // spi_master_start_transaction(device_ctx);
    // spi_master_transfer(device_ctx,
    //                     (uint8_t *)&out_buf,
    //                     (uint8_t *)&in_buf,
    //                     4);
    // spi_master_end_transaction(device_ctx);

    debug_printf("uart got 0x%x\n", out_buf);
    exit(0);
}
