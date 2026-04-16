if "%1"=="" goto usage

set prgpath=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release
set outpath=ECC%1\ManChkErasedChain
set VEpath=T:\NINJA\E71a\work\kasumi\ManualCheck\ReferenceForFinalCheck\VE

if not exist ECC%1\ManChkErasedChain mkdir ECC%1\ManChkErasedChain
if not exist ECC%1\ManChkErasedChain\data mkdir ECC%1\ManChkErasedChain\data


I:\NINJA\E71a\work\kasumi\ECC\MuonAnalysis\x64\Release\Pick_up_indicated_chain.exe ECC%1\ManChkErasedChain\data\water.momch ECC%1\ManChkErasedChain\vtx_water_erase_chain_list_without_man_chk.txt ECC%1\ManChkErasedChain\data\water_aft_finchk.momch
I:\NINJA\E71a\work\kasumi\ECC\MuonAnalysis\x64\Release\Pick_up_indicated_chain.exe ECC%1\ManChkErasedChain\data\iron.momch ECC%1\ManChkErasedChain\vtx_iron_erase_chain_list_without_man_chk.txt ECC%1\ManChkErasedChain\data\iron_aft_finchk.momch

%prgpath%\Momch_to_vtx_add_VE_flg.exe ECC%1\ManChkErasedChain\data\water_aft_finchk.momch %outpath%\vtx_water_aft_finchk.txt %VEpath%\ECC%1\water\VE_Flg_list.txt 
%prgpath%\Momch_to_vtx_add_VE_flg.exe ECC%1\ManChkErasedChain\data\iron_aft_finchk.momch %outpath%\vtx_iron_aft_finchk.txt %VEpath%\ECC%1\iron\VE_Flg_list.txt 

goto :eof


:usage
eccnum