#include "../include/cub3d.h"

void draw_vertical_line(void *mlx, void *win, int x, int y_start, int y_end, int color)
{
    int y = y_start;
    while (y <= y_end)
    {
        mlx_pixel_put(mlx, win, x, y, color);
        y++;
    }
}

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 480, "Cub3D simple vertical lines");
    for (int x = 5; x < 15; x++)
    {
        int wall_height = 20 + x * 20;
        int y_start = (480 - wall_height) / 2;
        int y_end = y_start + wall_height;
        draw_vertical_line(mlx, win, 30 * x, y_start, y_end, 0x00FF00);
    }

    mlx_loop(mlx);
    return 0;
}
