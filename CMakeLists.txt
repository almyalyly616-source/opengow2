cmake_minimum_required(VERSION 3.10)
project(OpenGOW2Engine CXX)

set(CMAKE_CXX_STANDARD 17)

# البحث عن مكتبات الرسوميات المطلوبة في النظام (SDL2 و OpenGL)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# تحديد الملفات المصدرية للمحرك (الملف الرئيسي والمكونات)
add_executable(opengow2_engine main.cpp)

# ربط المحرك ومستندات كرت الشاشة بمكتبات الرسوميات
target_link_libraries(opengow2_engine PRIVATE SDL2::SDL2 OpenGL::GL)
