<h1 align="center">Space Shooter</h1>

<p align="center">
  <img width="450" height="275" src="docs/sdl_spaceshooter.gif">
</p>

[![CodeFactor](https://www.codefactor.io/repository/github/joshuacrotts/Space-Shooter/badge)](https://www.codefactor.io/repository/github/joshuacrotts/Space-Shooter) ![GitHub contributors](https://img.shields.io/github/contributors/JoshuaCrotts/Space-Shooter ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/JoshuaCrotts/Space-Shooter) ![GitHub repo size](https://img.shields.io/github/repo-size/JoshuaCrotts/Space-Shooter)  ![](https://tokei.rs/b1/github/JoshuaCrotts/Space-Shooter) ![](https://tokei.rs/b1/github/JoshuaCrotts/Space-Shooter?category=files) [![GitHub issues open](https://img.shields.io/github/issues/JoshuaCrotts/Space-Shooter)]() 
[![GitHub issues closed](https://img.shields.io/github/issues-closed-raw/JoshuaCrotts/Space-Shooter)]()

Space Shooter is a little space shooting game based off a tutorial from the parallelrealities website. This introduced me to SDL and in-depth C programming. This project is buggy and a mess all around, but was one of my first experiences developing a somewhat large project in C, and more so with SDL. After this, I wrote C-Standards and several other things with C.

## Dependencies

If you want to run the game, just download the runtime binaries at the provided links below. Conversely, if you wish to build the project, you will need to grab the development libraries for your system. For my purposes, I used the MinGW versions.

1. [SDL TTF Library (sdl_ttf)](https://www.libsdl.org/projects/SDL_ttf/)
2. [SDL Image-Loading Library (sdl_image)](https://www.libsdl.org/projects/SDL_image/)
3. [SDL Audio Library (sdl_mixer)](https://www.libsdl.org/projects/SDL_mixer/)

## Rebuilding Space Shooter

**Windows**: To rebuild the code, clone the repository to your computer. This project is compiled with MinGW and a makefile. The SDL .dll files are not included and will need to be downloaded separately to build from source without modifications to the makefile. Compile the code via <code>mingw32-make</code>.

**Linux (Ubuntu/Debian)**: The process is similar to the former, with the exception of having to install SDL files to your system in Linux. Run the following commands (or their distro-equivalent) in your terminal:

1. <code>sudo apt-get install libsdl2-dev</code>
2. <code>sudo apt-get install libsdl2-image-dev</code>
3. <code>sudo apt-get install libsdl2-ttf-dev</code>
4. <code>sudo apt-get install libsdl2-mixer-dev</code>

Then, compile via <code>make</code>.

## Reporting Bugs

See the Issues Tab.

## Version History
The **master** branch encompasses all significant changes.
