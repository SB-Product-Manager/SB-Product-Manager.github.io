echo Release:Delete Old

cd S:\HP-Release\CC-PdM
s:
rmdir S:\HP-Release\CC-PdM\docs /s/q

echo Release:Copy Start

xcopy S:\HP-compiling\pelican\test\output\  S:\HP-Release\CC-PdM\docs\ /E /F
copy S:\HP-Release\CC-PdM\CNAME S:\HP-Release\CC-PdM\docs\CNAME 

echo Release:Copy End
pause