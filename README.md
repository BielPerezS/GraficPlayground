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

## User Guide
 - You are Patricio from the series SpongeBob, and can do the following actions:
 - C       : Toggle on/off Patricio POV. Also adjustable through "camera 2" in the interface.
 - WASD    : Move patricio
 - [SHIFT] : Toggle running
 - [SPACE] : Jump
 - [HORIZONTAL_ARROW_KEYS] : Moves Patricio's orientation.
 - [VERTICAL_ARROW_KEYS] : Adjust Patirico's Plane Y coordinate, also adjustable through "altura avio" in the interface. If patricio is riding his plane and its in route mode it also changes patricio vertical looking point.
 - Hold click && Move mouse   : Move the camera (The scene if Patricio POV is off, else Patricio's looking direction)
 - U      : Moves Patircio's Plane one step in a circular motion.
 - T      : Start's Patircio's Plane route. The plane starts spinning around the hangar.
 - F      : Change lighting place from Sonic to Patricio's Plane.
 - E      : Patircio teleports to its plane or goes back to its last position.
 - R      : Resets the scene and all its parameters.


