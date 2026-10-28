#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h> // مكتبة الرسوميات الرسمية للهواتف

class GOW2Renderer {
private:
    SDL_GLContext glContext;

public:
    // دالة تهيئة كرت الشاشة وضبط بيئة الـ OpenGL ES
    bool initGraphics(SDL_Window* window) {
        // ضبط إعدادات الرسوميات لتعمل بنظام OpenGL ES 2.0 المخصص للهواتف
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        // إنشاء سياق الرسم (Graphics Context)
        glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            std::cerr << "❌ OpenGL ES Context could not be created! Error: " << SDL_GetError() << std::endl;
            return false;
        }

        std::cout << "🚀 [GRAPHICS PASSED] OpenGL ES 2.0 Renderer Initialized successfully!" << std::endl;
        
        // تفعيل محرك مزامنة الشاشة الثابتة (V-Sync) لمنع تقطيع الصور وتثبيت الـ 60 فريم
        SDL_GL_SetSwapInterval(1); 
        return true;
    }

    // دالة تنظيف شاشة اللعبة ورسم الألوان (تحديث كل فريم)
    void clearScreen() {
        // تلوين الخلفية باللون الأسود الداكن الخاص ببدايات ألعاب God of War
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // دالة إغلاق وتنظيف ذاكرة كرت الشاشة
    void shutdown() {
        if (glContext) {
            SDL_GL_DeleteContext(glContext);
            std::cout << "🗑️ Graphics Renderer Cleaned up from Memory." << std::endl;
        }
    }
};

#endif // RENDERER_H
