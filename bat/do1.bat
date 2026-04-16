set prg=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release
set inpath=T:\NINJA\E71a\work\kasumi\ManualCheck\ManualCheckResult\Central\ECC%1\Findata
set sfpath=T:\NINJA\E71a\work\LatestData_sharingFile\SFver2

if not exist ECC%1 mkdir ECC%1
pushd ECC%1

mkdir data
%prg%\Output_track_information.exe %inpath%\Water.momch data\water.txt %1
%prg%\Output_track_information.exe %inpath%\iron.momch  data\iron.txt %1

mkdir data_alltrk
rem man-chkあと残ったpartnerのみ使ってvertexを計算
rem manual chk cut
%prg%\Output_track_information.exe %inpath%\Water.momch data_alltrk\water_manchkcut.txt %1 -5
%prg%\Output_track_information.exe %inpath%\iron.momch  data_alltrk\iron_manchkcut.txt %1 -5
pause


rem true partnerのみ使ってvertexを計算
rem manchk cut & mom-rng cut
%prg%\Output_track_information.exe %inpath%\Water.momch data_alltrk\water_manchk_momrngcut.txt %1 -2
%prg%\Output_track_information.exe %inpath%\iron.momch  data_alltrk\iron_manchk_momrngcut.txt %1 -2

popd

goto :eof

