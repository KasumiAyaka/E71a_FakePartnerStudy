set prg=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release
set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\mac
set prg2=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\prg

set fake=ECC5\\MC_FakePartner\\plot_water_fake92
set true=ECC5\\MC_FakePartner\\plot_water_true92
set target_data=ECC5\\MC_FakePartner\\plot_water_fake_42eve_agressive

set plotpath=ECC5\\AfterRngMomCut
if not exist %plotpath% mkdir %plotpath%
::goto :done
rem data
root -l -q -b mac\mkrf_momentum_hist_selected_material.C(\"ECC5\\data\\water.txt\",\"%plotpath%\\water_data_mom.root\",0,-1)
root -l -q -b mac\mkrf_multiplicity_hist_selected_material.C(\"ECC5\\data\\water.txt\",\"%plotpath%\\water_data_mul.root\",0,-1)
root -l -q -b mac\mkrf_emission_angle_hist_selected_material.C(\"ECC5\\data\\water.txt\",\"%plotpath%\\water_data_em.root\",0,-1)
rem root -l -q -b %mac%\Draw_same_Fakestop.C(\"%plotpath%\\water_data_mom.root\",\"%true%\\water_mom.root\",\"%fake%\\water_mom_remain.root\",\"%plotpath%\\water_mom.pdf\")
rem root -l -q -b %mac%\Draw_same_Fakestop.C(\"%plotpath%\\water_data_mul.root\",\"%true%\\water_mul.root\",\"%fake%\\water_mul_remain.root\",\"%plotpath%\\water_mul.pdf\")
rem root -l -q -b %mac%\Draw_same_Fakestop.C(\"%plotpath%\\water_data_em.root\",\"%true%\\water_em.root\",\"%fake%\\water_em_remain.root\",\"%plotpath%\\water_em.pdf\")
pause
:done

rem fake data set
set mcnum=67.4847
set datanum=83
rem fake
root -l -q -b mac\Comp_data_MCfake\mkrf_momentum_hist_selected_material.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"%plotpath%\\water_mc_mom.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_multiplicity_hist_selected_material.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"%plotpath%\\water_mc_mul.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_emission_angle_hist_selected_material.C(\"ECC5\\MC_FakePartner\\Findata\\water_fake.txt\",\"%plotpath%\\water_mc_em.root\",0,-1,%datanum%,%mcnum%)
rem true
root -l -q -b mac\Comp_data_MCfake\mkrf_momentum_hist_selected_material.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"%plotpath%\\water_mc_true_mom.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_multiplicity_hist_selected_material.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"%plotpath%\\water_mc_true_mul.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b mac\Comp_data_MCfake\mkrf_emission_angle_hist_selected_material.C(\"ECC5\\MC_FakePartner\\Findata\\water_true.txt\",\"%plotpath%\\water_mc_true_em.root\",0,-1,%datanum%,%mcnum%)
pause

root -l -q -b %mac%\Draw_same_Fakestop.C(\"%plotpath%\\water_data_mom.root\",\"%plotpath%\\water_mc_true_mom.root\",\"%plotpath%\\water_mc_mom.root\",\"%plotpath%\\water_mom.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%plotpath%\\water_data_mul.root\",\"%plotpath%\\water_mc_true_mul.root\",\"%plotpath%\\water_mc_mul.root\",\"%plotpath%\\water_mul.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%plotpath%\\water_data_em.root\",\"%plotpath%\\water_mc_true_em.root\",\"%plotpath%\\water_mc_em.root\",\"%plotpath%\\water_em.pdf\")













goto :skip
set plotpath=ECC5\\AfterRngMomCut_agressive
if not exist %plotpath% mkdir %plotpath%
root -l -q -b %mac%\Draw_same_Fakestop.C(\"ECC5\\AfterVC\\water_data_mom.root\",\"%true%\\water_mom.root\",\"%target_data%\\water_mom_remain.root\",\"%plotpath%\\water_mom.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"ECC5\\AfterVC\\water_data_mul.root\",\"%true%\\water_mul.root\",\"%target_data%\\water_mul_remain.root\",\"%plotpath%\\water_mul.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"ECC5\\AfterVC\\water_data_em.root\",\"%true%\\water_em.root\",\"%target_data%\\water_em_remain.root\",\"%plotpath%\\water_em.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop_emcos.C(\"ECC5\\AfterVC\\water_data_em.root\",\"%true%\\water_em.root\",\"%target_data%\\water_em_remain.root\",\"%plotpath%\\water_emcos.pdf\")
:skip