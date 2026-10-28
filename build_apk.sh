#!/bin/bash
echo "=================================================="
echo "---     OpenGOW2 APK Builder for Android       ---"
echo "=================================================="

# 1. تنظيف أي بناء قديم وإنشاء مجلدات حزمة الـ APK
echo "📁 Creating build directories..."
rm -rf build_apk opengow2.apk
mkdir -p build_apk/lib/arm64-v8a
mkdir -p build_apk/res/values

# 2. تجميع أكواد الـ C++ وتحويلها إلى مكتبة رسومية مشتركة (.so) تفهمها الهواتف
echo "⚡ Compiling C++ Native Engine (main.cpp)..."
clang++ -shared -fPIC -std=c++17 main.cpp \
    -lSDL2 -lGLESv2 -llog \
    -o build_apk/lib/arm64-v8a/libopengow2_engine.so

if [ $? -ne 0 ]; then
    echo "❌ Error: C++ Compilation failed!"
    exit 1
fi

# 3. إنشاء ملف القيم الأساسي للتطبيق
echo "📝 Generating resource strings..."
echo '<?xml version="1.0" encoding="utf-8"?><resources><string name="app_name">OpenGOW2 Engine</string></resources>' > build_apk/res/values/strings.xml

# 4. تجميع الحزمة وحزم ملف الـ AndroidManifest مع الملفات البرمجية
echo "📦 Packaging everything into APK..."
aapt package -f -M AndroidManifest.xml -S build_apk/res -I /system/framework/framework-res.apk -F opengow2.apk build_apk/

# 5. التوقيع الرقمي والأمني للتطبيق لكي يقبله نظام أندرويد 15 وتثبيته بأمان
echo "🔑 Generating debug security key and signing APK..."
keytool -genkey -v -keystore debug.keystore -storepass android -alias androiddebugkey -keypass android -keyalg RSA -keysize 2048 -validity 10000 -dname "CN=Android Debug,O=Android,C=US" 2>/dev/null

apksigner sign --ks debug.keystore --ks-pass pass:android --out opengow2_final.apk opengow2.apk

echo "=================================================="
echo "🎯 [SUCCESS] Your Native APK is Ready: 'opengow2_final.apk'"
echo "=================================================="
