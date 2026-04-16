Double_t nbins_mom = 100. ;
Double_t mom_min = 0.0 ;
Double_t mom_max = 2000.0 ;

void mkrf_emission_angle_hist2d(TString input="",TString output=""){//,Double_t evenum = 1.0, Double_t mcnum = 1.0){
	

	//nt1.ReadFile(input);
	TH2D h2d_mom("h2d_mom","ECC mcs vs BM rng; BM [MeV/c];ECC [MeV/c]", nbins_mom, mom_min, mom_max, nbins_mom, mom_min, mom_max);


	Int_t utime,bunch,eid,pid;
	Double_t w=1;
	Double_t mcs, s_err,l_err,BMrng,bms_err,bml_err;
	//Double_t norm = evenum / mcnum;

	std::ifstream ifs(input);
	//utime bunch eid pid mcs -err +err BM -err +e
	while(ifs>>utime>>bunch>>eid>>pid>>mcs>>s_err>>l_err>>BMrng>>bms_err>>bml_err){


		if(pid==13){
			h2d_mom.Fill(BMrng,mcs,w);
		}

	}

	//nt1.ResetBranchAddresses();

	TFile f(output,"RECREATE");
	h2d_mom.Write();

}