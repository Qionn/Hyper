# Building Hyper from Source

This guide will walk you through the steps to build the Hyper project from source using Premake5.

## Index

* [Requirements](#requirements)
* [Windows](#windows)
	* [Generate the Build Files](#generate-the-build-files-windows)
	* [Build the Project with Visual Studio](#build-the-project-with-visual-studio)
* [Linux and macOS](#linux-and-macos)
	* [Generate the Build Files](#generate-the-build-files-linux-and-macos)
	* [Build the Project with GNU Make](#build-the-project-with-gnu-make)

## Requirements

Before building the Hyper project from source, make sure that you have the following software installed on your system:

* Git
* LunarG Vulkan SDK 1.0 or newer
* Visual Studio 2022 *(Windows only)*
* GNU Make *(Linux and macOS only)*

## Windows

### Generate the Build Files (Windows)

1. Download Premake5 from the [Premake download page](https://premake.github.io/download) and save it to a location on your computer.
2. Open a command prompt and navigate to the root directory of the Hyper source code.
3. Run the following command to generate the build files for Visual Studio 2019:
```bash
path\to\premake5.exe vs2022
```
4. This will generate the Visual Studio solution and project files.

### Build the Project with Visual Studio

1. Open the \"Hyper.sln\" file with Visual Studio 2022.
2. Select \"Batch Build...\" from the \"Build\" menu.
	* In the \"Batch Build\" dialog, make sure that all projects are selected.
3. Click the \"Build\" button to build the project.
4. This will build the project and create the binary files in the \"bin\" directory.

## Linux and macOS

### Generate the Build Files (Linux and macOS)

1. Download Premake5 from the [Premake download page](https://premake.github.io/download) and save it to a location on your computer.
2. Open a terminal and navigate to the root directory of the Hyper source code.
3. Run the following command to generate the build files for GNU Make:
```bash
path/to/premake5 gmake2
```
4. This will generate the GNU Make build files.

### Build the Project with GNU Make

1. Open a terminal and navigate to the root directory of the Hyper source code.
2. Run the following command to build the project:
```bash
make
```
3. This will build the project and create the binary files in the \"bin\" directory.
