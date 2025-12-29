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

REM Load environment variables from .env file if it exists
if exist "%DECOMP_PATH%\.env" (
    echo Loading configuration from .env...
    for /f "usebackq tokens=1,* delims==" %%a in ("%DECOMP_PATH%\.env") do (
        set line=%%a
        REM Skip empty lines and comments
        if not "!line!"=="" (
            if not "!line:~0,1!"=="#" (
                set %%a=%%b
            )
        )
    )
    echo.
)

REM Set defaults if not provided in .env
if not defined VANILLA_ISO set VANILLA_ISO=%DECOMP_PATH%\orig\GZ2E01\baserom.iso
if not defined OUTPUT_ISO set OUTPUT_ISO=
if not defined LAUNCH set LAUNCH=true
if not defined DUAL_BOOT set DUAL_BOOT=false
if not defined DEVELOPMENT_MODE set DEVELOPMENT_MODE=true

REM Command line argument overrides .env OUTPUT_ISO
if not "%~1"=="" set OUTPUT_ISO=%~1

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
        echo.
        pause
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
        echo.
        pause
        exit /b 1
    )

    echo ISO copied successfully!
    echo.
) else (
    echo Using existing vanilla ISO: %VANILLA_ISO%
    echo.
)

REM Check if Dolphin path is defined and exists
if not defined DOLPHIN_PATH (
    echo Dolphin path not configured.
    echo.
    echo Please select your Dolphin.exe location...
    echo.

    REM Use PowerShell to show file dialog for Dolphin.exe
    for /f "delims=" %%I in ('powershell -Command "Add-Type -AssemblyName System.Windows.Forms; $dialog = New-Object System.Windows.Forms.OpenFileDialog; $dialog.Filter = 'Dolphin Emulator (Dolphin.exe)|Dolphin.exe|All Files (*.*)|*.*'; $dialog.Title = 'Select Dolphin.exe'; if ($dialog.ShowDialog() -eq 'OK') { $dialog.FileName }"') do set SELECTED_DOLPHIN=%%I

    if "!SELECTED_DOLPHIN!"=="" (
        echo WARNING: No Dolphin.exe selected. Launch features will be disabled.
        set LAUNCH=false
    ) else (
        set DOLPHIN_PATH=!SELECTED_DOLPHIN!
        echo Selected: !DOLPHIN_PATH!
        
        REM Save to .env file for future runs
        echo.
        echo Saving Dolphin path to .env file...
        if not exist "%DECOMP_PATH%\.env" (
            echo # Twilight Princess Build Configuration > "%DECOMP_PATH%\.env"
        )
        echo DOLPHIN_PATH=!DOLPHIN_PATH! >> "%DECOMP_PATH%\.env"
        echo Dolphin path saved!
    )
    echo.
) else if not exist "%DOLPHIN_PATH%" (
    echo Dolphin not found at: %DOLPHIN_PATH%
    echo.
    echo Please select your Dolphin.exe location...
    echo.

    REM Use PowerShell to show file dialog for Dolphin.exe
    for /f "delims=" %%I in ('powershell -Command "Add-Type -AssemblyName System.Windows.Forms; $dialog = New-Object System.Windows.Forms.OpenFileDialog; $dialog.Filter = 'Dolphin Emulator (Dolphin.exe)|Dolphin.exe|All Files (*.*)|*.*'; $dialog.Title = 'Select Dolphin.exe'; if ($dialog.ShowDialog() -eq 'OK') { $dialog.FileName }"') do set SELECTED_DOLPHIN=%%I

    if "!SELECTED_DOLPHIN!"=="" (
        echo WARNING: No Dolphin.exe selected. Launch features will be disabled.
        set LAUNCH=false
    ) else (
        set DOLPHIN_PATH=!SELECTED_DOLPHIN!
        echo Selected: !DOLPHIN_PATH!
        
        REM Save to .env file for future runs
        echo.
        echo Updating Dolphin path in .env file...
        REM Update existing DOLPHIN_PATH line
        powershell -Command "(Get-Content '%DECOMP_PATH%\.env') -replace '^DOLPHIN_PATH=.*', 'DOLPHIN_PATH=!DOLPHIN_PATH!' | Set-Content '%DECOMP_PATH%\.env'"
        echo Dolphin path updated!
    )
    echo.
) else (
    echo Using Dolphin at: %DOLPHIN_PATH%
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
    echo Waiting 30 seconds for process to fully terminate...
    timeout /t 30 /nobreak >NUL
) else (
    echo No Dolphin instances running.
)
echo.

echo [1/3] Configuring build...
python configure.py --non-matching --map
if errorlevel 1 (
    echo ERROR: Configure failed
    echo.
    pause
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
        echo.
        pause
        exit /b 1
    )
    echo Rebuilding...
    ninja
    if errorlevel 1 (
        echo ERROR: Build failed after clean
        echo.
        pause
        exit /b 1
    )
)

echo.
echo [3/3] Building ISO...
python tools\rebuild-decomp-tp.py "%VANILLA_ISO%" "%OUTPUT_ISO%" "%DECOMP_PATH%"
if errorlevel 1 (
    echo ERROR: ISO build failed
    echo.
    pause
    exit /b 1
)

echo.
echo ========================================
echo  Build complete!
echo  Output: %OUTPUT_ISO%
echo ========================================
echo.

REM Launch Dolphin if LAUNCH is enabled
if /i "%LAUNCH%"=="true" (
    REM Step 4: Launch Dolphin with dual boot if enabled
    if /i "%DUAL_BOOT%"=="true" (
        echo [4/4] Launching Dolphin in dual boot mode...
        if exist "%DOLPHIN_PATH%" (
            if exist "%VANILLA_ISO%" (
                echo Starting vanilla ISO: %VANILLA_ISO%
                start "" "%DOLPHIN_PATH%" -e "%VANILLA_ISO%"
            ) else (
                echo WARNING: Vanilla ISO not found at %VANILLA_ISO%
            )
            echo Starting modified ISO: %OUTPUT_ISO%
            start "" "%DOLPHIN_PATH%" -e "%OUTPUT_ISO%"
            echo Dolphin launched in dual boot mode.
        ) else (
            echo WARNING: Dolphin not found at %DOLPHIN_PATH%
            echo Please update DOLPHIN_PATH in .env file.
            pause
        )
    ) else (
        echo [4/4] Launching Dolphin...
        if exist "%DOLPHIN_PATH%" (
            start "" "%DOLPHIN_PATH%" -e "%OUTPUT_ISO%"
            echo Dolphin launched with modified ISO.
        ) else (
            echo WARNING: Dolphin not found at %DOLPHIN_PATH%
            echo Please update DOLPHIN_PATH in .env file.
            pause
        )
    )
) else (
    echo Skipping Dolphin launch (LAUNCH=false in .env)
)

echo.
echo Press any key to close...
pause >nul
endlocal
