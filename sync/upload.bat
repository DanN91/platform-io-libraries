@echo off
REM Navigate to the project root directory
cd /d "%~1"

REM Run PlatformIO build and upload
pio run --target upload

REM Optionally, add additional commands here
REM For example, you can call other scripts or commands
