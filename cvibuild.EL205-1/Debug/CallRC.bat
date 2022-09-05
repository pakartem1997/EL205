@echo "d:\my programs\cvi\cvi2013\sdk\bin\rc.exe" /d _CVI_ /i "d:\my programs\cvi\cvi2013\sdk\include" /fo %2 %1
@"d:\my programs\cvi\cvi2013\sdk\bin\rc.exe" /d _CVI_ /i "d:\my programs\cvi\cvi2013\sdk\include" /fo %2 %1 > Rc.out 2>&1
@if errorlevel 1 goto err
@echo RC complete
@exit 0
:err
@echo RC failed
@exit 1
