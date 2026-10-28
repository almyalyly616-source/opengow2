# OpenGOW2: God of War II Native Android Engine (WIP)

A custom native engine project for running **God of War II (PS2)** on Android devices natively without emulation overhead, developed using reverse engineering concepts.

## ⚠️ Legal Disclaimer
This repository **DOES NOT** contain any copyrighted game assets, ISOs, or proprietary Sony code. This is an open-source educational game engine project. To use this port, the end-user must provide their own legally obtained `gow2.iso` file.

## 🛠️ Current Status
- [x] Android 15 storage restrictions bypass (Scoped Storage Workaround).
- [x] ISO Header Validation & Sector 16 analysis.
- [x] PS2 Game ID Detection (`SCUS_974.81` NTSC-U).
- [x] Core ELF Executable extraction functionality (`GOW2_EXECUTABLE.ELF` successfully extracted).
- [ ] C++ Native Engine & Vulkan/OpenGL ES Graphics Layer Renderer (Next Step).

## 🚀 How to Run the Extractor
1. Place your legal `gow2.iso` inside your phone's **Download** folder.
2. Grant Termux "All Files Access" permission in Android settings.
3. Run the extractor tool:
   ```bash
   python extractor.py
   ```

**Developer:** [almyalyly616-source](https://github.com)
