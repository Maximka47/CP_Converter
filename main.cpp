#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

//CLEAR FUNCTION
void clear(char fill = ' ') {
    COORD tl = { 0,0 };
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
};

float r, g, b, c, m, y, k, h, s, v, f, t;


// RGB to CMYK conversion
void rgbToCmyk(float R, float G, float B, float& C, float& M, float& Y, float& K) {

    K = std::min(1.0f - R, std::min(1.0f - G, 1.0f - B));
    C = (1.0f - R - K) / (1.0f - K);
    M = (1.0f - G - K) / (1.0f - K);
    Y = (1.0f - B - K) / (1.0f - K);

}

// CMYK to RGB conversion
void cmykToRgb(float C, float M, float Y, float K, float& R, float& G, float& B) {
    R = 1.0f - std::min(1.0f, C * (1.0f - K) + K);
    G = 1.0f - std::min(1.0f, M * (1.0f - K) + K);
    B = 1.0f - std::min(1.0f, Y * (1.0f - K) + K);
}

// RGB to HSV conversion
void rgbToHsv(float R, float G, float B, float& H, float& S, float& V) {
    float maxColor = std::max(std::max(R, G), B);
    float minColor = std::min(std::min(R, G), B);
    float delta = maxColor - minColor;

    V = maxColor;

    if (maxColor != 0)
        S = delta / maxColor;
    else {
        S = 0;
        H = -1;
        return;
    }

    if (R == maxColor)
        H = (G - B) / delta;
    else if (G == maxColor)
        H = 2 + (B - R) / delta;
    else
        H = 4 + (R - G) / delta;

    H *= 60;
    if (H < 0)
        H += 360;
}

// HSV to RGB conversion
void hsvToRgb(float H, float S, float V, float& R, float& G, float& B) {
    if (S == 0) {
        R = G = B = V;
        return;
    }

    H /= 60;
    int i = static_cast<int>(H);
    float f = H - i;
    float p = V * (1 - S);
    float q = V * (1 - S * f);
    float t = V * (1 - S * (1 - f));

    switch (i) {
        case 0: R = V; G = t; B = p; break;
        case 1: R = q; G = V; B = p; break;
        case 2: R = p; G = V; B = t; break;
        case 3: R = p; G = q; B = V; break;
        case 4: R = t; G = p; B = V; break;
        case 5: default: R = V; G = p; B = q; break;
    }
}

int main() {

    clear();

    std::cout << "\n1. RGB\n";
    std::cout << "2. CMYK\n";
    std::cout << "3. HSV\n\n";
    std::cout << "Enter a number of color palette to convert from: ";
    
    std::cin >> f;

    clear();

    std::cout << "\n1. RGB\n";
    std::cout << "2. CMYK\n";
    std::cout << "3. HSV\n\n";
    std::cout << "Enter a number of color palette to convert to: ";

    std::cin >> t;

    if (f==t){
        clear();
        std::cout << "Its the same palette!";
        Sleep(3000);
        main();
    }

    if (f==1){
        if (t==2){
            clear();
            std::cout << "\nRGB to CMYK\n";
            std::cout << "Enter the value of Red: ";
            std::cin >> r;
            clear();

            std::cout << "\nRGB to CMYK\n";
            std::cout << "Enter the value of Green: ";
            std::cin >> g;
            clear();

            std::cout << "\nRGB to CMYK\n";
            std::cout << "Enter the value of Blue: ";
            std::cin >> b;
            clear();

            rgbToCmyk(r, g, b, c, m, y, k);

            std::cout << "\nRGB to CMYK: " << c << ", " << m << ", " << y << ", " << k << std::endl;            

        }else if (t==3){

            clear();
            std::cout << "\nRGB to HSV\n";
            std::cout << "Enter the value of Red: ";
            std::cin >> r;
            clear();

            std::cout << "\nRGB to HSV\n";
            std::cout << "Enter the value of Green: ";
            std::cin >> g;
            clear();

            std::cout << "\nRGB to HSV\n";
            std::cout << "Enter the value of Blue: ";
            std::cin >> b;
            clear();

            rgbToHsv(r, g, b, h, s, v);
            std::cout << "\nRGB to HSV: " << h << ", " << s << ", " << v << std::endl;

        }else{
            std::cout << "Wrong number!";
            Sleep(3000);
            main();
        }

    }else if (f==2){
        if (t==1){
            clear();
            std::cout << "\nCMYK to RGB\n";
            std::cout << "Enter the value of Cyan: ";
            std::cin >> c;
            clear();

            std::cout << "\nCMYK to RGB\n";
            std::cout << "Enter the value of Magenta: ";
            std::cin >> m;
            clear();

            std::cout << "\nCMYK to RGB\n";
            std::cout << "Enter the value of Yellow: ";
            std::cin >> y;
            clear();

            std::cout << "\nCMYK to RGB\n";
            std::cout << "Enter the value of Black: ";
            std::cin >> k;
            clear();

            cmykToRgb(c, m, y, k, r, g, b);
            std::cout << "\nCMYK to RGB: " << r << ", " << g << ", " << b << std::endl;
        }else if(t==3){
            clear();
            std::cout << "\n\nCMYK to HSV\n";
            std::cout << "Enter the value of Cyan: ";
            std::cin >> c;
            clear();

            std::cout << "\n\nCMYK to HSV\n";
            std::cout << "Enter the value of Magenta: ";
            std::cin >> m;
            clear();

            std::cout << "\n\nCMYK to HSV\n";
            std::cout << "Enter the value of Yellow: ";
            std::cin >> y;
            clear();

            std::cout << "\n\nCMYK to HSV\n";
            std::cout << "Enter the value of Black: ";
            std::cin >> k;
            clear();

            cmykToRgb(c, m, y, k, r, g, b);
            rgbToHsv(r, g, b, h, s, v);
            std::cout << "\n\nCMYK to HSV: " << h << ", " << s << ", " << v << std::endl;
        }else{
            std::cout << "Wrong number!";
            Sleep(3000);
            main();
        }

    }else if(f==3){
        if(t==1){

            clear();
            std::cout << "\n\nHSV to RGB\n";
            std::cout << "Enter the value of Hue: ";
            std::cin >> h;
            clear();

            std::cout << "\n\nHSV to RGB\n";
            std::cout << "Enter the value of Saturation: ";
            std::cin >> s;
            clear();

            std::cout << "\n\nHSV to RGB\n";
            std::cout << "Enter the value of Volume: ";
            std::cin >> v;
            clear();

            hsvToRgb(h, s, v, r, g, b);
            std::cout << "\n\nHSV to RGB: " << r << ", " << g << ", " << b << std::endl;

        }else if(t==2){
            clear();
            std::cout << "\n\nHSV to CMYK\n";
            std::cout << "Enter the value of Hue: ";
            std::cin >> h;
            clear();

            std::cout << "\n\nHSV to CMYK\n";
            std::cout << "Enter the value of Saturation: ";
            std::cin >> s;
            clear();

            std::cout << "\n\nHSV to CMYK\n";
            std::cout << "Enter the value of Volume: ";
            std::cin >> v;
            clear();

            hsvToRgb(h, s, v, r, g, b);
            rgbToCmyk(r, g, b, c, m, y, k);
            std::cout << "HSV to CMYK: " << c << ", " << m << ", " << y << ", " << k << std::endl;
        }else{
            std::cout << "\n\nWrong number!";
            Sleep(3000);
            main();
        }
    }else{
        std::cout << "Wrong number!";
        Sleep(3000);
        main();
    }

    char ex;

    std::cin >> ex;

    return 0;
}


