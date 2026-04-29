# blackhole_mono_particles

Simulasi visual black hole monokrom berbasis C++17 dan OpenGL 3.3 core profile. Fokusnya adalah piringan akresi granular hitam-putih dengan ratusan ribu partikel, event horizon hitam pekat, kamera 3D interaktif, grid ruang-waktu opsional, dan post-processing grayscale dengan contrast, bloom ringan, vignette, grain, serta distorsi lensing sederhana.

Visual piringan akresi sengaja tidak memakai warna kuning, oranye, merah, biru, atau palet warna lain. Semua output scene dan post-processing tetap grayscale.

## Dependencies

Linux packages yang diperlukan:

- CMake 3.16+
- g++ atau clang++ dengan dukungan C++17
- OpenGL / Mesa development headers
- GLFW
- GLM

GLAD sudah disertakan di folder `external/glad` sebagai loader minimal untuk fungsi OpenGL yang dipakai project ini.

Contoh instalasi Debian/Ubuntu:

```bash
sudo apt install build-essential cmake libglfw3-dev libglm-dev libgl1-mesa-dev
```

Contoh instalasi Fedora:

```bash
sudo dnf install gcc-c++ cmake glfw-devel glm-devel mesa-libGL-devel
```

## Build

```bash
mkdir build
cd build
cmake ..
make
./blackhole_mono_particles
```

Atau dari luar folder project:

```bash
cmake -S blackhole_mono_particles -B blackhole_mono_particles/build
cmake --build blackhole_mono_particles/build
./blackhole_mono_particles/build/blackhole_mono_particles
```

## Controls

- Left mouse drag di dalam window: orbit kamera mengelilingi pusat
- W / S: dekatkan / jauhkan kamera dari pusat
- A / D: orbit kamera ke kiri / kanan mengelilingi pusat
- Scroll di dalam window: dekatkan / jauhkan kamera dari pusat
- Space: pause / resume animasi
- R: reset kamera
- G: toggle grid ruang-waktu
- P: toggle post-processing
- N: toggle grain monokrom
- Esc: keluar

## Parameter visual utama

Parameter awal berada di `src/main.cpp` dan `src/ParticleSystem.hpp`:

- `NUM_PARTICLES = 200000`
- `INNER_RADIUS = 1.4f`
- `OUTER_RADIUS = 8.0f`
- `EVENT_HORIZON_RADIUS = 1.0f`
- `DISK_THICKNESS = 0.18f`
- `MIN_PARTICLE_SIZE = 0.75f`
- `MAX_PARTICLE_SIZE = 3.4f`
- `BASE_ORBIT_SPEED = 2.2f`
- `GRAIN_STRENGTH = 0.25f`
- `BLOOM_STRENGTH = 0.35f`
- `VIGNETTE_STRENGTH = 0.65f`
- `POST_CONTRAST = 1.25f`
- `ParticleSizeScale = 1.0f`

Jika GPU terasa berat, turunkan `NUM_PARTICLES` ke `50000` atau `30000`, atau turunkan `ParticleSizeScale` di `src/main.cpp`. Orbit partikel dihitung di vertex shader OpenGL sehingga CPU tidak meng-upload posisi partikel tiap frame, tetapi jumlah partikel, ukuran point sprite, additive blending, dan post-processing tetap bisa membebani GPU/fill-rate.

## Struktur

```text
blackhole_mono_particles/
├── CMakeLists.txt
├── README.md
├── assets/shaders/
├── external/glad/
└── src/
```

`external/glad` ditambahkan agar project tetap mudah dikompilasi walau package GLAD tidak tersedia di sistem.
