<a href="https://github.com/GameDev46" title="Go to GitHub repo">
    <img src="https://img.shields.io/static/v1?label=GameDev46&message=|&color=Green&logo=github&style=for-the-badge&labelColor=1f1f22" alt="GameDev46 - particle_experiment">
    <img src="https://img.shields.io/badge/Version-0.0.1-green?style=for-the-badge&labelColor=1f1f22&color=Green" alt="GameDev46 - particle_experiment">
</a>

![Static Badge](https://img.shields.io/badge/--1f1f22?style=for-the-badge&logo=C&logoColor=6060ef)
    
<a href="https://github.com/GameDev46/particle_experiment/stargazers">
    <img src="https://img.shields.io/github/stars/GameDev46/particle_experiment?style=for-the-badge&labelColor=1f1f22" alt="stars - particle_experiment">
</a>
<a href="https://github.com/GameDev46/particle_experiment/forks">
    <img src="https://img.shields.io/github/forks/GameDev46/particle_experiment?style=for-the-badge&labelColor=1f1f22" alt="forks - particle_experiment">
</a>
<a href="https://github.com/GameDev46/particle_experiment/issues">
    <img src="https://img.shields.io/github/issues/GameDev46/particle_experiment?style=for-the-badge&labelColor=1f1f22&color=blue"/>
 </a>

<br>
<br>

<div align="left">
<a href="https://gamedev46.github.io/particle_experiment/">
    <img src="https://img.shields.io/badge/View_site-GH_Pages-2ea44f?style=for-the-badge&labelColor=1f1f22" alt="View site - GH Pages">
</a>
</div>

<br>

<p align="left">
<a href="https://twitter.com/gamedev46" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/twitter.svg" alt="gamedev46" height="30" width="40" /></a>
<a href="https://instagram.com/oliver_pearce47" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/instagram.svg" alt="oliver_pearce47" height="30" width="40" /></a>
<a href="https://www.youtube.com/c/gamedev46" target="blank"><img align="center" src="https://raw.githubusercontent.com/rahuldkjain/github-profile-readme-generator/master/src/images/icons/Social/youtube.svg" alt="gamedev46" height="30" width="40" /></a>
</p>

# pixel_putt

A simple top down 2D golf game made entirely in C with Raylib

# Usage

Left click, pull back and release to shoot your trusty golf ball across the map evading obstacles and reaching the hole to progress. Pixel Putt is a simple open source golf game that can be used directly on your windows computer (I am not sure if it is supported on Mac and Linux) by running the [Pixel Putt executable](/pixelPutt.exe) file in the repository. Want to create your own levels or just change the game to your liking, open the [main c file](/main.c) using an appropriate code editing software and then when you are finished run the command...

<pre>gcc main.c -o pixelPuttModed.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm</pre>

...to compile your new code into an exe file. You will however need to install the gcc compiler if you haven't already done so if the compiling fails, but a useful tutorial can be found on the [official VS code website](https://code.visualstudio.com/docs/cpp/config-mingw). Once this is done simply run the pixelPuttModed.exe file and watch as your changes come to life in your new version!

# Screenshots

<p>
  <img src="https://github.com/GameDev46/pixel_putt/assets/76485006/643a3021-8a9e-43cb-a017-011b125c3310" height="300">
  &nbsp;
  <img src="https://github.com/GameDev46/pixel_putt/assets/76485006/031441c2-e326-4c5d-b52f-f466e7c5985a" height="300">
</p>
