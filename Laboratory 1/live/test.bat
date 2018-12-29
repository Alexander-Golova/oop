ECHO ON
SET PROGRAM="%~1"

ECHO for a generation live0
CALL %PROGRAM% testInput\live0.txt > %TEMP%\correctLive0.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctLive0.txt correctTest\correctLive0.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctLive0.txt
ECHO Test for live0 SUCCEED

ECHO for a generation live1
CALL %PROGRAM% testInput\live1.txt > %TEMP%\correctLive1.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctLive1.txt correctTest\correctLive1.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctLive1.txt
ECHO Test for live1 SUCCEED

ECHO for a generation live2
CALL %PROGRAM% testInput\live2.txt > %TEMP%\correctLive2.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctLive2.txt correctTest\correctLive2.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctLive2.txt
ECHO Test for live2 SUCCEED

ECHO for a generation live3
CALL %PROGRAM% testInput\live3.txt > %TEMP%\correctLive3.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctLive3.txt correctTest\correctLive3.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctLive3.txt
ECHO Test for live3 SUCCEED

ECHO for a generation live4
CALL %PROGRAM% testInput\live4.txt > %TEMP%\correctLive4.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctLive4.txt correctTest\correctLive4.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctLive4.txt
ECHO Test for live4 SUCCEED

ECHO for a generation live5
CALL %PROGRAM% testInput\live5.txt > %TEMP%\correctLive5.txt
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\correctLive5.txt correctTest\correctLive5.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\correctLive5.txt
ECHO Test for live5 SUCCEED

ECHO for a generation live6
CALL %PROGRAM% testInput\live6.txt 2> %TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctLive6.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for live6 SUCCEED

echo No params
CALL %PROGRAM%  2>%TEMP%\err.txt
IF NOT ERRORLEVEL 1 GOTO errs
FC %TEMP%\err.txt correctTest\correctNoParams.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for no params SUCCEEDB

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
