# Metaprogramming SFINAE
Educational project with Doxygen

## Build local Linux
```shell
sudo apt-get update && sudo apt-get install cmake -y

cd MetaprogrammingSFINAE
mkdir build && cd build

cmake ..

# build release
cmake --build . --config Release

# build deb-package
cmake --build . --target package
```

## Build local Windows
```shell
cd MetaprogrammingSFINAE
mkdir build && cd build

cmake ..

# build release
cmake --build . --config Release
```
