cmake_minimum_required(VERSION 3.5)

project(jazzjackrabbit
        DESCRIPTION "TP Final para la materia Taller de Programacion I - 1C2024"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Incluir SDL2 correctamente
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D_POSIX_C_SOURCE=200809L")

# Añadir el directorio de SDL2 en Linux (esto es clave)
include_directories(/usr/include/SDL2)

# Si estás en Mac, agregar flags específicos para OSX
if (APPLE)
    message("Estoy en OSX")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer")
endif()

# Configuración para obtener GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

# Evitar sobrescribir configuración de compilador en Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Habilitar pruebas
enable_testing()

# Subdirectorios
add_subdirectory(client_src)
add_subdirectory(server_src)
add_subdirectory(editor_src)
add_subdirectory(client_src/setupscreen)
add_subdirectory(editor_src/setupscreen_editor)

# Agregar ejecutables
add_executable(server
    server_src/main.cpp
)

find_package(Qt5Widgets REQUIRED)

add_executable(client
    client_src/main.cpp
)

add_executable(editor
    editor_src/main.cpp
)

add_executable(prueba
    tests_src/tests.cpp
    tests_src/protocolo_cliente_test.cpp
)

# Vincular bibliotecas específicas
target_link_libraries(client client_lib Qt5::Widgets setupscreen SDL2 SDL2_image pthread SDL2_ttf -lSDL2_mixer)
target_link_libraries(editor editor_lib Qt5::Widgets setupscreen_editor SDL2 SDL2_image pthread SDL2_ttf -lSDL2_mixer)
target_link_libraries(server server_lib pthread yaml-cpp)
target_link_libraries(prueba gtest_main gmock_main server_lib client_lib yaml-cpp)

# Configuración de pruebas con GoogleTest
include(GoogleTest)
gtest_discover_tests(prueba)
