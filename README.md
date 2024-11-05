# Building Examples

- Install `Visual Studio Code` from https://visualstudio.microsoft.com/downloads/
- Open and install all recommended workspace extensions
- Configure the current build environment:
  - [Building on Windows](#building-on-windows)
- Press `Ctrl` + `Shift` + `B` and select `CMake: build`

# Building on Windows
Below is a list of all tested environments for C/C++ development on Windows:

<b><i><u>MSYS2 MinGW-W64 (GCC)</u></b></i>
> MSYS2 is a collection of tools and libraries providing you with an easy-to-use environment for building, installing and running native Windows software.
> - Download the installer from https://www.msys2.org/
> - Install the software to `C:\msys64` (or another location)
> - Add `C:\msys64\mingw64\` to the `PATH` environment variable
> - Open the `MSYS2 MINGW64` terminal/software
> - Run the following command:
>   ```bash
>   pacman -S mingw-w64-x86_64-gcc\
>             mingw-w64-x86_64-ninja\
>             mingw-w64-x86_64-cmake
>   ```
> - Press `Enter` to finish installation

<b><i><u>Build Tools for Visual Studio 2022 (MSVC)</u></b></i>
> Visual Studio is a product family of tools and services for coding, debugging, and publishing apps on any platform and device.
> - Download the installer from https://visualstudio.microsoft.com/downloads/
> - Once `Visual Studio Installer` opens, select `Desktop Development with C++` option
> - Install the software to `C:\Program Files\Microsoft Visual Studio\2022\Build Tools` (or another location)