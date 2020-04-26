#!/bin/sh

cd build/

function help {
    printf "run.sh [action]\n\n"

    printf "%10s  %s\n" "config" "configure cmake in build folder"
    printf "%10s  %s\n" "configure" ""
    printf "%10s  %s\n" "shader" "copy shaders from ./shaders to executable"
    printf "%10s  %s\n" "shaders" ""
    printf "%10s  %s\n" "build" "build multik without configuration and coping chades"
    printf "%10s  %s\n" "multik" ""
    printf "\n%s\n" "runs multik without additional actions"

    exit 0
}

case $1 in
    "config" | "configure") 
        rm * -rf
        cmake ..
        cmake --build . --target copy_shaders
        cmake --build . --target build_multik_shaders
        ;;
    "shader" | "shaders")
        cmake --build . --target copy_shaders ;;
    "build" | "multik")
        cmake --build . ;;
    "-h" | "help") help ;;
esac

cd multik/
./multik.exe