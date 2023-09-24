#include <rp6502.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include <fcntl.h>


void main()
{
    int i, fd;
    typedef struct
    {
        bool x_wrap;
        bool y_wrap;
        int16_t x_pos_px;
        int16_t y_pos_px;
        int16_t width_px;
        int16_t height_px;
        uint16_t xram_data_ptr;
        uint16_t xram_palette_ptr;
    } mode3_config_t;
    mode3_config_t config = {};
    config.x_wrap = false;
    config.x_pos_px = 0;
    config.y_pos_px = 0;
    config.width_px = 320;
    config.height_px = 180;
    config.xram_data_ptr = 0x0200;
    config.xram_palette_ptr = 0x0000;
    RIA.addr0 = 0xFF00;
    RIA.step0 = 1;
    for (i = 0; i < sizeof(mode3_config_t); i++)
        RIA.rw0 = ((uint8_t *)&config)[i];

    i = ria_xreg(1, 0, 0, 2);
    printf("canvas=%d\n", i);
    i = ria_xreg(1, 0, 1, 3, 0xFF00, 2);
    printf("mode_3=%d\n", i);
    i = ria_xreg(1, 0, 1, 0, 2);
    printf("mode_0=%d\n", i);

    fd = open("kodim23_320.bin", O_RDONLY);
    if (fd < 0)
    {
        puts("file error");
        exit(1);
    }
    read_xram(0x0000, 0x6000, fd);
    read_xram(0x6000, 0x6000, fd);
    read_xram(0xC000, 0x2300, fd);
    close(fd);

    while (1)
    {
    }
}
