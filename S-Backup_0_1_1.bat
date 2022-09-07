set "Ymd=%date:~,4%%date:~5,2%%date:~8,2%"

echo Backup:del

rmdir S:\HP-Archive\CC-PdM_%ymd% /S /Q

md S:\HP-Archive\CC-PdM_%ymd%

xcopy S:\HP-Release\CC-PdM\site\ S:\HP-Archive\CC-PdM_%ymd%\ /E /F

copy S:\HP-Release\CC-PdM\CNAME S:\HP-Archive\CC-PdM_%ymd%\CNAME 

echo Backup:OK

pause