cmake_minimum_required(VERSION 3.16)

project(TaintedGrail-QuestsTracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appTaintedGrail-QuestsTracker
    src/main.cpp
)

qt_add_qml_module(appTaintedGrail-QuestsTracker
    URI TaintedGrail-QuestsTracker
    VERSION 1.0
    QML_FILES
        src/view/Main.qml
        QML_FILES src/view/QuestsTracker.qml
        QML_FILES src/view/QuestsMap.qml
        QML_FILES src/view/element/TGText.qml
        QML_FILES src/view/theme.js
)

set_target_properties(appTaintedGrail-QuestsTracker PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTaintedGrail-QuestsTracker
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appTaintedGrail-QuestsTracker
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
