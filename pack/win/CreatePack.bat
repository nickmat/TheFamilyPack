rem Create the windows installer package.

copy ..\..\build\vc9-working\Release\tfp.exe tfp03.exe
copy ..\..\sample\Example.tfpd
copy ..\..\sample\allged.ged
copy ..\..\sample\royal92.ged
"%ProgramFiles(x86)%\NSIS\makensis.exe" tfp.nsi

del tfp03.exe
del Example.tfpd
