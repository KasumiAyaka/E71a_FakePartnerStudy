set prg=C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release
set mac=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\mac\Comp_data_MCfake
set prg2=T:\NINJA\E71a\work\kasumi\ManualCheck\Analysis\prg
rem K:\NINJA\E71a\work\hayakawa\FakePartnerAnalysis\ECC5_center\03_vertex_location\muon_mc.momch
rem K:\NINJA\E71a\work\hayakawa\FakePartnerAnalysis\ECC5_center\05_event_treatment\event_water_fin3.momch
set datapath=Findata
pushd ECC%1\MC_FakePartner

set fake=water_fake85
set true=water_true85
set in_data=water_agressive
rem set mcnum=1
rem set datanum=1
set mcnum=67.4847
set datanum=85


rem agressive fake cut
::goto :done2
%prg%\Output_track_information_for_mc.exe %datapath%\%in_data%.momch %datapath%\%fake%.txt %1
sk %datapath%\\%fake%.txt
:done2
set plotpath=plot_%fake%
if not exist %plotpath% mkdir %plotpath%
::root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\%target_data%.txt\",\"%plotpath%\\water_em.root\",0,-15,%datanum%,%mcnum%)
::root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mom.root\",0,-15,%datanum%,%mcnum%)
::root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mul.root\",0,-15,%datanum%,%mcnum%)
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\%fake%.root\")
root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mom_remain.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mul_remain.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_em_remain.root\",0,-1,%datanum%,%mcnum%)
pause


rem true
::goto :done3
::%prg2%\Output_track_information_for_mc.exe %datapath%\%true%.momch %datapath%\%true%.txt %1
%prg%\Output_track_information_for_mc.exe data\muon_mc.momch %datapath%\%true%.txt %1
rem C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Output_track_information_for_mc.exe
sk %datapath%\\%true%.txt
:done3
set plotpath=plot_%true%
if not exist %plotpath% mkdir %plotpath%
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\%true%.txt\",\"%plotpath%\\%true%.root\")
root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\%true%.txt\",\"%plotpath%\\water_mom.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\%true%.txt\",\"%plotpath%\\water_mul.root\",0,-1,%datanum%,%mcnum%)
root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\%true%.txt\",\"%plotpath%\\water_em.root\",0,-1,%datanum%,%mcnum%)

goto :end



rem fake
rem 37.1286

rem goto :done1
rem I:\NINJA\E71a\work\kasumi\ECC\MuonAnalysis\x64\Release\pickup_selected_event_from_momch.exe %datapath%\Water.momch cnt2.txt %datapath%\%fake%.momch
rem %prg%\Output_track_information_for_mc.exe %datapath%\%fake%.momch %datapath%\%fake%.txt %1
rem sk %datapath%\\%fake%.txt
rem :done1
rem set plotpath=plot_%fake%
rem if not exist %plotpath% mkdir %plotpath%
rem root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\%fake%.root\")
rem rem root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mom.root\",0,-15,%datanum%,%mcnum%)
rem rem root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mul.root\",0,-15,%datanum%,%mcnum%)
rem rem root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_em.root\",0,-15,%datanum%,%mcnum%)
rem root -l -q -b %mac%\mkrf_momentum_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mom_remain.root\",0,-1,%datanum%,%mcnum%)
rem root -l -q -b %mac%\mkrf_multiplicity_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_mul_remain.root\",0,-1,%datanum%,%mcnum%)
rem root -l -q -b %mac%\mkrf_emission_angle_hist.C(\"%datapath%\\%fake%.txt\",\"%plotpath%\\water_em_remain.root\",0,-1,%datanum%,%mcnum%)
rem pause



%prg%\Output_track_information.exe %inpath%\iron.momch  data\iron.txt %1
sk %datapath%\\iron.txt
root -l -q -b %mac%\mkrf_txt2root.C(\"%datapath%\\iron.txt\",\"%datapath%\\iron.root\")


:end
popd