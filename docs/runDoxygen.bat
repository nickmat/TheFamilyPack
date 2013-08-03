cd doxygen
if exist tfp rmdir /S /Q tfp
doxygen tfp.doxy
if exist cal rmdir /S /Q cal
doxygen cal.doxy
if exist rec rmdir /S /Q rec
doxygen rec.doxy
if exist recgui rmdir /S /Q recgui
doxygen recgui.doxy

pause
