<h1 align="center" style="font-weight:bold;">FHI 🌻
</h1>

![banner](./banner.png)
<h2 align="center" style="font-weight:bold">
A C++ SDL Game: Flower Harvesting Incremental</h2>

## About

###### This project is developed as a part of the Advanced Programming course at the University of Engineering and Technology - VNUH.

- Full name: Nguyễn Đức Dũng
- SID: 23021495
- Course: INT2215_22
- Expected mark: >=8.5, reason:
  - Having a simple UI
  - Code from scratch, inherit some of the graphic and keyboard management code from [the instructor repo](https://github.com/chauttm/gameProject/tree/main/06_keyboard_event)
  - With game features:
    - Save/load game data
    - Volume slider
    - and more..

## Introduction

A game developed in C++ using the SDL2 library. The game is a simple incremental game where the player
earn flower by harvesting them (clicking on buttons). Level up to earn perk, which you can use upgrade many more
things. With many reset layers to improve early game process. 

### Download

Click [Release](https://github.com/DungxND/GameProj-SAI/releases) tab to download the latest executable release.

#### TO-DO:

- [x] Save and load game data
- [x] Create separate upgrade infobox
- [ ] Add reset layers
- [ ] Add more upgrades
- [ ] Add more sources
- [x] Multiple board tabs

## Build

This project is ready to be built on [JetBrains CLion](https://www.jetbrains.com/clion/). The `CMakeLists.txt` file is already configured to build the
project. SDL2, SDL2_image, SDL2_ttf, SDL2_mixer libraries are included. No additional setup is required.

To build the project, clone this repo and open in JetBrains CLion, Invalidate CMake Caches and Restart, then reload
CMake Project. After that,
build the project.

#### Requirement to build without CLion:

- **CMake** 3.29.3 or higher
- **SDL2**, **SDL2_image**, **SDL2_ttf**, **SDL2_mixer** (Already included in SDL folder)
- **MinGW** (for gcc.exe, g++.exe)
- **Ninja** (ninja.exe)

**Build command**:

Open the cloned game source folder and run this command in terminal:
```shell
cmake -S . -G Ninja -B build "-DCMAKE_CXX_COMPILER=/PATHTO/g++.exe" "-DCMAKE_C_COMPILER=/PATHTO/gcc.exe" "-DCMAKE_MAKE_PROGRAM=/PATHTO/ninja.exe"
cmake --build ./build --target FHI_Flower_Harvesting_Inc -j 14
```
Replace `/PATHTO/` with the path to the compiler and build tools.


## Credits

Thanks and credit to these projects and resources:

- **Core**: [SDL Libs](https://github.com/libsdl-org)
- **Music**:
  - [Bardcore Barbie Girl](https://www.youtube.com/watch?v=YNm3Ggv01Ns) - stantough
  - [Chiến thắng Điện Biên](https://bcdcnt.net/bai-hat/chien-thang-dien-bien-62.html) (Đỗ Nhuận) - Hợp ca nam nữ Đài TNVN
  - [Mùa xuân làng lúa làng hoa](https://open.spotify.com/track/1RgGpUM0a96PtGT7Q2RdBo) (Ngọc Khuê) - Bảo Trâm
  - [Hát về cây lúa hôm nay](https://open.spotify.com/track/0o1FvVBLsZB6iJ3DNSxWYm) (Hoàng Vân) - Vũ Thắng Lợi
- **Font**: [PressStart](https://fonts.google.com/specimen/Press+Start+2P)
- **Inspiration**: [Grass Cutting Incremental](https://www.roblox.com/games/9292879820/MULTIVERSE-Grass-Cutting-Incremental)

## Contact
Please send me an e-mail via: contact@dungxnd.io.vn

<br/>
<p align="center">
Powered by <a href="https://github.com/libsdl-org/SDL" target="_blank">SDL2</a> - Developed on <a href="https://www.jetbrains.com/clion/" target="_blank">JetBrains CLion</a>
</p>


