Twilight Princess Ultimate Edition (GCN USA)

A Windows-friendly fork of the decompiled GameCube USA (GZ2E01) build of The Legend of Zelda: Twilight Princess, featuring 60FPS physics, resolution scaling, and modern quality-of-life improvements.

<p align="center"> <img src="https://github.com/TP-Ultimate-Edition/.github/raw/main/banner.png" width="720" alt="Twilight Princess Ultimate Edition Banner"> </p>
🚫 IMPORTANT LEGAL NOTICE — READ BEFORE CONTINUING
We do NOT distribute game assets or ISO files.
We will NEVER provide, upload, or link to copyrighted ROMs, ISOs, or extracted game data.
You must supply your own LEGITIMATE personal dump of the GameCube USA version (GZ2E01).

This project only provides:

Decompiled code

Tools

Scripts

Engine patches

Instructions

You are responsible for obtaining your own legal copy of the game and dumping it yourself.

⚠️ Version Compatibility Notice
This project only works with the GameCube USA version (GZ2E01).

No PAL, Japanese, or Wii versions are supported.
Using any ISO other than GZ2E01 will result in errors or a broken build.

⭐ Features

True 60FPS engine via delta-time physics

Correct animation & gameplay timing at 60FPS

Resolution scaling for modern hardware

QoL improvements inspired by Twilight Princess HD

Windows + Linux ISO building included

Dolphin-optimized output

🚨 IMPORTANT BUILD PREREQUISITE

Before using any ISO build script:

You must successfully complete a normal decomp build using the USA (GZ2E01) ISO.

If the standard build fails, the ISO build will also fail.

🔧 Dependencies
🪟 Windows
1. Install Python 3.14.0 (64-bit)

Download: https://www.python.org/ftp/python/3.14.0/python-3.14.0-amd64.exe

Verify:

python --version
pip --version

2. Install Ninja
winget install Ninja-build.Ninja


or

pip install ninja

3. Install gclib
pip install "gclib[speedups] @ git+https://github.com/LagoLunatic/gclib.git"

🐧 Linux

Install Python + Ninja:

sudo apt install python3 python3-pip ninja-build


(or your distro equivalent)

Install gclib:

pip3 install "gclib[speedups] @ git+https://github.com/LagoLunatic/gclib.git"

🏗️ Standard Decomp Build (Required First)

Clone the repo:

git clone https://github.com/TP-Ultimate-Edition/Twilight-Princess-Ultimate-Edition.git
cd Twilight-Princess-Ultimate-Edition


Place your own legally dumped USA ISO at:

orig/GZ2E01/baserom.iso


Configure the project:

python3 configure.py --version=GZ2E01


Build:

ninja


A successful build produces:

Compiled REL modules

build/GZ2E01/framework.iso

💿 Windows ISO Build

Run:

build_iso.bat


You will be prompted for:

✔️ Your Dolphin Emulator path only

The script will:

Use your existing orig/GZ2E01/baserom.iso

Rebuild all RELs

Produce the patched 60FPS Ultimate Edition ISO

Output a Dolphin-ready image

🐍 Linux ISO Build

Run the included script:

python3 build_iso_linux.py


It will:

Ask for your output ISO name

Compile a patched 60FPS ISO

Output a Dolphin-ready image

⚡ 60FPS Engine Overview

This fork provides:

Frame-rate–independent delta-time physics

Proper 60FPS animations & movement

Smooth, stable gameplay

Resolution scaling

Optional TPHD-style QoL enhancements

📘 Modding & Contributions

Before modifying RELs or engine code:

→ Please read Modding Guide.pdf.

It covers:

Correct REL editing workflow

Build system requirements

How to avoid incompatible or broken builds

Maintaining 60FPS engine stability

🙏 Credits
🏹 Zelda Reverse Engineering Team

For fully decompiling the GameCube USA (GZ2E01) version of Twilight Princess.
This project exists thanks to their foundational work.

🔧 Carco

For essential research and documentation regarding:

REL internals

REL patching methodology

ISO rebuild processes

Their work made advanced engine modifications possible.

<p align="center"> <b>Enjoy Twilight Princess in smooth, modern 60FPS — using your own legitimate USA GCN dump!</b> </p>