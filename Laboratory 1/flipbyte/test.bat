@ECHO ON
SET PROGRAM="%~1"

ECHO No params
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for no params SUCCEED

ECHO Invalid param
CALL %PROGRAM% "a" 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctInvalidParam.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for invalid param SUCCEED

ECHO Negative number
CALL %PROGRAM% "-1" 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctNegativeNumber.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for negative number SUCCEED

ECHO Too large number
CALL %PROGRAM% "256" 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctTooLargeNumber.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for too large number SUCCEED

ECHO for flipbyte(0)
CALL %PROGRAM% 0 > %TEMP%\0.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\0.txt correctTest\correct0.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\0.txt
ECHO Test for flipbyte(0) SUCCEED

ECHO for flipbyte(255)
CALL %PROGRAM% 255 > %TEMP%\255.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\255.txt correctTest\correct255.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\255.txt
ECHO Test for flipbyte(255) SUCCEED

ECHO for flipbyte(105)
CALL %PROGRAM% 105 > %TEMP%\105.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\105.txt correctTest\correct105.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\105.txt
ECHO Test for flipbyte(105) SUCCEED

ECHO for flipbyte(19)
CALL %PROGRAM% 19 > %TEMP%\19.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\19.txt correctTest\correct19.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\19.txt
ECHO Test for flipbyte(19) SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
