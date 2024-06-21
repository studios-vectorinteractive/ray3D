@echo off
REM Check if python is installed or not
echo Checking Dependencies....
python --version >nul 2>&1
if %errorlevel% neq 0 (
	echo Python is not installed on this system, Please install Python and try again!
	exit /b 1
) else (
	echo Python...[OK]
)

echo setting up the project files...
python setup.py
echo generating project files...
ext-bin\premake5.exe vs2022
pause