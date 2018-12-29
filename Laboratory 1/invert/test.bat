@ECHO on
SET PROGRAM="%~1"

echo No params
CALL %PROGRAM%  2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for no params SUCCEEDB

echo Invert null matrix
CALL %PROGRAM% testInput\matrix0.txt > %TEMP%\correctMatrix0.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix0.txt correctTest\correctMatrix0.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix0.txt
ECHO Test on invertion the null matrix SUCCEED

echo Invert identity matrix
CALL %PROGRAM% testInput\matrix1.txt > %TEMP%\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix1.txt correctTest\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix1.txt
ECHO Test on invertion the identity matrix SUCCEED

echo Invert the 2th matrix
CALL %PROGRAM% testInput\matrix2.txt 2> %TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctMatrix2.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for the 2th matrix SUCCEED

echo Invert the 3th matrix
CALL %PROGRAM% testInput\matrix3.txt 2> %TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctMatrix3.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for the 3th matrix SUCCEED

echo Invert the 4th matrix
CALL %PROGRAM% testInput\matrix4.txt > %TEMP%\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix4.txt correctTest\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix4.txt
ECHO Test for the 4th matrix SUCCEED

echo Invert the 5th matrix (det = 0)
CALL %PROGRAM% testInput\matrix5.txt > %TEMP%\correctMatrix5.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix5.txt correctTest\correctMatrix5.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix5.txt
ECHO Test for the 5th matrix SUCCEED

echo Invert the 6th matrix
CALL %PROGRAM% testInput\matrix6.txt > %TEMP%\correctMatrix6.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix6.txt correctTest\correctMatrix6.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix6.txt
ECHO Test for the 6th matrix SUCCEED

echo Invert the 7th matrix
CALL %PROGRAM% testInput\matrix7.txt > %TEMP%\correctMatrix7.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix7.txt correctTest\correctMatrix7.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix7.txt
ECHO Test for the 7th matrix SUCCEED


ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1