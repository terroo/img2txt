#!/usr/bin/env bash
echo "[Desktop Entry]
Type=Application
Name=Img2Txt
Comment=Extract text from image
Exec=/usr/bin/env LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${HOME}/.local/bin/Qt/6.3.0/gcc_64/lib" img2txt
Icon=img2txt
Categories=Qt;Utility;" > ./img2txt.desktop
