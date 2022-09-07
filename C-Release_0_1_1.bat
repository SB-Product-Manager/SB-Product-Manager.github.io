echo Release:Delete Old

cd C:\HP-Release\CC-PdM
C:
rmdir C:\HP-Release\CC-PdM\docs /s/q

echo Release:Copy Start

xcopy C:\HP-compiling\pelican\test\output\  C:\HP-Release\CC-PdM\docs\ /E /F
copy C:\HP-Release\CC-PdM\CNAME C:\HP-Release\CC-PdM\docs\CNAME 

echo Release:Copy End
pause