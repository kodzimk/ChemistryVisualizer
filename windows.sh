COMPILER="gcc"
ARGS="-g -std=c99"
SRC="./src/*.c"
INCLUDE="./include"
BINARY="./lib/x64/"
LIBS="-lSDL2 -lSDL2_ttf -lSDL2_mixer -ldl -lSDL2_net"

# Echo out the platform we are compilng on.
echo "Compiling on ${OSTYPE}"

# Build the compile string
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo ""
elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Compilng on Mac"
    INCLUDE="./include `sdl2-config --clfags`"
    LIBS="`sdl2-config --libs` -lSDL2_ttf -lSDL2_mixer"
    echo ""
elif [[ "$OSTYPE" == "mysys" ]] ; then
    echo "Compiling on Windows(mysys)"
    LIBS="-lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer"
    echo ""
else
    echo "Not sure what operating system to build for?? Trying defaults"
    echo ""
fi

COMPILE="${COMPILER} ${ARGS} ${SRC} -I ${INCLUDE} -o ${BINARY} ${LIBS}"

# Write out the compile string for the user to see
echo ${COMPILE}

# Evaluate the compile string
eval $COMPILE