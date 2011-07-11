@echo off
call config.bat

set progfiles=%ProgramFiles%
if exist "%ProgramFiles(x86)%" set progfiles=%ProgramFiles(x86)%

rem start "" /b "%progfiles%\Microsoft Device Emulator\1.0\DeviceEmulator.exe" @roadrover.decfg
rem start "" /b "%progfiles%\Microsoft Device Emulator\1.0\DeviceEmulator.exe" roadrover.bin /vmname "RoadRover" /memsize %MemSize% /sharedfolder %StorageCard% /video %Video%
start "" /b "%progfiles%\Microsoft Device Emulator\1.0\DeviceEmulator.exe"
