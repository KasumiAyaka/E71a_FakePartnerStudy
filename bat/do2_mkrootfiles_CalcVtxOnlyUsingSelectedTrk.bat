if "%1"=="" goto :usage

set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\mac
set datapath=data_alltrk
set plotpath=plot_alltrk


pushd ECC%1

if not exist %plotpath% mkdir %plotpath%

rem use all trk( no trk cut )
::goto :done
sk %datapath%\water_manchkcut.txt
sk %datapath%\iron_manchkcut.txt
sk %datapath%\water_manchk_momrngcut.txt
sk %datapath%\iron_manchk_momrngcut.txt

root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\water_manchkcut.txt\",\"%datapath%\\water_manchkcut.root\")
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\iron_manchkcut.txt\",\"%datapath%\\iron_manchkcut.root\")
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\water_manchk_momrngcut.txt\",\"%datapath%\\water_manchk_momrngcut.root\")
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\iron_manchk_momrngcut.txt\",\"%datapath%\\iron_manchk_momrngcut.root\")
pause
:done
mkdir %plotpath%\iron_manchkcut
mkdir %plotpath%\water_manchkcut
root -l -q -b %mac%\HistGram.C(\"%datapath%\\iron_manchkcut.root\",\"%plotpath%\\iron_manchkcut\")
root -l -q -b %mac%\HistGram.C(\"%datapath%\\water_manchkcut.root\",\"%plotpath%\\water_manchkcut\")
mkdir %plotpath%\iron_manchk_momrngcut
mkdir %plotpath%\water_manchk_momrngcut
root -l -q -b %mac%\HistGram.C(\"%datapath%\\iron_manchk_momrngcut.root\",\"%plotpath%\\iron_manchk_momrngcut\")
root -l -q -b %mac%\HistGram.C(\"%datapath%\\water_manchk_momrngcut.root\",\"%plotpath%\\water_manchk_momrngcut\")


:usage
input eccnum