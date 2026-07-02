# Weave

## Build instructions

Weave can be built using CMake through the `CMakeLists.txt` at the root of the project.

### Windows

Using the CMake GUI, select the root of the project in the "Where is the source code" field. And select a new empty directory where the binaries will be built.

Then click "Configure", when that is done, click "Generate".

By default, this will create a Visual Studio solution project. Open that generated solution and build it through Visual Studio.

### Linux

#### Nix

First, enter a development shell. This will create a shell with all the required Wayland and/or X11 dependencies.

```bash
nix develop
```

Then create a build directory.

```bash
mkdir build
cd build
```

Configure the project.

```bash
cmake ..
```

And build

```bash
cmake --build .
```

## Development instructions

When developing on NixOS, and using CLion, use the following command to open CLion with all the needed Wayland and/or X11 dependencies:

```bash
nix develop
clion .
```
