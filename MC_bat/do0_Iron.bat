if "%1"=="" goto :usage


set n=%1
rem set prg_path=T:\NINJA\E71a\work\kasumi\VirtualErase
rem  C:\Users\kasumi\source\repos\VirtualErase\x64\Release\Pickup_unit_track.exe
rem T:\NINJA\E71a\work\kasumi\VirtualErase_ver2

set prg=T:\NINJA\E71a\work\kasumi\ManualCheck\ReferenceForFinalCheck\VE\prg
set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\ReferenceForFinalCheck\VE\mac


set input_path=T:\NINJA\E71a\work\kasumi\IronInteraction\ECC1\ManualCheck
set in_momch=%input_path%\event_iron_fin_CentralArea.momch
set work_path=ECC%n%\\iron
set ve_unit_list=unit_track_list_under16npl.txt
set npl_thr=15

if not exist %work_path% mkdir %work_path%
rem if not exist %input% M:\data\NINJA\prg\Read_Wrtie_Momchain.exe %input_path%\ECC%n%.momch %input%


pushd %work_path%

rem Make unit trtack list
%prg%\Pickup_unit_track_for_iron_int.exe %in_momch% %ve_unit_list% %npl_thr% 
rem output: gid cid pid venum pl0 rid0 pl1 rid1


rem Make batch-file for do VE and draw plot
if not exist Plot mkdir Plot
if exist VE_matching_Results.txt del VE_matching_Results.txt
if exist ECC%n%.bat del ECC%n%.bat
gawk "{print ""root"",""-l"",""-q"",""-b"",""T:\\NINJA\\E71a\\work\\kasumi\\VirtualErase_ver2\\mac\\MatchingVELinklet_water.C(""%n%"",""$1"",""$2"",""$4"",""$5"",""$6"",""$7"",""$8"")""}" %ve_unit_list% > ECC%n%.bat
echo exit >> ECC%n%.bat
if exist ECC%n%_mkve_list.bat del ECC%n%_mkve_list.bat
gawk "{print ""root"",""-l"",""-q"",""-b"",""T:\\NINJA\\E71a\\work\\kasumi\\VirtualErase_ver2\\mac\\MatchingVELinklet_OutputErasableTrack_water.C(""%n%"",""$1"",""$2"",""$3"",""$4"",""$5"",""$6"",""$7"",""$8"")""}" %ve_unit_list% > ECC%n%_mkve_list.bat
echo exit >> ECC%n%_mkve_list.bat
start ECC%n%.bat
start ECC%n%_mkve_list.bat

rem call ECC%n%_mkve_list.bat
rem gawk "{if($7*$7<100.0){print $2,$3}}" ECC%n%\water\VE_Results.txt >ECC%n%\water\EraseChainList.txt

popd

goto :eof

:usage
echo # of ECC
goto :eof

