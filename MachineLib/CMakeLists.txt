project(MachineLib)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

set(SOURCE_FILES
        pch.h
        IMachineSystem.h
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineDialog.cpp MachineDialog.h include/machine-api.h
        Const.cpp
        Const.h
        MachineSystemStandin.h
        MachineSystemStandin.cpp
        MachineStandin.cpp
        MachineStandin.h
        Polygon.cpp
        Polygon.h
        Cylinder.cpp
        Cylinder.h
        Box.cpp
        Box.h
        MachineSystem.cpp
        MachineSystem.h
        Machine.cpp
        Machine.h
        Component.cpp
        Component.h
        Machine1Factory.cpp
        Machine1Factory.h
        Sparty.cpp
        Sparty.h
        Crank.cpp
        Crank.h
        Shaft.cpp
        Shaft.h
        RotationSource.h
        IRotationSink.h
        Pulley.cpp
        Pulley.h
        KeyDropResponder.h
        Key.cpp
        Key.h
        Cam.cpp
        Cam.h
        Machine2Factory.cpp
        Machine2Factory.h
)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
