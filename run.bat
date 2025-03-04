@echo off

setlocal
call :setESC

cls

if exist build (
    echo %ESC%[1;33mDeleting existing build folder...%ESC%[0m
    rmdir /s /q build
)

echo %ESC%[1;32mCreate build folder...%ESC%[0m
mkdir build

cd build

cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release -j8

if %errorlevel% equ 0 (
    echo %ESC%[1;32mBuild succeeded. Opening Dotenv.exe ...%ESC%[0m
    cls
    cd Release
    Dotenv.exe
) else (
    echo %ESC%[1;31mBuild failed!%ESC%[0m
)

:setESC

for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
    set ESC=%%b
    exit /B 0
)

endlocal