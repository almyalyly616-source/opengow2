herecmake_minimum_required(VERSION 3.10)
project(OpenGOW2Engine CXX)

set(CMAKE_CXX_STANDARD 17)

# البحث عن مكتبة الرسوميات SDL2 في النظام
find_package(SDL2 REQUIRED)

# تحديد الملفات المصدرية للمحرك
add_executable(opengow2_engine main.cpp)

# ربط المحرك بمكتبة الرسوميات
target_link_libraries(opengow2_engine PRIVATE SDL2::SDL2)
