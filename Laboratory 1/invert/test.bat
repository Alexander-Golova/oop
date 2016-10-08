@ECHO on
SET PROGRAM="%~1"

echo Invert identity matrix
CALL %PROGRAM% testInput\matrix1.txt > %TEMP%\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix1.txt correctTest\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix1.txt
ECHO Test on invertion the identity matrix SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
