# Dynamic Machine System Factory

## Overview
The **Canadian Experience** project is a C++ application designed to simulate and animate various machine systems and characters. It features an animation framework, actor and timeline management, and machine system integrations. The project is built using CMake for cross-platform compatibility and includes a robust testing suite powered by Google Test.

## Features
- **Animation System**: Supports keyframe-based animations with actors and drawable components.
- **Machine System**: A modular system for constructing and controlling animated machinery.
- **User Interface**: Built using wxWidgets for cross-platform graphical interaction.
- **Testing Suite**: Utilizes Google Test for unit testing and validation.
- **Doxygen Documentation**: Automatically generated HTML documentation for code reference.

## Project Structure
```
├── CanadianExperienceApp.cpp/.h   # Main application entry point
├── CanadianExperienceLib          # Core library with animation and actor management
│   ├── Actor.cpp/.h               # Defines animation actors
│   ├── Drawable.cpp/.h            # Drawable components for actors
│   ├── Picture.cpp/.h             # Manages animated pictures
│   ├── Timeline.cpp/.h            # Handles animation timelines
│   └── ...
├── MachineLib                     # Machine system components
│   ├── Machine.cpp/.h             # Base machine class
│   ├── MachineSystem.cpp/.h       # System to manage machines
│   ├── Components (Box, Shaft, Pulley, Crank, etc.)
│   └── ...
├── MachineDemo                     # Standalone demonstration of the machine system
├── MachineTests                     # Google Test unit tests for machine components
├── Tests                            # Additional unit tests for animation framework
├── resources                        # Icons, images, and assets
├── html                             # Auto-generated Doxygen documentation
├── CMakeLists.txt                   # CMake build configuration
└── README.md                        # This file
```

## Installation & Build
### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- CMake (3.10+ recommended)
- wxWidgets (for UI support)
- Google Test (for running unit tests)

### Build Instructions
```sh
mkdir build
cd build
cmake ..
make
```

### Running the Application
```sh
./CanadianExperience
```

### Running Tests
```sh
make test
ctest --output-on-failure
```

## Documentation
The project includes auto-generated documentation using **Doxygen**. To generate the documentation:
```sh
doxygen Doxyfile.doxy
```
Then, open `html/index.html` in a browser.

## License
This project is licensed under the MIT License. See `LICENSE` for details.
