# Nibbler
Create the snake game using different graphic libraries. We can switch between them at runtime.

I used 3 libraries:
- Ncurses
- SFML
- Opengl

With 1 bonus library:
- Miniaudio

The goal of this project is to use theses functions:
- **dlopen**: load dynamic library.
- **dlclose**: close dynamic library.
- **dlsym**: load symbol.

---

- Clone Repository
```bash
git clone https://github.com/vvaucoul/Nibbler && cd Nibbler
```

- Download and Compile libraries
```bash
make install-libs
```

- Compilation
```bash
make
```

- Start the game
```bash
./nibbler [width] [height] [interface]
```

Switch between Interfaces:

- Ncurses: **U**
- SFML: **I**
- OpenGL: **O**

## Examples

![Snake_01](https://user-images.githubusercontent.com/66129673/206437547-fb4c2206-fc5b-45ae-b88a-42940a05b131.gif)

---

<img src="https://user-images.githubusercontent.com/66129673/206437043-2227bc69-db17-4caf-a265-6f9080cd744b.png">
<img align="left" src="https://user-images.githubusercontent.com/66129673/206437197-54726300-5508-4e65-9701-3c58709f4360.png" width="45%">
<img src="https://user-images.githubusercontent.com/66129673/206437285-a88746d4-f262-40ef-bf26-cc5db9597d5a.png" width="45%">

