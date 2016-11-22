@echo off
cls
setlocal enabledelayedexpansion

rem Check for obvious problems
if [%1]==[] goto ShowUse
if not exist sketches\%1 goto NotFound

echo Compiling sketch %1 to bin\%1.exe...

rem Generate list of files to compile
set FileList=
dir main.cpp emulate\*.c emulate\*.cpp sketches\%1\*.c sketches\%1\*.cpp /ON /B /S 2>nul > ~files~.tmp
for /F "usebackq delims=" %%I in (`type ~files~.tmp`) do (
   set RelativePath=%%~I
   set RelativePath=!RelativePath:%cd%=!
   set RelativePath=!RelativePath:~1!
   set RelativePath=!RelativePath:\=/!
   set FileList=!FileList! !RelativePath!
)
del ~files~.tmp
set FileList=!FileList:~1!

rem Compile all the files
gcc !FileList! -D__EMULATING__ -DGAMENAME=\"%1\" -DSKETCH=\"../sketches/%1/%1.ino\" -IC:\MinGW\msys\1.0\include -LC:\MinGW\msys\1.0\lib\ -fpermissive -lstdc++ -std=gnu++11 -O2 -g -lsdl2 -Iemulate -include emulate/emulate.h -obin/%1.exe

rem Check for error
if errorlevel 1 goto CompilationFailed

rem Remove unnecessary information from the executable
strip bin/%1.exe

rem Check for error
if errorlevel 1 goto PostFailed

rem Report success, ask to run
set /P c=Compilation appears successful, run [y]? 
if /I "%c%" EQU "y" goto :RunProgram

goto EndOfProgram

:ShowUse

echo Please specify which sketch in the sketches folder to compile, like this:
echo   make mycoolgame

goto EndOfProgram

:NotFound

echo There is no sketch named %1 in the sketches folder

goto EndOfProgram

:RunProgram

rem Run compiled program
echo Running...
bin\%1.exe

:PostFailed

:CompilationFailed

:EndOfProgram

endlocal
