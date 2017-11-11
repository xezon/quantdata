cd /D %~dp0..\..\curl\winbuild
set RTLIBCFG=static
nmake /f Makefile.vc mode=static VC=15 WITH_SSL=static WITH_DEVEL=..\..\deps32 GEN_PDB=yes DEBUG=no
nmake /f Makefile.vc mode=static VC=15 WITH_SSL=static WITH_DEVEL=..\..\deps32 GEN_PDB=yes DEBUG=yes
cd ..
mkdir libc\Win32
xcopy builds\libcurl-vc15-x86-debug-static-ssl-static-ipv6-sspi\lib\*.* libc\Win32\*.* /Y
xcopy builds\libcurl-vc15-x86-release-static-ssl-static-ipv6-sspi\lib\*.* libc\Win32\*.* /Y
