set(CMAKE_AUTORCC ON)
cmake_minimum_required(VERSION 3.19)
project(calcuLMatrice LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(calcuLMatrice
    WIN32 MACOSX_BUNDLE
    main.cpp
    Calcule.cpp
    Calcule.h
    Calcule.ui
    Matrice.h Matrice.cpp
    ressources.qrc

)

target_link_libraries(calcuLMatrice
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS calcuLMatrice
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET calcuLMatrice
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
