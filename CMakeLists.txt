cmake_minimum_required(VERSION 3.19)
project(SensorDashboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(SensorDashboard
    # WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.h mainwindow.cpp mainwindow.ui
    sensor.h sensor.cpp
    sensorsimulator.h sensorsimulator.cpp
)

target_link_libraries(SensorDashboard
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(SensorDashboard PRIVATE Qt6::Core)

# include(GNUInstallDirs)

# install(TARGETS SensorDashboard
#     BUNDLE  DESTINATION .
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# )

# qt_generate_deploy_app_script(
#     TARGET SensorDashboard
#     OUTPUT_SCRIPT deploy_script
#     NO_UNSUPPORTED_PLATFORM_ERROR
# )
# install(SCRIPT ${deploy_script})
