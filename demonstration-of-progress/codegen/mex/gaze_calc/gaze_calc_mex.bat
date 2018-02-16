@echo off
set MATLAB=E:\Program Files\MATLAB
set MATLAB_ARCH=win64
set MATLAB_BIN="E:\PROGRAMFILES\MATLAB\bin"
set ENTRYPOINT=mexFunction
set OUTDIR=.\
set LIB_NAME=gaze_calc_mex
set MEX_NAME=gaze_calc_mex
set MEX_EXT=.mexw64
call "E:\PROGRAMFILES\MATLAB\sys\lcc64\lcc64\mex\lcc64opts.bat"
echo # Make settings for gaze_calc > gaze_calc_mex.mki
echo COMPILER=%COMPILER%>> gaze_calc_mex.mki
echo COMPFLAGS=%COMPFLAGS%>> gaze_calc_mex.mki
echo OPTIMFLAGS=%OPTIMFLAGS%>> gaze_calc_mex.mki
echo DEBUGFLAGS=%DEBUGFLAGS%>> gaze_calc_mex.mki
echo LINKER=%LINKER%>> gaze_calc_mex.mki
echo LINKFLAGS=%LINKFLAGS%>> gaze_calc_mex.mki
echo LINKOPTIMFLAGS=%LINKOPTIMFLAGS%>> gaze_calc_mex.mki
echo LINKDEBUGFLAGS=%LINKDEBUGFLAGS%>> gaze_calc_mex.mki
echo MATLAB_ARCH=%MATLAB_ARCH%>> gaze_calc_mex.mki
echo BORLAND=%BORLAND%>> gaze_calc_mex.mki
echo OMPFLAGS= >> gaze_calc_mex.mki
echo OMPLINKFLAGS= >> gaze_calc_mex.mki
echo EMC_COMPILER=lcc64>> gaze_calc_mex.mki
echo EMC_CONFIG=optim>> gaze_calc_mex.mki
"E:\PROGRAMFILES\MATLAB\bin\win64\gmake" -B -f gaze_calc_mex.mk
pause