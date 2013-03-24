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
mkdir tfp\build\vc9
mkdir tfp\include
mkdir tfp\include\cal
mkdir tfp\include\rec
mkdir tfp\include\rg
mkdir tfp\include\wx
mkdir tfp\sample
mkdir tfp\src
mkdir tfp\src\cal
mkdir tfp\src\img
mkdir tfp\src\img\cht
mkdir tfp\src\img\ed
mkdir tfp\src\rec
mkdir tfp\src\rec\generated
mkdir tfp\src\rg
mkdir tfp\src\tfp
mkdir tfp\src\tfp\generated
mkdir tfp\tests
mkdir tfp\tests\cal
mkdir tfp\tests\rec
mkdir tfp\utils
mkdir tfp\utils\cal
mkdir tfp\utils\doccore
mkdir tfp\utils\file2cpp

copy ..\..\ReadMe.txt tfp\ReadMe.txt > nul
copy ..\..\src\gpl3.txt tfp\License.txt > nul
copy ..\..\3rdparty\wxsqlite3\*.* tfp\3rdparty\wxsqlite3 > nul
copy ..\..\build\build.txt tfp\build > nul
copy ..\..\build\gnu\*.* tfp\build\gnu > nul
copy ..\..\build\nmake\*.* tfp\build\nmake > nul
copy ..\..\build\vc9\*.* tfp\build\vc9 > nul
copy ..\..\include\*.* tfp\include > nul
copy ..\..\include\cal\*.* tfp\include\cal > nul
copy ..\..\include\rec\*.* tfp\include\rec > nul
copy ..\..\include\rg\*.* tfp\include\rg > nul
copy ..\..\include\wx\*.* tfp\include\wx > nul
copy ..\..\sample\Example.tfpd tfp\sample > nul
copy ..\..\sample\allged.ged tfp\sample > nul
copy ..\..\src\dummy.cpp tfp\src > nul
copy ..\..\src\webviewfshandler.* tfp\src > nul
copy ..\..\src\cal\*.* tfp\src\cal > nul
copy ..\..\src\img\*.* tfp\src\img > nul
copy ..\..\src\img\cht\*.* tfp\src\img\cht > nul
copy ..\..\src\img\ed\*.* tfp\src\img\ed > nul
copy ..\..\src\rec\*.* tfp\src\rec > nul
copy ..\..\src\rec\generated\*.* tfp\src\rec\generated > nul
copy ..\..\src\rg\*.* tfp\src\rg > nul
copy ..\..\src\tfp\*.* tfp\src\tfp > nul
copy ..\..\src\tfp\generated\*.* tfp\src\tfp\generated > nul
copy ..\..\tests\*.* tfp\tests > nul
copy ..\..\tests\cal\*.* tfp\tests\cal > nul
copy ..\..\tests\rec\*.* tfp\tests\rec > nul
copy ..\..\utils\cal\*.* tfp\utils\cal > nul
copy ..\..\utils\doccore\dcMain.cpp tfp\utils\doccore > nul
copy ..\..\utils\file2cpp\*.* tfp\utils\file2cpp > nul

7za a -r tfp.zip tfp > ziplist.txt
dtou -v -I tfp -E .;c;ci;cpp;css;f2c;fbp;h;htm;sql;txt;xpm > convert-rpt.txt
7za a -r tfp.tar tfp > nul
7za a -r tfp.gz tfp.tar > nul
del tfp.tar
rmdir /S /Q tfp
