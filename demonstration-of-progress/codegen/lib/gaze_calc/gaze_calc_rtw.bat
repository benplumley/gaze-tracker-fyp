@echo off

set MATLAB=E:\Program Files\MATLAB

cd .

if "%1"=="" (E:\Program Files\MATLAB\bin\win64\gmake -f gaze_calc_rtw.mk all) else (E:\Program Files\MATLAB\bin\win64\gmake -f gaze_calc_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
