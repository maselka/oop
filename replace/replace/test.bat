echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM replace string from empty file
%MyProgram% empty.txt "%TEMP%\output.txt" 11 22 || goto err
fc empty.txt %TEMP%\output.txt || goto err
echo test 1 passed

REM call programm without 1 argument
%MyProgram% MissingFile.txt "%TEMP%\output.txt" 11 && goto err
echo test 2 passed

REM call programm without 2 argument
%MyProgram% MissingFile.txt 11 && goto err
echo test 3 passed

REM call programm without 3 argument
%MyProgram% MissingFile.txt && goto err
echo test 4 passed

REM call programm without arguments 
%MyProgram% && goto err
echo test 5 passed

echo All tests passed
exit /B 0

:err
echo Test failed
exit /B 1