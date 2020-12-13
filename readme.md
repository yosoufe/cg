# Practice with OpenGl and learn about Computer Graphics

Following a udemy course: https://www.udemy.com/course/graphics-with-modern-opengl/

# Usage:
It is tested on Ubuntu. Install the apt packages in section below. 
Download and install your latest Graphics Card's Driver. 
I tested with Nvidia card. Then

### to clone:
```
git clone https://github.com/yosoufe/cg.git
cd cg
git submodule update --init --recursive
```

### to compile
```
mkdir build && cd build
cmake ..
make
```

### to run
```
# in build directory
./main

```

# How I built 3rdParty libs:
You do not need to follow this section for using the repo on ubuntu.
### glew and glfw:
I already built them and added them to `3rdParty` dir here.
But this is how I compiled them as personal documentation:


Download [glew](http://glew.sourceforge.net/) and 
[glfw](https://www.glfw.org/download.html) and extract 
them, then build them as follow in ubuntu.

```bash
git clone https://github.com/nigels-com/glew.git
sudo apt-get install libgl-dev dos2unix git wget
cd glew/auto
make -j20
cd ../build
mkdir install
cmake -DCMAKE_INSTALL_PREFIX=install ./cmake
make -j20


cd ../.. # to root of the project
git clone git@github.com:glfw/glfw.git
sudo apt-get install xorg-dev
mkdir -p build/install
cd build
cmake -DCMAKE_INSTALL_PREFIX=install ../
make -j20 install
```

Then moved the `install` directories into the 3rdParty directory of this repo.

#### GLM: OpenGL Mathematics
I included [GML](http://glm.g-truc.net/) as a submodule 
to this repo by running the following

```
cd 3rdParty
git submodule add git@github.com:g-truc/glm.git
```