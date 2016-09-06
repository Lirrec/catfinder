call %~dp0\ue4_setvars.bat

REM "%ENGINE_DIR%/Engine/Binaries/DotNET/UnrealBuildTool.exe" mamv_vr Development Win64 -project="C:/bachelorarbeit/mamv_vr/mamv_vr.uproject" -rocket -editorrecompile -progress -noubtmakefiles

REM "%ENGINE_DIR%\Engine\Binaries\DotNET\UnrealBuildTool.exe" mamv_vr Development Win64 C:\bachelorarbeit\mamv_vr\mamv_vr.uproject -rocket -NoHotReloadFromIDE -ignorejunk -noubtmakefiles


"%ENGINE_DIR%\Engine\Binaries\DotNET\UnrealBuildTool.exe" %PROJECT_NAME%Editor Win64 Development "%PROJECT_DIR%\%PROJECT_FILE%" -rocket
pause