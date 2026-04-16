set prg=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\
set datapath=T:\NINJA\E71a\work\Momch_after_divide_Area\Add_sandmuonflg_sf_information
set output=Findata


rem gawk '{if($3=="o"){print $1,$2}if($4=="fake"){print $1,$2}}' ECC5\MC_FakePartner\water\EraseChainList2.txt  > ECC5\MC_FakePartner\water\EraseChainList_agressive.txt


pushd ECC%1\MC_FakePartner

if not exist %output% mkdir %output%
echo add material_flg == 0 :water
rem gawk "{print $2,$4}" tmp_mc.txt > weight_list.txt
C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\add_weight_to_momch.exe data\event_water_fin3_edit_partner_stopflg.momch  data\event_water_fin3_edit_partner_stopflg_add_weigt.momch data\weight_list_water.txt
rem %prg%\Add_ManualCheckResults.exe data\event_water_fin3_edit_partner_stopflg_add_weigt.momch tmp0.momch 0
%prg%\Add_material_flg.exe data\event_water_fin3_edit_partner_stopflg_add_weigt.momch tmp.momch data\material_flg_water.txt
%prg%\Add_manualcheck_result_to_chain.exe tmp.momch water\EraseChainList_agressive.txt -5  %output%\water_agressive.momch


goto :end
%prg%\Add_material_flg.exe %datapath%\ECC5_iron_CentralArea.momch tmp.momch List_iron_add_matelial_flg.txt
%prg%\Add_manualcheck_result_to_chain.exe tmp.momch iron_erase_chain_by_finalcheck.txt -5 tmp1.momch
%prg%\Add_manualcheck_result_to_chain.exe tmp1.momch iron_FakePartner.txt -10 %output%\iron.momch

:end
del tmp*.momch
popd

