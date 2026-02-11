# Development Environment Setup Guide

This guide will help you set up your development environment for the Embedded C/C++ course.

# link to this class repo
https://github.com/Anaga/embedded-course-2026


## Required Software

### 1. Visual Studio Code
- Download: https://code.visualstudio.com/
- Install with default settings
- Recommended for: Windows, macOS, Linux

### 2. PlatformIO Extension
**After installing VSCode:**
1. Open VSCode
2. Click Extensions icon (left sidebar) or press `Ctrl+Shift+X`
3. Search for "PlatformIO IDE"
4. Click Install
5. Reload VSCode when prompted
6. Wait for PlatformIO to finish installation (~5 minutes)

**Verify installation:**
- You should see PlatformIO icon on the left sidebar
- Click it and check if PlatformIO Home opens

### 3. Git
**Windows:**
- Download: https://git-scm.com/download/win
- Install with default settings
- Choose "Git Bash" during installation

**Verify:**
```bash
git --version
# Should show: git version 2.x.x dhjfgh
```

### 4. Python (required for PlatformIO)
**Usually installed with PlatformIO, but if issues occur:**

**Windows/macOS:**
- Download Python 3.9+: https://www.python.org/downloads/
- **Important:** Check "Add Python to PATH" during installation


## Hardware Drivers dghjh

### For STM32 (ST-Link)
**Windows:**
- Download ST-Link drivers: https://www.st.com/en/development-tools/stsw-link009.html
- Install and restart


### For ESP32
**Windows:**
- CP2102/CH340 USB drivers usually install automatically
- If not: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers


### For RP2040 (Raspberry Pi Pico)
- No special drivers needed
- Works as USB mass storage device

## SSH Setup for GitHub/GitLab

### 1. Generate SSH key
```bash
# Open terminal (Git Bash on Windows)
ssh-keygen -t ed25519 -C "your.email@example.com"

# Press Enter to save in default location
# Enter passphrase (optional but recommended)
```

### 2. Copy public key
**Windows (Git Bash):**
```bash
cat ~/.ssh/id_ed25519.pub
```

### 3. Add to GitHub
1. Go to: https://github.com/settings/keys
2. Click "New SSH key"
3. Paste your public key
4. Click "Add SSH key"

### 4. Test connection
```bash
ssh -T git@github.com
# Should see: "Hi username! You've successfully authenticated..."
```

## Create Your Course Repository
```bash
# 1. Create new repository on GitHub
# Name: embedded-course-2026 (or your-name-embedded-course)

# 2. Clone the template (optional - for reference only)
git clone git@github.com:Anaga/embedded-course-2026.git

# 3. Create your own repository
mkdir your-name-embedded-course
cd your-name-embedded-course
git init

# 4. Create basic structure
mkdir module1 module2 module3 module4 module5 module6
echo "# My Embedded Course Work" > README.md

# 5. First commit
git add .
git commit -m "Initial commit: course structure"

# 6. Connect to GitHub
git remote add origin git@github.com:your-username/your-repo-name.git
git branch -M main
git push -u origin main

# 7. Add instructor as collaborator
# On GitHub: Settings → Collaborators → Add @Anaga
```

## First PlatformIO Project (Test Setup)

### Create "Blink" project for ESP32:

1. Open VSCode
2. Click PlatformIO icon → "New Project"
3. Settings:
   - Name: `test-blink`
   - Board: Search "ESP32 Dev Module"
   - Framework: Arduino
4. Click "Finish" (will download packages ~5 minutes first time)

5. Replace `src/main.cpp` with:
```cpp
#include <Arduino.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

6. Connect ESP32 via USB
7. Click "Upload" button (→) in PlatformIO toolbar
8. LED should blink!

## Troubleshooting

### "PlatformIO: Command not found"
- Restart VSCode completely
- Reinstall PlatformIO extension

### "Permission denied" (Linux/macOS)
```bash
sudo usermod -a -G dialout $USER
# Log out and back in
```

### "Port not found" when uploading
- Check USB cable (try different one)
- Check device manager (Windows) or `ls /dev/tty*` (Linux/macOS)
- Install drivers (see Hardware Drivers section)

### Git SSH not working
- Check SSH key is added to GitHub
- Test: `ssh -T git@github.com`
- Try HTTPS instead: `git clone https://github.com/...`

## Useful VSCode Extensions (Optional)

- **C/C++** (Microsoft) - IntelliSense for C/C++
- **GitLens** - Enhanced Git integration
- **Better Comments** - Color-coded comments
- **Bracket Pair Colorizer** - Matching brackets colors

## Getting Help

- Course instructor: @Anaga
- PlatformIO Docs: https://docs.platformio.org/
- ESP32 Docs: https://docs.espressif.com/
- STM32 Docs: https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html

---
