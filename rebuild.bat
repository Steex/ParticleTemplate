@echo off
call "%RB5_ROOT%/update.bat" nopause
call "%RB5_ROOT%/dllcopy.bat" nopause

echo *** Build the game ***
echo.
devenv.com /nologo /rebuild "release|windows" "src/template.sln"

pause