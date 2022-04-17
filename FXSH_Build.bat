@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist BVFPLAY.G1A  del BVFPLAY.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"D:\Programs\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"D:\Programs\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "E:\Code\BVF\bvf_play"
if not exist BVFPLAY.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

