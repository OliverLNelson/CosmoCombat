//combine all the headers in Abstractions/ to easily include in the correct order

#pragma once
#ifdef __linux__

#endif
#define SDL_MAIN_HANDLED //prevents interfearence from SDL_Main


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <chrono>
#include "SDL.h"
//#include "SDL_main.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_thread.h"
#include <time.h>
#include <random>
#include <algorithm>
#include <cmath>
#include <memory>
using namespace std;
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#include "TextureHandling.cpp"

using namespace TextureHandling;

#include "Misc.h"
#include "Misc.cpp"
#include "Colors.h"
#include "Geometry.h"
#include "Images.h"
#include "Text.h"
#include "SDL_GUI.h"
#include "video.h"
extern const char* clearLine = "\r"; //some escape sequences used to clear a line in the console
