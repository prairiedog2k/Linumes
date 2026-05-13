#include "framework/OpenGLHeaders.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

#include "MediaManager.h"
#include "MediaConfigurationTypes.h"
#include "ScreenDimensions.h"

int          MediaManager::screenheight = 0;
int          MediaManager::screenwidth  = 0;
SDL_Window*  MediaManager::_window      = nullptr;

MediaManager::MediaManager(int width, int height, int bpp)
    : screenbpp(bpp), _fullscreen(false), glContext(nullptr), joystick(nullptr)
{
    MediaManager::screenheight = height;
    MediaManager::screenwidth  = width;
}

MediaManager::MediaManager(Configuration configuration)
    : screenbpp(0), _fullscreen(false), glContext(nullptr), joystick(nullptr)
{
    int h = std::atoi(configuration.getValue(MEDIA_SCREEN_HEIGHT).c_str());
    int w = std::atoi(configuration.getValue(MEDIA_SCREEN_WIDTH).c_str());
    int b = std::atoi(configuration.getValue(MEDIA_SCREEN_BPP).c_str());
    MediaManager::screenheight = (h > 0) ? h : SCREEN_DIM_H;
    MediaManager::screenwidth  = (w > 0) ? w : SCREEN_DIM_W;
    screenbpp = (b > 0) ? b : SCREEN_DIM_BPP;
}

MediaManager::~MediaManager() {
    release();
}

void MediaManager::initSDL()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
}

void MediaManager::initAudio()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) == -1) {
        std::cerr << "Mix_OpenAudio: " << Mix_GetError() << std::endl;
        SDL_Quit();
    }
    Mix_AllocateChannels(16);
    Mix_Volume(1, MIX_MAX_VOLUME / 2);
    for (int chan = 2; chan < 16; chan++)
        Mix_Volume(chan, MIX_MAX_VOLUME);
}

void MediaManager::initGraphics()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    _window = SDL_CreateWindow(
        "Linumes - 2008",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenwidth, screenheight,
        flags);

    if (!_window) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    glContext = SDL_GL_CreateContext(_window);
    if (!glContext) {
        std::cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    SDL_GL_SetSwapInterval(1);
}

void MediaManager::resizeWindow(int width, int height)
{
    if (height == 0) height = 1;
    GLfloat ratio = (GLfloat)width / (GLfloat)height;

    glViewport(0, 0, (GLint)width, (GLint)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool MediaManager::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    return true;
}

void MediaManager::initCursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

void MediaManager::initJoyStick()
{
    joystick = nullptr;
    int numJoy = SDL_NumJoysticks();
    if (numJoy > 0) {
#ifdef DEBUG
        printf("There %s %d Joystick%s Attached to the Computer\n",
               (numJoy > 1 ? "are" : "is"), numJoy, (numJoy > 1 ? "s" : ""));
#endif
        joystick = SDL_JoystickOpen(numJoy - 1);
        if (joystick) {
#ifdef DEBUG
            printf("\tUsing Joystick %s\n", SDL_JoystickNameForIndex(numJoy - 1));
#endif
            SDL_JoystickEventState(SDL_ENABLE);
        }
    }
}

void MediaManager::initFont()
{
    TTF_Init();
}

bool MediaManager::init()
{
#ifdef MING_RANDOM
    srand((unsigned int)time(nullptr));
#else
    srand((unsigned int)time(nullptr));
#endif
    initSDL();
    initAudio();
    initGraphics();
    initFont();
    initGL();
    resizeWindow(screenwidth, screenheight);
    return true;
}

void MediaManager::release()
{
    if (!_window && glContext == nullptr) return; // already released
    Mix_CloseAudio();
    TTF_Quit();
    if (glContext) {
        SDL_GL_DeleteContext(glContext);
        glContext = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    SDL_Quit();
}

void MediaManager::toggleFullScreen()
{
    _fullscreen = !_fullscreen;
    SDL_SetWindowFullscreen(_window, _fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

bool MediaManager::resizeScreenTo(int w, int h)
{
    screenwidth  = w;
    screenheight = h;
    SDL_SetWindowSize(_window, w, h);
    resizeWindow(w, h);
    return true;
}

void MediaManager::takeScreenShot()
{
    static int screenshotCounter = 0;
    int screenWidth  = screenwidth;
    int screenHeight = screenheight;

    char screenshotName[64];
    sprintf(screenshotName, "screenshot%02d.bmp", screenshotCounter++);

    Uint32 rmask, gmask, bmask, amask = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff0000;
    gmask = 0x00ff00;
    bmask = 0x0000ff;
#else
    rmask = 0x0000ff;
    gmask = 0x00ff00;
    bmask = 0xff0000;
#endif
    SDL_Surface *image = SDL_CreateRGBSurface(0, screenWidth, screenHeight, 24, rmask, gmask, bmask, amask);
    SDL_Surface *temp  = SDL_CreateRGBSurface(0, screenWidth, screenHeight, 24, rmask, gmask, bmask, amask);
    if (!image || !temp) return;

    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, screenWidth, screenHeight, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    for (int i = 0; i < screenHeight; i++)
        memcpy((char *)temp->pixels + 3 * screenWidth * i,
               (char *)image->pixels + 3 * screenWidth * (screenHeight - i - 1),
               3 * screenWidth);

    SDL_SaveBMP(temp, screenshotName);
    SDL_FreeSurface(image);
    SDL_FreeSurface(temp);
}
