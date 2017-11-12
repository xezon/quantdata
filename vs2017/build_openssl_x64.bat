setlocal
set outpath=..\deps\x64
cd /D %~dp0..\..\openssl
nmake clean
perl Configure VC-WIN64A no-asm no-shared --prefix="%cd%\%outpath%" --openssldir="%cd%\%outpath%"
nmake
nmake install
endlocal
