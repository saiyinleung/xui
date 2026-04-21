@echo off

echo ============================
echo Building xui (MSVC)
echo ============================

REM --------------------------------------------------
REM Check MSVC environment
REM --------------------------------------------------
where cl >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: cl.exe not found
    echo Please run this from:
    echo "x64 Native Tools Command Prompt for VS"
    exit /b 1
)

REM --------------------------------------------------
REM Clean previous build (optional)
REM --------------------------------------------------
if exist app.exe del app.exe
if exist *.obj del *.obj

REM --------------------------------------------------
REM Compile + Link
REM --------------------------------------------------
cl /nologo /Zi /W3 ^
examples\minimal\main.c ^
src\core.c ^
src\platform\win32.c ^
/Iinclude ^
/Fe:app.exe ^
/link user32.lib gdi32.lib

REM --------------------------------------------------
REM Result
REM --------------------------------------------------
if %errorlevel% equ 0 (
    echo.
    echo Build successful: app.exe
) else (
    echo.
    echo Build failed
    exit /b 1
)
