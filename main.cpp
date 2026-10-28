#include <iostream>
#include <SDL2/SDL.h>
#include "elf_parser.h"

// أبعاد شاشة اللعبة الافتراضية لبورت الهاتف
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* argv[]) {
    std::cout << "--- OpenGOW2 Native C++ Engine Initialized ---" << std::endl;

    // 1. تشغيل محلل الـ ELF لقراءة نواة لعبة God of War 2
    std::string elf_file_path = "GOW2_EXECUTABLE.ELF";
    std::cout << "🎮 Loading Core Game Logic..." << std::endl;
    
    // استدعاء دالة الفحص الذكي لتفكيك وقراءة ملف الـ ELF المستخرج
    if (!GOW2ElfParser::parseELF(elf_file_path)) {
        std::cerr << "⚠️ Warning: Continuing engine initialization without core game logic for testing." << std::endl;
    }

    // 2. تهيئة مكتبة الرسوميات والمحرك الرسومي (SDL2)
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

    std::cout << "✅ Native Game Window Created Successfully!" << std::endl;

    // دورة اللعبة الافتراضية المؤقتة للاختبار
    bool isRunning = true;
    SDL_Event event;
    Uint32 startTime = SDL_GetTicks();

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }
        
        // إغلاق تلقائي بعد 5 ثوانٍ في هذه المرحلة التجريبية
        if (SDL_GetTicks() - startTime > 5000) {
            isRunning = false;
        }
    }

    // 4. إغلاق وتنظيف الذاكرة
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
