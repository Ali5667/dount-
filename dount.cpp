#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h> // Required for usleep() to control animation speed

int main() {
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];
    
    // Clear screen using ANSI escape code
    printf("\x1b[2J");
    
    for (;;) {
        // Clear text buffer (fill with spaces)
        memset(b, 32, sizeof(b));
        // Clear depth buffer (fill with zeros)
        memset(z, 0, sizeof(z));
        
        // Render loop for the 3D donut
        for (j = 0; j < 6.28; j += 0.07) {
            for (i = 0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;

                // 3D to 2D Projecting coordinates (X and Y)
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y = 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                
                // Calculate luminance (lighting intensity)
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

                // Check bounds and Z-buffer occlusion
                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        // Move cursor to top-left corner to redraw smoothly
        printf("\x1b[H");
        
        // Render the frame to terminal
        for (k = 0; k < 1760; k++) {
            putchar(k % 80 ? b[k] : '\n');
        }

        // Increment angles to animate rotation
        A += 0.04;
        B += 0.02;
        
        // Frame rate control: 30ms delay prevents frame tearing/warping
        usleep(30000); 
    }
    return 0;
}
