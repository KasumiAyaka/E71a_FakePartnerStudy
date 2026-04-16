set prg=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release
set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\mac\Comp_data_MCfake
set prg2=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\prg

set plotpath=ECC5\\AfterVC
if not exist ECC5\\AfterVC mkdir ECC5\\AfterVC 

goto :done
rem true
%prg%\Output_track_information_for_mc.exe ECC5\MC_FakePartner\data\muon_mc.momch ECC5\\MC_FakePartner\\Findata\\water_true.txt 5
sk ECC5\\MC_FakePartner\\Findata\\water_true.txt
rem fake
C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Add_material_flg.exe ECC5\MC_FakePartner\data\event_water_fin3_edit_partner_stopflg_add_weigt.momch ECC5\MC_FakePartner\data\event_water_fin3_edit_partner_stopflg_add_weigt_addMaterialFlg.momch ECC5\MC_FakePartner\data\material_flg.txt
%prg%\Output_track_information_for_mc.exe ECC5\MC_FakePartner\data\event_water_fin3_edit_partner_stopflg_add_weigt_addMaterialFlg.momch ECC5\\MC_FakePartner\\Findata\\water_fake.txt 5
sk ECC5\\MC_FakePartner\\Findata\\water_fake.txt
rem data
%prg%\Output_track_information.exe T:\NINJA\E71a\work\kasumi\ManualCheck\ManualCheckResult\Central\ECC5\Findata\Water.momch ECC5\\data\\water.txt 5
sk ECC5\\data\\water.txt
:done

root -l -q -b mac\mkrf_txt2root.C(\"ECC5\\data\\water.txt\",\"%plotpath%\\water.root\")
root -l -q -b %mac%\mkrf_txt2root.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"%plotpath%\\water_fake.root\")
root -l -q -b %mac%\mkrf_txt2root.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"%plotpath%\\water_true.root\")


rem data
root -l -q -b mac\mkrf_momentum_hist.C(\"ECC5\\data\\water.txt\",\"ECC5\\AfterVC\\water_data_mom.root\",0,-20)
root -l -q -b mac\mkrf_multiplicity_hist.C(\"ECC5\\data\\water.txt\",\"ECC5\\AfterVC\\water_data_mul.root\",0,-20)
root -l -q -b mac\mkrf_emission_angle_hist.C(\"ECC5\\data\\water.txt\",\"ECC5\\AfterVC\\water_data_em.root\",0,-20)
pause

::goto :skip
set mcnum=1
set datanum=1
set mcnum=87.7181
set datanum=101
rem fake
root -l -q -b mac\Comp_data_MCfake\mkrf_momentum_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"ECC5\\AfterVC\\water_mc_mom.root\",0,-20,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_multiplicity_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"ECC5\\AfterVC\\water_mc_mul.root\",0,-20,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_emission_angle_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"ECC5\\AfterVC\\water_mc_em.root\",0,-20,%datanum%,%mcnum%)
pause

rem true
root -l -q -b mac\Comp_data_MCfake\mkrf_momentum_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"ECC5\\AfterVC\\water_mc_true_mom.root\",0,-20,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_multiplicity_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"ECC5\\AfterVC\\water_mc_true_mul.root\",0,-20,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_emission_angle_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"ECC5\\AfterVC\\water_mc_true_em.root\",0,-20,%datanum%,%mcnum%)
pause
::done


:skip
root -l -q -b mac\Draw_same_Fakestop.C(\"%plotpath%\\water_data_mom.root\",\"%plotpath%\\water_mc_true_mom.root\",\"%plotpath%\\water_mc_mom.root\",\"%plotpath%\\water_mom.pdf\")
root -l -q -b mac\Draw_same_Fakestop.C(\"%plotpath%\\water_data_mul.root\",\"%plotpath%\\water_mc_true_mul.root\",\"%plotpath%\\water_mc_mul.root\",\"%plotpath%\\water_mul.pdf\")
root -l -q -b mac\Draw_same_Fakestop.C(\"%plotpath%\\water_data_em.root\",\"%plotpath%\\water_mc_true_em.root\",\"%plotpath%\\water_mc_em.root\",\"%plotpath%\\water_em.pdf\")
root -l -q -b mac\Draw_same_Fakestop_emcos.C(\"%plotpath%\\water_data_em.root\",\"%plotpath%\\water_mc_true_em.root\",\"%plotpath%\\water_mc_em.root\",\"%plotpath%\\water_em_cos.pdf\")


set nm=Ffactor060
::set nm=cut2seg4pl
::root -l -q -b mac\mkrf_emission_angle_hist.C(\"ECC5\\data\\water.txt\",\"ECC5\\AfterVC\\water_data_em%nm%.root\",-1,-20)
::root -l -q -b mac\Comp_data_MCfake\mkrf_emission_angle_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"ECC5\\AfterVC\\water_mc_em%nm%.root\",-1,-20,%datanum%,%mcnum%)
::root -l -q -b mac\Comp_data_MCfake\mkrf_emission_angle_hist.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"ECC5\\AfterVC\\water_mc_true_em%nm%.root\",-1,-20,%datanum%,%mcnum%)
root -l -q -b mac\Draw_same_Fakestop.C(\"%plotpath%\\water_data_em%nm%.root\",\"%plotpath%\\water_mc_true_em.root\",\"%plotpath%\\water_mc_em%nm%.root\",\"%plotpath%\\water_em%nm%.pdf\")
::root -l -q -b mac\Draw_same_Fakestop_emcos.C(\"%plotpath%\\water_data_em%nm%.root\",\"%plotpath%\\water_mc_true_em%nm%.root\",\"%plotpath%\\water_mc_em%nm%.root\",\"%plotpath%\\water_em_cos%nm%.pdf\")
