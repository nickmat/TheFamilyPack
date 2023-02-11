@echo off
if exist rmdir /S /Q tfp
if exist tfp.zip del tfp.zip
if exist tfp.gz del tfp.gz

mkdir tfp
mkdir tfp\3rdparty
mkdir tfp\3rdparty\wxsqlite3
mkdir tfp\build
mkdir tfp\build\gnu
mkdir tfp\build\nmake
mkdir tfp\build\vc19
mkdir tfp\include
mkdir tfp\include\cal
mkdir tfp\include\catch2
mkdir tfp\include\hxml5
mkdir tfp\include\rec
mkdir tfp\include\rg
mkdir tfp\include\wx
mkdir tfp\sample
mkdir tfp\src
mkdir tfp\src\cal
mkdir tfp\src\hxml5
mkdir tfp\src\img
mkdir tfp\src\img\cht
mkdir tfp\src\img\ed
mkdir tfp\src\rc
mkdir tfp\src\rec
mkdir tfp\src\rec\embed
mkdir tfp\src\rg
mkdir tfp\src\rg\fb
mkdir tfp\src\tfp
mkdir tfp\src\tfp\embed
mkdir tfp\test
mkdir tfp\test\csv1
mkdir tfp\test\csv1\ass1
mkdir tfp\test\csv1\ass1\image
mkdir tfp\test\csv1\image
mkdir tfp\test\ru
mkdir tfp\test\tdb
mkdir tfp\tests
mkdir tfp\tests\cal
mkdir tfp\tests\rec
mkdir tfp\utils
mkdir tfp\utils\cal
mkdir tfp\utils\cdb
mkdir tfp\utils\cdm
mkdir tfp\utils\doccore

copy ..\..\readme.md tfp\readme.md > nul
copy ..\..\src\gpl3.txt tfp\License.txt > nul
copy ..\..\3rdparty\wxsqlite3\*.* tfp\3rdparty\wxsqlite3 > nul
copy ..\..\build\build.txt tfp\build > nul
copy ..\..\build\gnu\*.* tfp\build\gnu > nul
copy ..\..\build\nmake\*.* tfp\build\nmake > nul
copy ..\..\build\vc19\*.* tfp\build\vc19 > nul
copy ..\..\include\cal\*.* tfp\include\cal > nul
copy ..\..\include\catch2\*.* tfp\include\catch2 > nul
copy ..\..\include\hxml5\*.* tfp\include\hxml5 > nul
copy ..\..\include\rec\*.* tfp\include\rec > nul
copy ..\..\include\rg\*.* tfp\include\rg > nul
copy ..\..\include\wx\*.* tfp\include\wx > nul

rem ================[ Examples ]====================
copy ..\..\sample\Example.tfpd tfp\sample > nul
copy ..\..\sample\allged.ged tfp\sample > nul
copy ..\..\sample\royal92.ged tfp\sample > nul

copy ..\..\src\dummy.cpp tfp\src > nul
copy ..\..\src\cal\*.* tfp\src\cal > nul
copy ..\..\src\hxml5\*.* tfp\src\hxml5 > nul
copy ..\..\src\img\*.* tfp\src\img > nul
copy ..\..\src\img\cht\*.* tfp\src\img\cht > nul
copy ..\..\src\img\ed\*.* tfp\src\img\ed > nul
copy ..\..\src\rc\*.* tfp\src\rc > nul
copy ..\..\src\rec\*.* tfp\src\rec > nul
copy ..\..\src\rec\embed\*.* tfp\src\rec\embed > nul
copy ..\..\src\rg\*.* tfp\src\rg > nul
copy ..\..\src\rg\fb\*.* tfp\src\rg\fb > nul
copy ..\..\src\tfp\*.* tfp\src\tfp > nul
copy ..\..\src\tfp\embed\*.* tfp\src\tfp\embed > nul
rem Use test\*.??? to avoid copying *.tfpd files
copy ..\..\test\*.??? tfp\test > nul
copy ..\..\test\csv1\*.* tfp\test\csv1 > nul
copy ..\..\test\csv1\ass1\*.* tfp\test\csv1\ass1 > nul
copy ..\..\test\csv1\ass1\image\*.* tfp\test\csv1\ass1\image > nul
copy ..\..\test\csv1\image\*.* tfp\test\csv1\image > nul
copy ..\..\test\ru\*.* tfp\test\ru > nul
copy ..\..\test\tdb\*.* tfp\test\tdb > nul
rem Remove temporary databases created during test runs.
if exist ..\..\tests\*.tfpd del ..\..\tests\*.tfpd
copy ..\..\tests\*.* tfp\tests > nul
copy ..\..\tests\cal\*.* tfp\tests\cal > nul
copy ..\..\tests\rec\*.* tfp\tests\rec > nul
copy ..\..\utils\cal\*.* tfp\utils\cal > nul
copy ..\..\utils\cdb\*.* tfp\utils\cdb > nul
copy ..\..\utils\cdm\*.* tfp\utils\cdm > nul
copy ..\..\utils\doccore\dcMain.cpp tfp\utils\doccore > nul

7zr a -r tfp.zip tfp > ziplist.txt
dtou -v -I tfp -E .;c;ci;cpp;css;f2c;fbp;h;htm;sql;txt;xpm > convert-rpt.txt
7zr a -r tfp.tar tfp > nul
7zr a -r tfp.gz tfp.tar > nul
del tfp.tar
rmdir /S /Q tfp

pause
