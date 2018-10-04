#include "raylib.h"
#include <stdlib.h>


class Checker {
    public:
        Checker() {
            // TODO: Make the checker fit the window size.
            const int width = 1024;
            const int height = 1024;

            // Dynamic memory allocation to store pixels data (Color type)
            Color *pixels = (Color *)malloc(width*height*sizeof(Color));

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    if (((x/32+y/32)/1)%2 == 0) pixels[y*height + x] = DARKGRAY;
                    else pixels[y*height + x] = BLACK;
                }
            }

            // Load pixels data into an image structure and create texture
            Image checkedIm = LoadImageEx(pixels, width, height);
            m_checked = LoadTextureFromImage(checkedIm);
            UnloadImage(checkedIm);     // Unload CPU (RAM) image data

            // Dynamic memory must be freed after using it
            free(pixels);               // Unload CPU (RAM) pixels data
        }
        ~Checker() {
            UnloadTexture(m_checked);
        }
        void update() {
            DrawTexture(m_checked, GetScreenWidth()/2 - m_checked.width/2, GetScreenHeight()/2 - m_checked.height/2, Fade(WHITE, 0.5f));
        }
    private:
        int m_width;
        int m_height;
        Texture2D m_checked;
};
