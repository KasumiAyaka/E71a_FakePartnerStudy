if "%1"=="" goto usage

set prgpath=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release
set outpath=ECC%1\ManChkErasedChain
set VEpath=T:\NINJA\E71a\work\kasumi\ManualCheck\ReferenceForFinalCheck\VE

if not exist ECC%1\ManChkErasedChain mkdir ECC%1\ManChkErasedChain
if not exist ECC%1\ManChkErasedChain\data mkdir ECC%1\ManChkErasedChain\data

gawk "{print $1}" ..\ManualCheckResult\Central\ECC%1\water_FakePartner.txt> ECC%1\ManChkErasedChain\data\water_event_list.txt
gawk "{print $1}" ..\ManualCheckResult\Central\ECC%1\iron_FakePartner.txt > ECC%1\ManChkErasedChain\data\iron_event_list.txt
I:\NINJA\E71a\work\kasumi\ECC\MuonAnalysis\x64\Release\pickup_selected_event_from_momch.exe ..\ManualCheckResult\Central\ECC%1\Findata\Water.momch ECC%1\ManChkErasedChain\data\Water_event_list.txt ECC%1\ManChkErasedChain\data\water.momch
I:\NINJA\E71a\work\kasumi\ECC\MuonAnalysis\x64\Release\pickup_selected_event_from_momch.exe ..\ManualCheckResult\Central\ECC%1\Findata\iron.momch ECC%1\ManChkErasedChain\data\iron_event_list.txt ECC%1\ManChkErasedChain\data\iron.momch

%prgpath%\Momch_to_vtx_add_VE_flg.exe ECC%1\ManChkErasedChain\data\water.momch %outpath%\vtx_water.txt %VEpath%\ECC%1\water\VE_Flg_list.txt 
%prgpath%\Momch_to_vtx_add_VE_flg.exe ECC%1\ManChkErasedChain\data\iron.momch %outpath%\vtx_iron.txt %VEpath%\ECC%1\iron\VE_Flg_list.txt 

%prgpath%\Momch_to_vtx_add_VE_flg.exe ECC%1\ManChkErasedChain\data\water.momch %outpath%\vtx_water_after_manchk.txt %VEpath%\ECC%1\water\VE_Flg_list.txt  1
%prgpath%\Momch_to_vtx_add_VE_flg.exe ECC%1\ManChkErasedChain\data\iron.momch %outpath%\vtx_iron_after_manchk.txt %VEpath%\ECC%1\iron\VE_Flg_list.txt  1
goto :eof


rem gawk "{if(NF==8){flg=-1;if($1==5211){flg=1}}if(flg>0){print $0}}" T:\NINJA\E71a\work\kasumi\EvrntAnalysis_ECC5\Water\vtx_before_FinalCheck.txt
rem T:\NINJA\E71a\work\kasumi\EvrntAnalysis_ECC5\Iron\ECC5\iron
rem gawk '{printf("gawk \"{if(NF==8){flg=-1;if($1==%d){flg=1}}if(flg{}0){print $0}}\" T:\\NINJA\\E71a\\work\\kasumi\\EvrntAnalysis_ECC5\\Iron\\ECC5\\iron\\vtx_Before_finalcheck.txt\n", $1)}' ECC5\ManChkErasedChain\iron_event_list.txt > do.bat

:usage
eccnum