set ZBS=C:\ZeroBraneStudioEduPack-0.60-win32
set LUA_PATH=./?.lua;%ZBS%/lualibs/?/?.lua;%ZBS%/lualibs/?.lua
set LUA_CPATH=./?.dll;%ZBS%/bin/?.dll;%ZBS%/bin/clibs/?.dll
luajit.exe benchmark.lua
pause

rem  ================ linux下面的办法 ===========
rem export ZBS=/opt/zbstudio
rem export LUA_PATH="./?.lua;$ZBS/lualibs/?/?.lua;$ZBS/lualibs/?.lua"
rem export LUA_CPATH="./?.dll;$ZBS/bin/linux/x86/?.dll;$ZBS/bin/linux/x86/clibs/?.dll"
rem ./myapplication
