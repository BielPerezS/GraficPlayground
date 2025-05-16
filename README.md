# GraficPlayground

**GraficPlayground** is a simple 3D graphics playground built with **Qt** and **OpenGL**. It allows for rendering 3D models, setting up scenes, experimenting with lighting, and handling basic interaction through keyboard and mouse events.

---

## ✅ Requirements

Make sure you have the following installed before building:

- **QMake** version **3.1** or higher
- **Qt** version **5.15.13** or higher

---

## 🧪 How to Build and Run

Open a terminal in the project folder and run:

```bash
qmake
make
./examen
```
---
## 📁 Project Structure
```bash
GraficPlayground/
│
├── shaders/           # Contains vertex and fragment shaders for lighting
│
├── model/
│   ├── model.cpp      # Model loader implementation
│   ├── model.h        # Model loader header
│   └── *.obj          # 3D model files (textures not supported)
│
├── MyGLWidget.cpp     # Main OpenGL widget - handles everything
├── ExamGLWidget.cpp   # Base widget with a default (empty) scene
├── main.cpp           # Entry point
└── examen.pro         # Project file for QMake
```
---
## 🎮 What It Does

   - Loads and displays 3D models

   - Initializes custom 3D scenes

   - Sets up lighting via shaders

   - Handles movement and basic interaction

   - Syncs user events (keyboard, mouse) with the scene

   - Note: Due to limitations in model.cpp, models with textures (like many from https://www.models-resource.com/) will appear completely white.

## 🕹️ User Guide

You control **Patricio** from *SpongeBob*. Here's how to interact with the scene:

### 🎥 Camera Controls
- `C` — Toggle Patricio's POV (also adjustable via "camera 2" in the UI)
- `Hold Left Click + Move Mouse` — Rotate the camera  
  (controls the scene if POV is off, or Patricio’s view direction if POV is on)

### 🧍 Movement Controls
- `W / A / S / D` — Move Patricio
- `SHIFT` — Toggle running mode
- `SPACE` — Jump
- `← / →` — Rotate Patricio left/right
- `↑ / ↓` — Change Patricio's Y-plane coordinate (also adjustable via "altura avió" in the UI)

### ✈️ Plane Controls
- `U` — Move Patricio’s plane one step in a circular motion
- `T` — Start the plane's automated route (circles around the hangar)
- `E` — Teleport Patricio to/from his plane

### 💡 Scene & Lighting
- `F` — Toggle light source between Sonic and Patricio’s plane
- `R` — Reset the scene and all parameters



