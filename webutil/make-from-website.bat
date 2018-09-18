@echo off

echo Run WebPageLayout

xcopy /Q /S /I /Y ..\website ..\web-new

wpl --version

wpl --source ../website --target .. --layout layout.json

pause
