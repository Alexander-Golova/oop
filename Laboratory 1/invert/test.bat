@ECHO on
SET PROGRAM="%~1"

REM No params
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO err
DEL %TEMP%\err.txt
ECHO Test "no params" SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
