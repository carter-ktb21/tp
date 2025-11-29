@echo off
REM Twilight Princess Decompilation Build Script
REM This script compiles the decompilation and builds a modified ISO

setlocal enabledelayedexpansion

echo ========================================
echo Twilight Princess ISO Build Script
echo ========================================
echo.

set DECOMP_PATH=%~dp0
REM Remove trailing backslash from DECOMP_PATH
if "%DECOMP_PATH:~-1%"=="\" set DECOMP_PATH=%DECOMP_PATH:~0,-1%
set VANILLA_ISO=%DECOMP_PATH%\orig\GZ2E01\baserom.iso
set OUTPUT_ISO=%~1

REM Set default output path if not provided
if "%OUTPUT_ISO%"=="" (
    set OUTPUT_ISO=%DECOMP_PATH%\output_iso\modified.iso
)

REM Check if baserom.iso exists
if not exist "%VANILLA_ISO%" (
    echo Vanilla ISO not found at: %VANILLA_ISO%
    echo.
    echo Please select your Twilight Princess ISO file...
    echo.

    REM Use PowerShell to show file dialog
    for /f "delims=" %%I in ('powershell -Command "Add-Type -AssemblyName System.Windows.Forms; $dialog = New-Object System.Windows.Forms.OpenFileDialog; $dialog.Filter = 'ISO Files (*.iso;*.gcm)|*.iso;*.gcm|All Files (*.*)|*.*'; $dialog.Title = 'Select Twilight Princess ISO'; if ($dialog.ShowDialog() -eq 'OK') { $dialog.FileName }"') do set SELECTED_ISO=%%I

    if "!SELECTED_ISO!"=="" (
        echo ERROR: No ISO file selected. Exiting.
        exit /b 1
    )

    echo Selected: !SELECTED_ISO!
    echo.
    echo Copying ISO to %VANILLA_ISO%...

    REM Create directory if it doesn't exist
    if not exist "%DECOMP_PATH%\orig\GZ2E01" mkdir "%DECOMP_PATH%\orig\GZ2E01"

    REM Copy the selected ISO
    copy "!SELECTED_ISO!" "%VANILLA_ISO%"
    if errorlevel 1 (
        echo ERROR: Failed to copy ISO
        exit /b 1
    )

    echo ISO copied successfully!
    echo.
) else (
    echo Using existing vanilla ISO: %VANILLA_ISO%
    echo.
)

REM Create output directory if it doesn't exist
for %%F in ("%OUTPUT_ISO%") do set OUTPUT_DIR=%%~dpF
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

echo Output ISO will be: %OUTPUT_ISO%
echo.

REM Close Dolphin emulator if it's running and has the ISO open
echo Checking for running Dolphin emulator...
taskkill /F /IM Dolphin.exe >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo Dolphin closed successfully.
    timeout /t 2 /nobreak >NUL
) else (
    echo No Dolphin instances running.
)
echo.

echo [1/3] Configuring build...
python configure.py --non-matching --map
if errorlevel 1 (
    echo ERROR: Configure failed
    exit /b 1
)

echo.
echo [2/3] Building with ninja...
ninja
if errorlevel 1 (
    echo Hash mismatch detected, cleaning build directory...
    if exist "build\GZ2E01" (
        rd /s /q "build\GZ2E01" 2>nul
    )
    echo Reconfiguring...
    python configure.py --non-matching --map
    if errorlevel 1 (
        echo ERROR: Reconfigure failed
        exit /b 1
    )
    echo Rebuilding...
    ninja
    if errorlevel 1 (
        echo ERROR: Build failed after clean
        exit /b 1
    )
)

echo.
echo [3/3] Building ISO...
python tools\rebuild-decomp-tp.py "%VANILLA_ISO%" "%OUTPUT_ISO%" "%DECOMP_PATH%"
if errorlevel 1 (
    echo ERROR: ISO build failed
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo Output ISO: %OUTPUT_ISO%
echo ========================================
echo.

REM Check if DOLPHIN_PATH is set and valid
if defined DOLPHIN_PATH (
    if exist "%DOLPHIN_PATH%" (
        echo Launching Dolphin...
        start "" "%DOLPHIN_PATH%" -e "%OUTPUT_ISO%"
        goto :eof
    ) else (
        echo Warning: DOLPHIN_PATH is set but file not found.
        echo Prompting for new Dolphin location...
    )
)

REM DOLPHIN_PATH not set or invalid - prompt user to select Dolphin.exe
echo.
echo Dolphin path not configured.
echo Please select your Dolphin.exe file...
echo.

for /f "delims=" %%I in ('powershell -Command "Add-Type -AssemblyName System.Windows.Forms; $dialog = New-Object System.Windows.Forms.OpenFileDialog; $dialog.Filter = 'Dolphin Executable (Dolphin.exe)|Dolphin.exe|All Files (*.*)|*.*'; $dialog.Title = 'Select Dolphin.exe'; if ($dialog.ShowDialog() -eq 'OK') { $dialog.FileName }"') do set SELECTED_DOLPHIN=%%I

if "!SELECTED_DOLPHIN!"=="" (
    echo No Dolphin executable selected. Skipping launch.
    goto :eof
)

echo Selected: !SELECTED_DOLPHIN!
echo Saving DOLPHIN_PATH for future builds...
setx DOLPHIN_PATH "!SELECTED_DOLPHIN!" >NUL 2>&1

echo Launching Dolphin...
start "" "!SELECTED_DOLPHIN!" -e "%OUTPUT_ISO%"

endlocal
