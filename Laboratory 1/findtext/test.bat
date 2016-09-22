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

REM Empty text
CALL %PROGRAM% testInput\empty.txt "my" > %TEMP%\empty.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\empty.txt correctTest\correctEmpty.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\empty.txt
ECHO Test on find in empty file SUCCEED

REM Missing file
CALL %PROGRAM% testInput\missing.txt "my" > %TEMP%\missing.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\missing.txt correctTest\correctMissing.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\missing.txt
ECHO Test on find in missing file SUCCEED

REM We are testing for an empty searching string
CALL %PROGRAM% testInput\multiline.txt "" > %TEMP%\multiline.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\multiline.txt correctTest\correctEmptyString.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\multiline.txt
ECHO Test on empty searching string SUCCEED

REM Text not found
CALL %PROGRAM% testInput\multiline.txt "string" > %TEMP%\multiline.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\multiline.txt correctTest\correctTextNotFound.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\multiline.txt
ECHO Test "text not found" SUCCEED

REM Text several occurrences
CALL %PROGRAM% testInput\severalOccurrences.txt "a" > %TEMP%\severalOccurrences.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\severalOccurrences.txt correctTest\correctSeveralOccurrences.txt
IF NOT ERRORLEVEL 1 GOTO errs
DEL %TEMP%\severalOccurrences.txt
ECHO Test several occurrences SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1
