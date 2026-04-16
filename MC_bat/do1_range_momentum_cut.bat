
if "%2"=="" goto :usage

set prg=T:\NINJA\E71a\work\kasumi\ManualCheck\ReferenceForFinalCheck\VE\prg
set param=T:\NINJA\E71a\work\kasumi\VirtualErase_ver2
set input_path=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\ECC%1\MC_FakePartner\data
set input_mc=K:\NINJA\E71a\work\hayakawa\FakePartnerAnalysis\ECC%1_center\03_vertex_location\muon_mc.momch

if "%2"=="iron" goto :iron
set inmomch=%input_path%\event_water_fin3.momch
:conti

set output=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\ECC%1\MC_FakePartner
if not exist %output%\vph_pl_correction_mip.txt copy T:\NINJA\E71a\work\ECC%1\PID\VPHcorrection\gel\vph\corr_plot\vph_pl_correction_mip.txt %output%

if not exist  %output%\%2 mkdir  %output%\%2
pause

pushd %output%\%2
set vphparam=T:\NINJA\E71a\work\kasumi\ManualCheck\ReferenceForFinalCheck\VE\ECC%1\%2

goto :skip
rem done %prg%\Decide_mip_Hip_thr.exe ..\vph_pl_correction_mip.txt mip_thr.txt
%prg%\Judge_black_for_found_ve_track.exe VE_matching_Results.txt %vphparam%\mip_thr.txt judge_black.txt > zLog_Judge_black_for_found_ve_track.log.txt
%prg%\Make_VE_flg_list.exe judge_black.txt %param%\lateral_mean_sig.txt %param%\radial_mean_sig.txt VE_Flg_list.txt > zLog_Make_VE_flg_list.log.txt

C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Add_partner_stop_flg.exe %inmomch% %input_path%\event_water_fin3_edit_partner_stopflg.momch
:skip
%prg%\Momch_to_vtx_add_VE_flg.exe %input_path%\event_water_fin3_edit_partner_stopflg.momch vtx_cut4seg4pl.txt VE_Flg_list.txt
rem %prg%\Momch_to_vtx_add_VE_flg_cut2seg4pl_trk.exe %input_path%\event_water_fin3_edit_partner_stopflg.momch vtx_cut4seg4pl.txt VE_Flg_list.txt
goto :skip2
copy vtx.txt vtx_after_chk.txt 
:skip2
gawk "{if(NF==8){gid=$1}if(NF==27&&$1>0){print gid,$1}}" T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\ECC5\MC_FakePartner\water\vtx_after_chk.txt > T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\ECC5\MC_FakePartner\water\EraseChainList.txt


rem C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Momch_to_vtx_add_VE_flg_for_FakePatnerStudy.exe %input_mc% %inmomch% vtx_muon_is_mc.txt VE_Flg_list.txt
rem C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Momch_to_vtx_add_VE_flg_for_FakePatnerStudy.exe  K:\NINJA\E71a\work\hayakawa\FakePartnerAnalysis\ECC5_center\03_vertex_location\muon_mc.momch T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\ECC5\MC_FakePartner\data\event_water_fin3.momch  vtx_muon_is_mc.txt VE_Flg_list.txt
rem not work well
popd


goto :eof

:iron
set inmomch=%input_path%\event_iron_fin_CentralArea.momch
goto :conti

rem original
rem copy K:\NINJA\E71a\work\suzuki\PID\VPHcorrection\gel\vph\corr_plot\*.txt 
rem set prg=C:\Users\kasumi\source\repos\VirtualErase\x64\Release
cd /d T:\NINJA\E71a\work\kasumi\VirtualErase_ver2
root -l -q -b mac\plot_drdl.C(\"I:\\NINJA\\E71a\\work\\kasumi\\ECC5\\VirtualErase\\f_pl055_052\\l-055-052.root\",\"PL055-052.pdf\",\"lateral_mean_sig.txt\",\"radial_mean_sig.txt\")

cd /d T:\NINJA\E71a\work\kasumi\VirtualErase_ver2\ECC5\water\mip_Hip_ref
if not exist vph_pl_correction_mip.txt copy K:\NINJA\E71a\work\suzuki\PID\VPHcorrection\gel\vph\corr_plot\vph_pl_correction_mip.txt

C:\Users\kasumi\source\repos\VirtualErase\x64\Release\Decide_mip_Hip_thr.exe vph_pl_correction_mip.txt mip_thr.txt 
C:\Users\kasumi\source\repos\VirtualErase\x64\Release\Judge_black_for_found_ve_track.exe ..\VE_matching_Results.txt mip_thr.txt judge_black.txt > Judge_black_for_found_ve_track.log.txt
C:\Users\kasumi\source\repos\VirtualErase\x64\Release\Make_VE_flg_list.exe judge_black.txt T:\NINJA\E71a\work\kasumi\VirtualErase_ver2\lateral_mean_sig.txt T:\NINJA\E71a\work\kasumi\VirtualErase_ver2\radial_mean_sig.txt VE_Flg_list.txt > Make_VE_flg_list.log.txt
C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Momch_to_vtx_add_VE_flg.exe T:\NINJA\E71a\work\kasumi\EvrntAnalysis_ECC5\ECC5.momch vtx_test.txt VE_Flg_list.txt
copy   vtx_test.txt T:\NINJA\E71a\work\kasumi\EvrntAnalysis_ECC5



:usage
echo eccnum material(iron / water)
