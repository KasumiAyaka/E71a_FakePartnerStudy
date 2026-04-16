
void mkrf_txt2root(TString input="",TString output=""){
	

	TFile *file = TFile::Open(output,"RECREATE");
	TTree* tree = new TTree("tree","tree");

	tree->ReadFile(input.Data(),"ecc/I:eid/I:utime/L:bunch/I:vpl/I:material/I:ntrk/I:ntrk_all/I:vx/D:vy/D:vz/D:dz/D:cid/I:pid/I:stopflg/I:charge/I:MCS/D:MCSerrl/D:MCSerrh/D:BMflg/I:BMrng/D:BMrngerrl/D:BMrngerrh/D:BMcur/D:BMcurerrl/D:BMcurerrh/D:mulikelihood/D:plikelihood/D:pb/D:nseg/I:npl/I:pl0/I:pl1/I:rid/I:vph/I:ax/D:ay/D:x/D:y/D:z/D:ip/D:md/D:oa/D");
	tree->Write();
	
	file->Close();

}