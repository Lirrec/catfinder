@echo off

if exist "D:\Epic Games\4.13" (
set ENGINE_DIR=D:\Epic Games\4.13
) else (
set ENGINE_DIR=E:\Epic Games\4.13
)


set PROJECT_NAME=
set PROJECT_DIR=
set PROJECT_FILE=

REM Keep backing up until we find the .uproject file.
REM If we reaches a root directory, it will stop trying.
:Find_ProjectFile
set CURRENTDIR="%cd%"
cd..

if exist *.uproject. (
	for /f %%f in ('dir /b *.uproject') do set PROJECT_FILE=%%f
	if defined PROJECT_FILE goto Found_ProjectFile
	goto Error_NoProjectFile
) else if "%cd%" == %CURRENTDIR% (
	goto Error_NoProjectFile
) else (
	goto Find_ProjectFile
)

:Found_ProjectFile
for %%* in (.) do set PROJECT_NAME=%%~n*
if NOT defined PROJECT_NAME goto Error_NoProjectName

set PROJECT_DIR=%CD%
if NOT defined PROJECT_DIR goto Error_NoProjectDir

@echo PROJECT_NAME is %PROJECT_NAME%
@echo PROJECT_DIR is %PROJECT_DIR%
@echo PROJECT_FILE is %PROJECT_FILE%
@echo ENGINE_DIR is %ENGINE_DIR%
goto Exit

:Error_NoProjectName
echo/ ue4_setvars ERROR: Unable to set project name.
goto Exit

:Error_NoProjectDir
echo/ ue4_setvars ERROR: Unable to set project directory.
goto Exit

:Error_NoProjectFile
echo/ ue4_setvars ERROR: Unable to set project file.
goto Exit

:Exit