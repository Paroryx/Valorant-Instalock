@echo off
setlocal enabledelayedexpansion
set "settings=settings.txt"
for /f "tokens=2 delims=:" %%b in ('findstr /i "agent_id:" "%settings%"') do (
    set "agent_id=%%b"
)
for /f "tokens=2 delims=:" %%a in ('findstr /i "delay:" "%settings%"') do (
    set "delay=%%a"
)
for /f "tokens=2 delims=:" %%c in ('findstr /i "help:" "%settings%"') do (
    set "help=%%c"
)
for /f "tokens=2 delims=:" %%d in ('findstr /i "random:" "%settings%"') do (
    set "random=%%d"
)
if "%help%" == "yes" (
	title Valorant Instalock -help
	Valorant_InstalockV1.exe ?
	pause
	exit
) else if "%random%" == "yes" (
	title Valorant Instalocker %delay%ms -random
	Valorant_InstalockV1.exe 33 %delay%
) else (
	title Valorant Instalock %delay%ms Agent-%agent_id%
	Valorant_InstalockV1.exe %agent_id% %delay%
)
pause