if "%1"=="" goto :usage

pushd ECC%1
if not exist plot mkdir plot

set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\mac
set datapath=data
set plotpath=plot


::goto :done
sk %datapath%\\water.txt
sk %datapath%\\iron.txt
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\water.txt\",\"%datapath%\\water.root\")
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron.root\")
pause
:done

rem no cut
root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mom.root\",0,-10)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mul.root\",0,-10)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_em.root\",0,-10)

rem after manual check
root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mom_after_manchk.root\",0,-5)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mul_after_manchk.root\",0,-5)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_em_after_manchk.root\",0,-5)

rem after range-mom cut
root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mom_remain.root\",0,-1)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mul_remain.root\",0,-1)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_em_remain.root\",0,-1)

rem draw same
root -l -q -b %mac%\Draw_same.C(\"%datapath%\\water_mom\",\"%plotpath%\\water_mom.pdf\")
root -l -q -b %mac%\Draw_same.C(\"%datapath%\\water_mul\",\"%plotpath%\\water_mul.pdf\")
root -l -q -b %mac%\Draw_same.C(\"%datapath%\\water_em\",\"%plotpath%\\water_em.pdf\")
pause


rem iron
root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_mom.root\",2,-15)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_mul.root\",2,-15)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_em.root\",2,-15)

root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_mom_after_manchk.root\",2,-5)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_mul_after_manchk.root\",2,-5)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_em_after_manchk.root\",2,-5)

root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_mom_remain.root\",2,-1)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_mul_remain.root\",2,-1)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron_em_remain.root\",2,-1)


root -l -q -b %mac%\Draw_same.C(\"%datapath%\\iron_mom\",\"%plotpath%\\iron_mom.pdf\")
root -l -q -b %mac%\Draw_same.C(\"%datapath%\\iron_mul\",\"%plotpath%\\iron_mul.pdf\")
root -l -q -b %mac%\Draw_same.C(\"%datapath%\\iron_em\",\"%plotpath%\\iron_em.pdf\")

popd
goto :eof

root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mom_cutall.root\")
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_mul_cutall.root\")
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\water.txt\",\"%datapath%\\water_em_cutall.root\")


:usage
input eccnum