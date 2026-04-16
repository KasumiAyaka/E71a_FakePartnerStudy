
void mkrf_txt2root_ver2(TString input="",TString output=""){
	
//C:\Users\kasumi\source\repos\ArrangeMomch\x64\Release\Vtx_pos_check.exe ECC5\data\water.txt ECC5\data\water_vtxpos_chk.txt 4.00 30 10
//root -l -q -b mac\mkrf_txt2root_ver2.C(\"ECC5\\data\\water_vtxpos_chk.txt\",\"ECC5\\data\\water_vtxpos_chk.root\")
	TFile *file = TFile::Open(output,"RECREATE");
	TTree* tree = new TTree("tree","tree");

	tree->ReadFile(input.Data(),"ecc/I:eid/I:utime/L:bunch/I:vpl/I:material/I:ntrk/I:vx/D:vy/D:vz/D:vdz/D:ntrk_all/I:md_all/D:vdz_all/D:cid/I:pid/I:stopflg/I:charge/I:MCS/D:MCSerrl/D:MCSerrh/D:BMflg/I:BMrng/D:BMrngerrl/D:BMrngerrh/D:BMcur/D:BMcurerrl/D:BMcurerrh/D:mulikelihood/D:plikelihood/D:pb/D:nseg/I:npl/I:pl0/I:pl1/I:rid/I:vph/I:ax/D:ay/D:x/D:y/D:z/D:ip/D:md/D:oa/D:dz/D:selflg/I");
	tree->Write();
	
	file->Close();

}