# 🖼️ Preview

> <p align="center">
>
> <video controls src="preview.mp4" title="preview"></video>

> </p>
>
> <br>
> <br>
> <br>

# 🎵 Music Player with Raylib

This project is a simple desktop music player built using [Raylib](https://www.raylib.com/) and C++.  
It features a modern UI with dark/light mode toggle, play/pause, next/previous controls, and a seek slider for music playback.

## ✨ Features

- 🎶 Play multiple local MP3 tracks
- ⏯️ Play/Pause button
- ⏩ Next & ⏪ Previous track controls
- 📀 Animated CD artwork
- 🌗 Dark/Light mode toggle
- 📊 Seek slider with time display

## 🛠️ How to Build

1. Make sure you have [Raylib](https://www.raylib.com/) installed.
2. Use the provided `Makefile` or VS Code tasks to build:
   - **Debug:**  
     `make PLATFORM=PLATFORM_DESKTOP BUILD_MODE=DEBUG`
   - **Release:**  
     `make PLATFORM=PLATFORM_DESKTOP`

## 📂 Project Structure

- `main.cpp` — Main application logic and render loop
- `src/function.h` — UI and music control functions
- `resource/` — Images and music files

## 🚀 Usage

- Run the compiled executable.
- Use the UI buttons to control playback and switch tracks.
- Toggle dark/light mode using the switch in the top-right corner.

---

Made with
