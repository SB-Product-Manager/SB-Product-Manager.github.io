set "Ymd=%date:~,4%%date:~5,2%%date:~8,2%"

echo Backup:del

rmdir C:\HP-Archive\CC-PdM_%ymd% /S /Q

md C:\HP-Archive\CC-PdM_%ymd%

xcopy C:\HP-Release\CC-PdM\site\ C:\HP-Archive\CC-PdM_%ymd%\ /E /F

copy C:\HP-Release\CC-PdM\CNAME C:\HP-Archive\CC-PdM_%ymd%\CNAME 

echo Backup:OK

pause