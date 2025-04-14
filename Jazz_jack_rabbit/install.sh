#!/bin/bash

# Función para comprobar si un paquete está instalado
is_installed() {
    dpkg -l | grep -q "$1"
}

# Actualizar la lista de paquetes
echo "Actualizando la lista de paquetes..."
sudo apt-get update

# Instalar herramientas de compilación si no están ya instaladas
if ! is_installed "build-essential"; then
    echo "Instalando herramientas de compilación..."
    sudo apt-get install -y build-essential cmake
else
    echo "build-essential ya está instalado."
fi

# Instalar SDL2 y bibliotecas relacionadas si no están ya instaladas
if ! is_installed "libsdl2-dev"; then
    echo "Instalando SDL2 y sus dependencias..."
    sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
else
    echo "SDL2 ya está instalado."
fi

# Instalar dependencias de Qt5 si no están ya instaladas
if ! is_installed "qt5-qmake"; then
    echo "Instalando dependencias de Qt5..."
    sudo apt-get install -y qt5-qmake qtbase5-dev qtchooser qtbase5-dev-tools libqt5widgets5
else
    echo "Qt5 ya está instalado."
fi

# Instalar Google Test (GTest) si no está ya instalado
if ! is_installed "libgtest-dev"; then
    echo "Instalando Google Test..."
    sudo apt-get install -y libgtest-dev
else
    echo "Google Test ya está instalado."
fi

# Instalar YAML-CPP si no está ya instalado
if ! is_installed "libyaml-cpp-dev"; then
    echo "Instalando YAML-CPP..."
    sudo apt-get install -y libyaml-cpp-dev
else
    echo "YAML-CPP ya está instalado."
fi

# Instalar dependencias de hilos si no están ya instaladas
if ! is_installed "libpthread-stubs0-dev"; then
    echo "Instalando dependencias de hilos..."
    sudo apt-get install -y libpthread-stubs0-dev
else
    echo "Las dependencias de hilos ya están instaladas."
fi

# Instalar Python3 si no está ya instalado
if ! is_installed "python3"; then
    echo "Instalando Python3..."
    sudo apt-get install -y python3
else
    echo "Python3 ya está instalado."
fi

# Instalar la librería estándar de C++ si no está ya instalada
if ! is_installed "libstdc++-dev"; then
    echo "Instalando la librería estándar de C++..."
    sudo apt-get install -y libstdc++-dev
else
    echo "La librería estándar de C++ ya está instalada."
fi

# Crear el directorio build si no existe
echo "Creando el directorio 'build'..."
mkdir -p build

# Entrar en el directorio build
echo "Entrando al directorio 'build'..."
cd build

# Ejecutar cmake
echo "Ejecutando cmake ..."
cmake ..

# Ejecutar make para compilar el proyecto
echo "Compilando el proyecto con make..."
make

# Confirmar que todo se haya instalado y compilado correctamente
echo "Instalación y compilación completa. El proyecto ha sido compilado exitosamente."

