setlocal
set outpath=..\deps\Win32
cd /D %~dp0..\..\openssl
nmake clean
perl Configure VC-WIN32 no-asm no-shared --prefix="%cd%\%outpath%" --openssldir="%cd%\%outpath%"
nmake
nmake install
endlocal
