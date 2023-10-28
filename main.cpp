#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "CubeCraft.h"

int main()
{
    try {
        cubecraft::Init();
        cubecraft::Loop();
        cubecraft::Quit();
    }
    catch (...) {
        return -1;
    }
    
    return 0;
}