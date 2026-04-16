if "%1"=="" goto :usage

set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\mac

pushd T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis

set datapath=ECC%1\\data
set mc_datapath=ECC%1\\MC_FakePartner\\plot_water_mc_42eve
set fake_datapath=ECC%1\\MC_FakePartner\\plot_water_42eve
set plotpath=ECC%1\\MC_FakePartner\\Plotcomp_water_42eve
if not exist %plotpath% mkdir %plotpath%
rem all
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_mom.root\",\"%mc_datapath%\\water_mom.root\",\"%fake_datapath%\\water_mom.root\",\"%plotpath%\\water_mom_nocut.pdf\")
pause
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_mul.root\",\"%mc_datapath%\\water_mul.root\",\"%fake_datapath%\\water_mul.root\",\"%plotpath%\\water_mul_nocut.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_em.root\",\"%mc_datapath%\\water_em.root\",\"%fake_datapath%\\water_em.root\",\"%plotpath%\\water_em_nocut.pdf\")
rem after cut
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_mom_remain.root\",\"%mc_datapath%\\water_mom.root\",\"%fake_datapath%\\water_mom_remain.root\",\"%plotpath%\\water_mom.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_mul_remain.root\",\"%mc_datapath%\\water_mul.root\",\"%fake_datapath%\\water_mul_remain.root\",\"%plotpath%\\water_mul.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_em_remain.root\",\"%mc_datapath%\\water_em.root\",\"%fake_datapath%\\water_em_remain.root\",\"%plotpath%\\water_em.pdf\")

set mc_datapath=ECC%1\\MC_FakePartner\\plot_water_mc_42eve
set fake_datapath=ECC%1\\MC_FakePartner\\plot_eve_water_agressive
set plotpath=ECC%1\\MC_FakePartner\\Plotcomp_water_42eve_agressive
if not exist %plotpath% mkdir %plotpath%

root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_mom.root\",\"%mc_datapath%\\water_mom.root\",\"%fake_datapath%\\water_mom_remain.root\",\"%plotpath%\\water_mom.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_mul.root\",\"%mc_datapath%\\water_mul.root\",\"%fake_datapath%\\water_mul_remain.root\",\"%plotpath%\\water_mul.pdf\")
root -l -q -b %mac%\Draw_same_Fakestop.C(\"%datapath%\\water_em.root\",\"%mc_datapath%\\water_em.root\",\"%fake_datapath%\\water_em_remain.root\",\"%plotpath%\\water_em.pdf\")

popd
goto :eof

root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mom_cutall.root\")
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mul_cutall.root\")
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_em_cutall.root\")


:usage
input eccnum