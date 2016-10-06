@ECHO OFF
SET PROGRAM="%~1"

REM Invert identity matrix
CALL %PROGRAM% testInput\matrix1.txt > %TEMP%\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix1.txt correctTest\correctMatrix1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix1.txt
ECHO Test on invertion the identity matrix SUCCEED

REM Invert null matrix
CALL %PROGRAM% testInput\matrix0.txt > %TEMP%\correctMatrix0.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix0.txt correctTest\correctMatrix0.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix0.txt
ECHO Test on invertion the null matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix2.txt > %TEMP%\correctMatrix2.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix2.txt correctTest\correctMatrix2.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix2.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix3.txt > %TEMP%\correctMatrix3.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix3.txt correctTest\correctMatrix3.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix3.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix4.txt > %TEMP%\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix4.txt correctTest\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix4.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix4.txt > %TEMP%\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix4.txt correctTest\correctMatrix4.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix4.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix5.txt > %TEMP%\correctMatrix5.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix5.txt correctTest\correctMatrix5.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix5.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix6.txt > %TEMP%\correctMatrix6.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix6.txt correctTest\correctMatrix6.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix6.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix7.txt > %TEMP%\correctMatrix7.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix7.txt correctTest\correctMatrix7.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix7.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix8.txt > %TEMP%\correctMatrix8.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix8.txt correctTest\correctMatrix8.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix8.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix9.txt > %TEMP%\correctMatrix9.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix9.txt correctTest\correctMatrix9.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix9.txt
ECHO Test on invertion matrix SUCCEED

REM Invert matrix
CALL %PROGRAM% testInput\matrix10.txt > %TEMP%\correctMatrix10.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctMatrix10.txt correctTest\correctMatrix10.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctMatrix10.txt
ECHO Test on invertion matrix SUCCEED

REM No params
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for no params SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
