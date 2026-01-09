qt_add_qml_module(Core STATIC
        URI Core       # ↔ QML 端 import AmpSnap.Core 1.0
        VERSION 1.0
        SOURCES
        KdbProxy.h
        bdaqctrl.h
        core.h
        core.cpp
        DIOModule.h
        DIOModule.cpp
        ModbusManager.h
        ModbusManager.cpp
        ModbusWorker.h
        ModbusWorker.cpp
        MS300.h
        MS300.cpp
        Tension.h
        Tension.cpp
)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(Core
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::QuickTimeline
        Qt${QT_VERSION_MAJOR}::ShaderTools
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::Concurrent
        Qt${QT_VERSION_MAJOR}::SerialBus
#        Qt${QT_VERSION_MAJOR}::OpcUa
)
