cd win
call CreatePack.bat
cd ..
copy win\tfp-setup.exe tfp_0-3-0-1-1_setup.exe
del win\tfp-setup.exe

cd src
call create-source.bat
cd ..
copy src\tfp.gz tfp_0-3-0-1-1_src.gz
del src\tfp.gz
copy src\tfp.zip tfp_0-3-0-1-1_src.zip
del src\tfp.zip

pause