# Img2Txt

![Img2Txt](./resources/img/img2txt.png) 

Graphic application to extract text from image

---

# Dependencies
+ [gcc/g++](https://gcc.gnu.org/)
+ [CMake](https://cmake.org/)
+ [Make](https://www.gnu.org/software/make/)
+ [Qt](https://www.qt.io/)
+ [OpenCV](https://github.com/opencv/opencv)
+ [Leptonica](https://github.com/DanBloomberg/leptonica)
+ [Tesseract](https://github.com/tesseract-ocr/tesseract)

Example of dependencies on [Ubuntu](https://ubuntu.com/):

Download and install [from here](https://www.qt.io/download-qt-installer), like this [video](https://www.youtube.com/watch?v=2fXBeN1EUzs) .
> Remember the path where you installed it and add Qt6 support and Qt5 compatibility

And now install the packages:
```bash
sudo apt install build-essential cmake make g++ libtesseract-dev libopencv-dev
```

---

# Building and Install
> Change `PATH/TO/Qt` by the path where you installed Qt

If you chose to install Qt in your home directory, just change `[PATH/TO/Qt]` to `${HOME}/Qt`, also inform the version of Qt6 that is on your system, that is, change `[6.X.X]` to the corresponding version.
> In my case I installed it on `${HOME}/.local/bin` so I run: `cmake -B build -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH=${HOME}/.local/bin/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake -DCMAKE_PREFIX_PATH:PATH=${HOME}/.local/bin/Qt/6.3.0/gcc_64` .

And then clone, build and install:

> NOTE: Change: `[PATH/TO]` and `6.X.X` 
```bash
git clone https://github.com/terroo/img2txt
cd img2txt
cmake -B build \
    -DCMAKE_PROJECT_INCLUDE_BEFORE:FILEPATH=[PATH/TO]/Qt/Tools/QtCreator/share/qtcreator/package-manager/auto-setup.cmake \
    -DCMAKE_PREFIX_PATH:PATH=PATH/TO/Qt/[6.X.X]/gcc_64
cd build
make
sudo make install
```

Before opening the app add these lines to your BASHRC:
```bash
echo 'export LD_LIBRARY_PATH="[PATH/TO]/Qt/[6.X.X]/gcc_64/lib"' >> ~/.bashrc
exec $SHELL
source ~/.bashrc
```

---

# Screenshots

![]() 

![]() 

---

# Uninstall
