# Fallout Place In Red VR

Mod to allow for placing workshop items in red areas for the VR version of the game.    Based on patches for the psc87's [NG place in red mod](https://www.nexusmods.com/fallout4/mods/14601?tab=description)   

## Requirements

- [CMake](https://cmake.org/)
  - Add this to your `PATH`
- [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [CommonLibF4](https://github.com/alandtse/CommonLibF4)
  - Add this as as an environment variable `CommonLibVRF4`

## User Requirements

- [VR Address Library for F4SEVR](https://www.nexusmods.com/fallout4/mods/64879)
  - Needed for VR

## Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

## Building

```
git clone git@github.com:rollingrock/fallout-place-in-red-vr.git
cd fallout-place-in-red-vr
# pull submodules
git submodule update --init --recursive
```

### VR

```
# run preset
cmake --preset vs2022-windows-vcpkg-vr
# see CMakeUserPresets.json.template to customize presets
cmake --build buildvr --config Release
```

## Credits

Skyrim/Fallout modding is built on the community. I cannot ever have done any of my mods alone and the work continues to be built off of people such as listed below.

- psc87 - for NG version of this mod
- alandtse for all the tools and commonlib direction
- Contributors to [CommonLib (check fork network and all the credits)](https://github.com/alandtse/CommonLibVR/tree/vr), including the original author, [Ryan](https://github.com/Ryan-rsm-McKenzie).
- [F4SE Team](https://skse.silverlock.org/)
- [Powerof3](https://github.com/powerof3)
- shad0wshayd3 - for easy to follow commonlib examples to learn off of

