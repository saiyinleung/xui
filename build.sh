#!/bin/sh

echo "Building xui..."

OS="$(uname)"

# --------------------------------------------------
# macOS (Clang + Cocoa)
# --------------------------------------------------
if [ "$OS" = "Darwin" ]; then
    echo "Detected macOS"

    clang -g -Wall -Wextra \
    examples/minimal/main.c \
    src/core.c \
    src/platform/macos.m \
    -Iinclude \
    -framework Cocoa \
    -o app

# --------------------------------------------------
# Linux (placeholder for future)
# --------------------------------------------------
elif [ "$OS" = "Linux" ]; then
    echo "Detected Linux (not implemented yet)"
    exit 1

# --------------------------------------------------
# Windows (Git Bash / MinGW)
# --------------------------------------------------
else
    echo "Detected Windows (MinGW)"

    gcc -g -Wall -Wextra \
    examples/minimal/main.c \
    src/core.c \
    src/platform/win32.c \
    -Iinclude \
    -lgdi32 \
    -o app.exe
fi

# --------------------------------------------------
# Result
# --------------------------------------------------

if [ $? -eq 0 ]; then
    echo "Build successful"
else
    echo "Build failed"
fi
