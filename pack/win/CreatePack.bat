rem Create the windows installer package.

copy ..\..\build\vc-working\Release\tfp.exe tfp03.exe
copy ..\..\sample\Example.tfpd
copy ..\..\sample\allged.ged
copy ..\..\sample\royal92.ged
"%ProgramFiles(x86)%\NSIS\makensis.exe" tfp.nsi

del tfp03.exe
del Example.tfpd
del allged.ged
del royal92.ged
