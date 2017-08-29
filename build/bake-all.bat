bakefile -f gnu -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=gnu -o gnu/makefile tfp.bkl -DNO_UTILS=1 -DNO_DEPS

bakefile -f msvs2008prj -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=vc9 -o vc9/tfp tfp.bkl

bakefile -f msvc -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=nmake -o nmake/tfp.mak tfp.bkl -DNO_DEPS=1

bakefile -f msvc -I %WXWIN%\build\bakefiles\wxpresets -D BUILD_DIR=nmake-dep -o nmake-dep/tfp.mak tfp.bkl

pause