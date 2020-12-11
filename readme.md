# Practice with OpenGl and learn about Computer Graphics



Download [glew](http://glew.sourceforge.net/) and glfw and extract them, then build them as follow in ubuntu.

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