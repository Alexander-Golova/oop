@ECHO OFF
SET PROGRAM="%~1"

REM Find the text in multiline file
CALL %PROGRAM% testInput\multiline.txt "my" > %TEMP%\multiline.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\multiline.txt correctTest\correctMultiline.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\multiline.txt
ECHO Test on find in multiline file SUCCEED

REM No params
CALL %PROGRAM%  2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for no params SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
