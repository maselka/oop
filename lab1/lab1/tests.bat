echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% empty.txt "%TEMP%\output.txt" || goto err
fc empty.txt %TEMP%\output.txt || goto err
echo test 1 passed

REM Copy non empty file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" || goto err
fc NonEmptyFile.txt %TEMP%\output.txt || goto err
echo test 2 passed

REM Copy missing file
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo test 3 passed

REM call programm withoy
%MyProgram% MissingFile.txt && goto err
echo test 4 passed

REM call programm with 
%MyProgram% && goto err
echo test 5 passed

echo All tests passed
exit /B 0

:err
echo Test failed
exit /B 1