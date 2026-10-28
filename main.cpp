#include <iostream>
#include <SDL2/SDL.h>
#include "elf_parser.h"
#include "renderer.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* argv[]) {
    std::cout << "--- OpenGOW2 Native C++ Engine Initialized ---" << std::endl;

    // 1. تشغيل محلل الـ ELF وقراءة البيانات النواتية للعبة
    std::string elf_file_path = "GOW2_EXECUTABLE.ELF";
    GOW2ElfParser::parseELF(elf_file_path);

    // 2. تهيئة مكتبة الرسوميات (SDL2)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "❌ SDL Could not initialize! Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    // 3. إنشاء نافذة اللعبة المخصصة للهاتف
    SDL_Window* window = SDL_CreateWindow(
        "OpenGOW2 Engine", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP
    );

    if (!window) {
        std::cerr << "❌ Game Window could not be created! Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // 4. تشغيل محرك الرسوميات (OpenGL ES 2.0)
    GOW2Renderer renderer;
    if (!renderer.initGraphics(window)) {
        std::cerr << "❌ Failed to initialize Graphics Renderer!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // دورة اللعبة الحقيقية (Game Loop) لتردد الفريمات
    bool isRunning = true;
    SDL_Event event;
    Uint32 startTime = SDL_GetTicks();

    while (isRunning) {
        // فحص مدخلات المستخدم أو أزرار التحكم
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        
        // مسح الشاشة وتلوينها بالخلفية الداكنة للعبة (60 فريم في الثانية)
        renderer.clearScreen();
        
        // تحديث وعرض الفريمات على شاشة الهاتف
        SDL_GL_SwapWindow(window);

        // إغلاق تلقائي بعد 5 ثوانٍ في هذا الطور التجريبي
        if (SDL_GetTicks() - startTime > 5000) {
            isRunning = false;
        }
    }

    // 5. إغلاق وتنظيف الذاكرة بالكامل عند الخروج
    renderer.shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
