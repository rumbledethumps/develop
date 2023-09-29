#include <rp6502.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <fcntl.h>

void main()
{
    int i, fd, x, y;
    uint8_t v;

    xram0_struct_set(0xFF00, vga_mode3_config_t, x_wrap, true);
    xram0_struct_set(0xFF00, vga_mode3_config_t, y_wrap, true);
    xram0_struct_set(0xFF00, vga_mode3_config_t, x_pos_px, 0);
    xram0_struct_set(0xFF00, vga_mode3_config_t, y_pos_px, 0);
    xram0_struct_set(0xFF00, vga_mode3_config_t, width_px, 320);
    xram0_struct_set(0xFF00, vga_mode3_config_t, height_px, 180);
    xram0_struct_set(0xFF00, vga_mode3_config_t, xram_data_ptr, 0x0200);
    xram0_struct_set(0xFF00, vga_mode3_config_t, xram_palette_ptr, 0x0000);

    i = xreg(1, 0, 0, 2);
    printf("canvas=%d\n", i);
    i = xreg(1, 0, 1, 3, 2, 0xFF00);
    printf("mode_3=%d\n", i);
    i = xreg(1, 0, 1, 0, 1);
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

    v = RIA.vsync;
    while (1)
    {
        if (RIA.vsync == v)
            continue;
        xram0_struct_set(0xFF00, vga_mode3_config_t, x_pos_px, x);
        xram0_struct_set(0xFF00, vga_mode3_config_t, y_pos_px, y);
        if (++x >= 320)
            x = -320;
        if (++y >= 180)
            y = -180;
        v = RIA.vsync;
    }
}
