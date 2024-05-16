<h1 align="center" style="font-weight:bold;">FHI
</h1>
<h2 align="center" style="font-weight:bold">
A C++ SDL Game: Flower Harvesting Incremental</h2>

![banner](./banner.png)

### About:

###### This project is developed as a part of the Advanced Programming course at the University of Engineering and Technology - VNUH.

- Name: Nguyễn Đức Dũng
- SID: 23021495
- Expected mark: 8.5, reason:
  - Having a simple UI
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

This project is ready to be built on JetBrains CLion. The `CMakeLists.txt` file is already configured to build the
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
Replace `/PATHTO/` with the path to the compiler and build tools.

```shell
cmake -S . -G Ninja -B build "-DCMAKE_CXX_COMPILER=/PATHTO/g++.exe" "-DCMAKE_C_COMPILER=/PATHTO/gcc.exe" "-DCMAKE_MAKE_PROGRAM=/PATHTO/ninja.exe"
cmake --build ./build --target FHI_Flower_Harvesting_Inc -j 14
```

## Credits

Thanks and credit to these projects and resources:

- Core: [SDL Libs](https://github.com/libsdl-org)
- Music:
  [Bardcore Barbie Girl](https://www.youtube.com/watch?v=YNm3Ggv01Ns), [Chiến thắng Điện Biên](https://bcdcnt.net/bai-hat/chien-thang-dien-bien-62.html), [Mùa xuân làng lúa làng hoa](https://open.spotify.com/track/1RgGpUM0a96PtGT7Q2RdBo), [Hát về cây lúa hôm nay](https://open.spotify.com/track/0o1FvVBLsZB6iJ3DNSxWYm?si=acdff0ebfec543ce)
- Font: [PressStart](https://fonts.google.com/specimen/Press+Start+2P)

<br/>
<p align="center">
Powered by <a href="https://github.com/libsdl-org/SDL" target="_blank">SDL2</a> - Developed on JetBrains CLion</p>


