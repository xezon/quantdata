cd /D %~dp0..\..\openssl
nmake clean
perl Configure VC-WIN32 no-asm no-shared --prefix="%cd%\..\deps32" --openssldir="%cd%\..\deps32"
nmake
::nmake test
nmake install
