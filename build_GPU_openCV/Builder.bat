@echo off
setlocal enabledelayedexpansion

:MENU
echo ===================================================
echo   OpenCV 4.13 CUDA Compiler Automation Script
echo ===================================================
echo Select your NVIDIA GPU Generation:
echo [1] RTX 40xx Series (Ada Lovelace) : Architecture 8.9
echo [2] RTX 30xx Series (Ampere)       : Architecture 8.6
echo [3] RTX 20xx / GTX 16xx (Turing)   : Architecture 7.5
echo [4] GTX 10xx Series (Pascal)       : Architecture 6.1
echo [5] Custom / Enter manually
echo ===================================================
set /p choice="Enter your choice (1-5): "

if "%choice%"=="1" set "ARCH_BIN=8.9" & goto START_BUILD
if "%choice%"=="2" set "ARCH_BIN=8.6" & goto START_BUILD
if "%choice%"=="3" set "ARCH_BIN=7.5" & goto START_BUILD
if "%choice%"=="4" set "ARCH_BIN=6.1" & goto START_BUILD
if "%choice%"=="5" goto CUSTOM_ARCH

echo Invalid choice. Please try again.
pause
cls
goto MENU

:CUSTOM_ARCH
echo.
set /p ARCH_BIN="Enter your specific CUDA_ARCH_BIN value (e.g., 8.6): "
goto START_BUILD

:START_BUILD
echo.
echo ===================================================
echo Target GPU Compute Capability set to: %ARCH_BIN%
echo Starting CMake Configuration...
echo ===================================================

:: Run configuration targeting a new dedicated 'build_cuda' directory
cmake -B build_cuda -S sources ^
  -G "Visual Studio 17 2022" -A x64 ^
  -D WITH_CUDA=ON ^
  -D CUDA_ARCH_BIN="%ARCH_BIN%" ^
  -D WITH_CUDNN=ON ^
  -D OPENCV_DNN_CUDA=ON ^
  -D OPENCV_EXTRA_MODULES_PATH="opencv_contrib-4.13.0/modules" ^
  -D BUILD_TESTS=OFF ^
  -D BUILD_PERF_TESTS=OFF ^
  -D CMAKE_INSTALL_PREFIX="build_cuda/install"

if %ERRORLEVEL% neq 0 (
    echo.
    echo [ERROR] CMake configuration failed. Check logs above.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ===================================================
echo CMake Configuration Successful. Starting Compilation...
echo WARNING: This will take 30-90 minutes depending on your hardware.
echo ===================================================
pause

:: Compile the binaries across 8 parallel CPU threads
cmake --build build_cuda --config Release --parallel 8

if %ERRORLEVEL% neq 0 (
    echo.
    echo [ERROR] Compilation failed.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo ===================================================
echo Compilation Successful. Installing binaries...
echo ===================================================
:: Isolate the finished headers and libraries into the install prefix directory
cmake --install build_cuda --config Release

echo.
echo ===================================================
echo [SUCCESS] OpenCV with CUDA has finished building!
echo Binaries are located in: opencv4.13\build_cuda\install
echo ===================================================
pause