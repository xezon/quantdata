cd /D %~dp0..\..\curl\winbuild
set RTLIBCFG=static
setlocal
set outpath=..\..\deps\x64
nmake /f Makefile.vc mode=static VC=15 WITH_SSL=static WITH_DEVEL=%outpath% GEN_PDB=yes DEBUG=no
nmake /f Makefile.vc mode=static VC=15 WITH_SSL=static WITH_DEVEL=%outpath% GEN_PDB=yes DEBUG=yes
xcopy ..\builds\libcurl-vc15-x64-debug-static-ssl-static-ipv6-sspi\*.* %outpath%\*.* /sy
xcopy ..\builds\libcurl-vc15-x64-release-static-ssl-static-ipv6-sspi\*.* %outpath%\*.* /sy
endlocal
