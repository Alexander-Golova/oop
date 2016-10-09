@ECHO on
SET PROGRAM="%~1"

echo Invert identity matrix
CALL %PROGRAM% testInput\matrix1.txt>%TEMP%\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO err
FC %TEMP%\correctMatrix1.txt correctTest\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\correctMatrix1.txt
ECHO Test on invertion the identity matrix SUCCEED

:err
ECHO TEST FAILED
EXIT 1
