cd /D %~dp0..\..\openssl
nmake clean
perl Configure VC-WIN64A no-asm no-shared --prefix="%cd%\..\deps64" --openssldir="%cd%\..\deps64"
nmake
::nmake test
nmake install
