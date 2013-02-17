if exist vc9-ex del vc9-ex\*.vcproj
bakefile -f msvs2008prj -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=vc9-ex -o vc9-ex/tfp tfp.bkl -D INC_NON_SVN=1
pvc -v -I vc9-ex\tfp_rec.vcproj -P tfp_rec-vcproj-processed-files.txt -O vc9-ex\tfp_rec.vcproj
pvc -v -I vc9-ex\tfp_tfp.vcproj -P tfp_tfp-vcproj-processed-files.txt -O vc9-ex\tfp_tfp.vcproj

@echo off
if '%1' == 'cont' goto end
pause
:end
echo on
