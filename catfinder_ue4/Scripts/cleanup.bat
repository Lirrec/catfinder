REM Deletes all Intermediate Directories

call %~dp0\ue4_setvars.bat

if NOT defined PROJECT_DIR goto ERROR

echo "Deleting Intermediate Files and Dirs"

rmdir /S /Q "%PROJECT_DIR%\Intermediate"
rmdir /S /Q "%PROJECT_DIR%\Saved"
rmdir /S /Q "%PROJECT_DIR%\Binaries"
rmdir /S /Q "%PROJECT_DIR%\Build\Receipts"

rem rmdir /S /Q "%PROJECT_DIR%\Plugins\MamvClientPlugin\Binaries"
rem rmdir /S /Q "%PROJECT_DIR%\Plugins\MamvClientPlugin\Intermediate"

del  /Q "%PROJECT_DIR%\%PROJECT_NAME%.sdf"
del  /Q "%PROJECT_DIR%\%PROJECT_NAME%.sln"
del  /Q "%PROJECT_DIR%\%PROJECT_NAME%.v14.suo"

echo "Regenerating Visual Studio Project Files"

REM "\Engine\Build\BatchFiles\RocketGenerateProjectFiles.bat" -CurrentPlatform -Game mamv_vr  "%PROJECT_DIR%\%PROJECT_FILE%"
echo "Project file: %PROJECT_DIR%\%PROJECT_FILE%"

REM "%ENGINE_DIR%\Engine\Binaries\DotNET\UnrealBuildTool.exe"  -cmakefile -project="%PROJECT_DIR%\%PROJECT_FILE%" -game -CurrentPlatform -OnlyPublic -NoShippingConfigs
"%ENGINE_DIR%\Engine\Binaries\DotNET\UnrealBuildTool.exe"  -ProjectFiles -project="%PROJECT_DIR%\%PROJECT_FILE%" -game -CurrentPlatform -OnlyPublic -NoShippingConfigs
echo "Done.."
pause
goto DONE

ERROR:
echo "PROJECT_DIR NOT SET!!"

DONE:
pause