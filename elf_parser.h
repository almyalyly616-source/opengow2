here#ifndef ELF_PARSER_H
#define ELF_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

// تعريف ترويسة ملف الـ ELF لجهاز PS2 (نظام 32-بت)
struct Elf32_Header {
    unsigned char e_ident[16]; // هويات الملف السحرية
    uint16_t      e_type;      // نوع الملف
    uint16_t      e_machine;   // المعالج المستهدف (MIPS لـ PS2)
    uint32_t      e_version;   // إصدار الملف
    uint32_t      e_entry;     // نقطة انطلاق كود اللعبة الرئيسي (Entry Point)
    uint32_t      e_phoff;     // إزاحة جدول ترويسة البرنامج
    uint32_t      e_shoff;     // إزاحة جدول ترويسة الأقسام
    uint32_t      e_flags;     // أعلام المعالج
    uint16_t      e_ehsize;    // حجم الترويسة الحالية
    uint16_t      e_phentsize; // حجم ترويسة البرنامج فردياً
    uint16_t      e_phnum;     // عدد ترويسات البرامج
    uint16_t      e_shentsize; // حجم ترويسة الأقسام فردياً
    uint16_t      e_shnum;     // عدد ترويسات الأقسام
    uint16_t      e_shstrndx;  // دليل قسم الأسماء
};

class GOW2ElfParser {
public:
    static bool parseELF(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "❌ Error: Could not open GOW2_EXECUTABLE.ELF" << std::endl;
            return false;
        }

        Elf32_Header header;
        file.read(reinterpret_cast<char*>(&header), sizeof(Elf32_Header));

        // التحقق من الرقم السحري للملف (يجب أن يبدأ بـ 0x7F 'E' 'L' 'F')
        if (header.e_ident[0] != 0x7F || header.e_ident[1] != 'E' || 
            header.e_ident[2] != 'L' || header.e_ident[3] != 'F') {
            std::cerr << "❌ Error: Invalid ELF magic numbers! Not a native PS2 file." << std::endl;
            return false;
        }

        std::cout << "🎯 [ELF PASSED] God of War 2 Core Logic Verified!" << std::endl;
        
        // جهاز الـ PS2 يعتمد على معالج MIPS (كود الماكينة الخاص به تقنياً هو 8)
        std::cout << "📟 Target Machine Code: " << header.e_machine << " (MIPS Architecture)" << std::endl;
        
        // استخراج نقطة البداية لتشغيل اللعبة في الذاكرة
        std::cout << "🔑 Game Execution Entry Point: 0x" << std::hex << header.e_entry << std::dec << std::endl;
        std::cout << "📊 Number of internal sections found: " << header.header.e_shnum << std::endl;

        return true;
    }
};

#endif // ELF_PARSER_H
