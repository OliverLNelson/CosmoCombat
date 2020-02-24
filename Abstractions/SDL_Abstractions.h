//combine all the headers in Abstractions/ to easily include in the correct order

#pragma once
#ifdef __linux__

#endif
#define SDL_MAIN_HANDLED //prevents interfearence from SDL_Main

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "SDL.h"
//#include "SDL_main.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_thread.h"
#include <time.h>
#include <algorithm>
#include <cmath>
using namespace std;
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")
#include "Misc.h"
#include "TextureHandling.cpp"//Specific operations needed to deal with textures (multithreading, re-buffering, queueing, etc...)
using namespace TextureHandling;
TextureHandler textureHandler = TextureHandler();


#include "Colors.h"
#include "Geometry.h"
#include "Images.h"
#include "Text.h"
#include "SDL_GUI.h"
#include "video.h"
