if exist vc9-dep del vc9-dep\*.vcproj
bakefile -f msvs2008prj -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=vc9-dep -o vc9-dep/tfp tfp.bkl
pvc -v -I vc9-dep\tfp_rec.vcproj -P tfp_rec-vcproj-processed-files.txt -O vc9-dep\tfp_rec.vcproj
pvc -v -I vc9-dep\tfp_tfp.vcproj -P tfp_tfp-vcproj-processed-files.txt -O vc9-dep\tfp_tfp.vcproj

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
