# 🎮 GraficPlayground

**GraficPlayground** is an OpenGL-based 3D graphics playground built using Qt and QMake. This project serves as an interactive platform to experiment with 3D scenes, lighting, model loading, and event handling. Ideal for learning and extending OpenGL in a Qt environment.

---

## 🚀 Getting Started

### ✅ Prerequisites

Make sure you have the following installed:

- **Qt** `>= 5.15.13`
- **QMake** `>= 3.1`

---

### 🛠️ Build Instructions

To compile and run the project:

```bash
qmake
make
./examen

GraficPlayground/
│
├── shaders/          # Contains lighting shaders (vertex & fragment)
├── model/
│   ├── model.cpp     # Model loader implementation
│   ├── model.h       # Model loader header
│   └── *.obj         # 3D model files (textures not supported)
├── MyGLWidget.cpp    # Main playground logic
├── ExamGLWidget.cpp  # Base OpenGL widget (provides default scene)
└── main.cpp          # Application entry point


🧠 Key Concepts

    MyGLWidget inherits from ExamGLWidget and implements the full logic of the playground:

        Scene initialization

        Model loading

        Lighting setup

        Object movement

        Input/event synchronization

    Model Textures:
    Due to limitations in model.cpp, texture loading is not supported. Models that rely on textures (e.g., those from The Models Resource) will appear white.
