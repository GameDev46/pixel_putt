<a href="https://github.com/GameDev46" title="Go to GitHub repo">
    <img src="https://img.shields.io/static/v1?label=GameDev46&message=|&color=Green&logo=github&style=for-the-badge&labelColor=1f1f22" alt="GameDev46 - particle_experiment">
    <img src="https://img.shields.io/badge/Version-0.1.2-green?style=for-the-badge&labelColor=1f1f22&color=Green" alt="GameDev46 - pixel_putt">
</a>

 ![Static Badge](https://img.shields.io/badge/--1f1f22?style=for-the-badge&logo=C&logoColor=6060ef)
    
<a href="https://github.com/GameDev46/pixel_putt/stargazers">
    <img src="https://img.shields.io/github/stars/GameDev46/pixel_putt?style=for-the-badge&labelColor=1f1f22" alt="stars - pixel_putt">
</a>
<a href="https://github.com/GameDev46/pixel_putt/forks">
    <img src="https://img.shields.io/github/forks/GameDev46/pixel_putt?style=for-the-badge&labelColor=1f1f22" alt="forks - pixel_putt">
</a>
<a href="https://github.com/GameDev46/pixel_putt/issues">
    <img src="https://img.shields.io/github/issues/GameDev46/pixel_putt?style=for-the-badge&labelColor=1f1f22&color=blue"/>
 </a>

<br>
<br>

<p align="left">
<a href="https://twitter.com/gamedev46" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/twitter.svg" alt="gamedev46" height="30" width="40" /></a>
<a href="https://www.youtube.com/c/gamedev46" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/youtube.svg" alt="gamedev46" height="30" width="40" /></a>
</p>

# pixel_putt

A simple top down 2D golf game made entirely in C using the [Raylib library](https://raylib.com)

# Usage

You may use any version of Pixel Putt you like, but I reccomend using the [newest version](/Pixel%20Putt%20V0.2.0) as it will be the least buggy and most user friendly out of them all!

Left click, pull back and release to shoot your trusty golf ball across the map evading obstacles and reaching the hole to progress. Pixel Putt is an open source golf game that can be used directly on your windows computer (I am not sure if it is supported on Mac and Linux) by running the [Pixel Putt executable](Pixel%20Putt%20V0.2.0/pixelPutt.exe) file in the repository. If you want to create your own levels or just change the game to your liking, open the [main c file](Pixel%20Putt%20V0.2.0/main.c) using an appropriate code editing software and then when you are finished run the command...

<pre>gcc main.c -o pixelPuttModed.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm</pre>

...to compile your new code into an exe file. You will however need to install the gcc compiler if you haven't already done so if the compiling fails, but a useful tutorial can be found on the [official VS code website](https://code.visualstudio.com/docs/cpp/config-mingw). Once this is done simply run the pixelPuttModed.exe file and watch as your changes come to life in your new version!

# Screenshots

<p>
  <img src="https://github.com/GameDev46/pixel_putt/assets/76485006/643a3021-8a9e-43cb-a017-011b125c3310" height="300">
  &nbsp;
  <img src="https://github.com/GameDev46/pixel_putt/assets/76485006/031441c2-e326-4c5d-b52f-f466e7c5985a" height="300">
</p>

# Credits

**Theme Song:** <br>
GameDev46

**Sound Effects:** <br>
[freesound.org](https://freesound.org)<br>
GameDev46

**Programming:** <br>
GameDev46

**Art:** <br>
GameDev46

# Update Log

[**V0.1.0**](/Pixel%20Putt%20V0.1.0)

- Initial release

[**V0.1.2**](/Pixel%20Putt%20V0.1.2)

- More levels
- Better level creation system
- More block types
- Main Menu
- Level select
- Many bug fixes!

[**V0.2.0**](/Pixel%20Putt%20V0.2.0)

- Saving and loading
- New menu buttons
- Physics changes
- New levels
- Many bug fixes!
