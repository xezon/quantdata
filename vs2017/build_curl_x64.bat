cd /D %~dp0..\..\curl\winbuild
set RTLIBCFG=static
nmake /f Makefile.vc mode=static VC=15 WITH_SSL=static WITH_DEVEL=..\..\deps64 GEN_PDB=yes DEBUG=no
nmake /f Makefile.vc mode=static VC=15 WITH_SSL=static WITH_DEVEL=..\..\deps64 GEN_PDB=yes DEBUG=yes
cd ..
mkdir libc\x64
xcopy builds\libcurl-vc15-x64-debug-static-ssl-static-ipv6-sspi\lib\*.* libc\x64\*.* /Y
xcopy builds\libcurl-vc15-x64-release-static-ssl-static-ipv6-sspi\lib\*.* libc\x64\*.* /Y
