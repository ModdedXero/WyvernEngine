pushd %~dp0
call %WYVERN_DIR%\vendor\premake\premake5.exe vs2022 --projname=RougeForest
popd

pause