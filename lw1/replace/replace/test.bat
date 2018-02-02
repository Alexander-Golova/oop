@ECHO OFF

set PROGRAM="%~1"

REM invalid arguments
CALL %PROGRAM% 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctInvalidArguments.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\err.txt
ECHO Test for invalid arguments SUCCEED

REM search string is empty
CALL %PROGRAM% "inputTest\severalOccurrences.txt" %TEMP%\emptySearchString.txt "" "papa" 2>%TEMP%\err.txt
IF NOT ERRORLEVEL 0 GOTO errs
FC %TEMP%\err.txt correctTest\correctEmptySearchString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\emptySearchString.txt
DEL %TEMP%\err.txt
ECHO Test for empty search string SUCCEED

REM replace string is empty
CALL %PROGRAM% "inputTest\severalOccurrences.txt" %TEMP%\emptyReplaceString.txt "mama" ""
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\emptyReplaceString.txt correctTest\correctEmptyReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\emptyReplaceString.txt
ECHO Test for empty replace string SUCCEED

REM replace "mama" to "papa"
CALL %PROGRAM% "inputTest\severalOccurrences.txt" %TEMP%\papaReplaceString.txt "mama" "papa"
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\papaReplaceString.txt correctTest\correctPapaReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\papaReplaceString.txt
ECHO Test for replace "mama" to "papa" SUCCEED

REM replace "ma" to "mama"
CALL %PROGRAM% "inputTest\severalOccurrences.txt" %TEMP%\mamamamaReplaceString.txt "ma" "mama"
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\mamamamaReplaceString.txt correctTest\correctMamamamaReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\mamamamaReplaceString.txt
ECHO Test for replace "ma" to "mama" SUCCEED

REM replace "1231234" to "pi"
CALL %PROGRAM% "inputTest\number.txt" %TEMP%\piReplaceString.txt "1231234" "pi"
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\piReplaceString.txt correctTest\correctPiReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\piReplaceString.txt
ECHO Test for replace "1231234" to "pi" SUCCEED

REM replace "poni" to "koni"
CALL %PROGRAM% "inputTest\multiline.txt" %TEMP%\koniReplaceString.txt "pony" "koni"
IF ERRORLEVEL 1 GOTO errs
FC %TEMP%\koniReplaceString.txt correctTest\correctKoniReplaceString.txt
IF ERRORLEVEL 1 GOTO errs
DEL %TEMP%\koniReplaceString.txt
ECHO Test for replace "poni" to "koni" SUCCEED

ECHO ALL TESTS WERE SUCCEED
EXIT 0

:errs
ECHO TEST FAILED
EXIT 1