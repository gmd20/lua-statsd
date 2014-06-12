#!/bin/bash
export LD_LIBRARY_PATH=`pwd`
export LUA_PATH="./?.lua;/usr/local/share/lua/5.1/?/?.lua;/usr/local/share/lua/5.1/?.lua"
export LUA_CPATH="./?.so;/usr/local/lib/lua/5.1/?.so"
luajit benchmark.lua
