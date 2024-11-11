#include "render.h"
#include <bitset>

const uint8_t smallLetterFont_8[3][16] = {
    {0, 253, 39, 39, 254, 253, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // A

    {1, 254, 254, 146, 146, 255, 109, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // B

    {1, 56, 124, 198, 130, 131, 131, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // C

};

void displayPrint(RGBA **displayBuffer, int width, int height)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if((int)displayBuffer[y][x].getRed() == 1) {
                std::cout<<"\033[31m" << (int)displayBuffer[y][x].getRed()<< "\033[0m" <<" ";
            }else if((int)displayBuffer[y][x].getGreen() == 1){
                std::cout<<"\033[32m" << (int)displayBuffer[y][x].getRed()<< "\033[0m" <<" ";
            }else if((int)displayBuffer[y][x].getBlue() == 1){
                std::cout<<"\033[34m" << (int)displayBuffer[y][x].getRed()<< "\033[0m" <<" ";
            }else if((int)displayBuffer[y][x].getAlpha() == 0){
                std::cout<<"\033[30m" << (int)displayBuffer[y][x].getRed()<< "\033[0m" <<" ";
            }else {
                std::cout<< (int)displayBuffer[y][x].getRed() <<" ";
            }
        }
        std::cout<<std::endl;
    }
}
int main()
{

    uint8_t DISPLAY_WIDTH = 80;
    uint8_t DISPLAY_HEIGHT = 30;

    RGBA **displayBuffer = new RGBA *[DISPLAY_HEIGHT];

    for (int i = 0; i < DISPLAY_HEIGHT; ++i)
    {
        displayBuffer[i] = new RGBA[DISPLAY_WIDTH];
    }

    RGBA color(1, 0, 0, 1);
    Canvas canvas = {10,10,50,20};
    Render rd(displayBuffer, DISPLAY_WIDTH, DISPLAY_HEIGHT,color,canvas,{0,0,0,0});

    // RGBA color1(2, 2, 2, 2);
    // Canvas canvas1 = {30,20,80,30};
    // Render rd1(displayBuffer, DISPLAY_WIDTH, DISPLAY_HEIGHT,color1,canvas1,{0,0,0,0});


    rd.textRenderer(smallLetterFont_8, "ABCABCABCABCABC",{1,0,0,1},{0,1,0,1});
    // rd1.textRenderer(smallLetterFont_8, "B");

    // // for (int i = -1; i < 10; i++)
    // // {
    // //        int x = rd.decodeVerticalLine(smallLetterFont_8[0],i);

    // //    std::bitset<32> binary(x);
    // //     std::cout << binary << std::endl;

    // // }

    // // displayBuffer[0][0] = RGBA(100,100,100,100);

    // Render rd3(displayBuffer,DISPLAY_WIDTH,DISPLAY_HEIGHT);
    // rd3.fillCanvas({9,9,9,9});
    // rd3.textRenderer(smallLetterFont_8,"ABC",{1,1,1,1},{0,0,0,0});
    
    displayPrint(displayBuffer,DISPLAY_WIDTH,DISPLAY_HEIGHT);
    
    // rd.eraseCanvas();
    // displayPrint(displayBuffer,DISPLAY_WIDTH,DISPLAY_HEIGHT);

    return 0;
}