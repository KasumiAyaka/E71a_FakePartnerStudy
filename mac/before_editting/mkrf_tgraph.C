#include <iostream>
#include <fstream>

void mkrf_tgraph(TString input="",TString output=""){
	

	//nt1.ReadFile(input);
	Int_t utime,bunch,gid,vpl,nseg,npl;
	Double_t ax,ay,x,y;
	Int_t charge;
	Double_t BM,BMerrm,BMerrp,MCS,MCSerrm,MCSerrp;
	Int_t timestamp;

	const Int_t NPOINT=20000;
	const Int_t pi_NPOINT=20000;
	Double_t BMmom[NPOINT],ECCmom[NPOINT],pi_mom[pi_NPOINT];
	Int_t cnt=0;
	Int_t picnt=0;
	std::ifstream ifs(input);
	
	if(!ifs){
		std::cerr<<"File open error!"<<std::endl;
	}
	
	while(ifs >> utime>>bunch>>gid>>vpl>>nseg>>npl>>ax>>ay>>x>>y>>charge>>BM>>BMerrm>>BMerrp>>MCS>>MCSerrm>>MCSerrp>>timestamp){
		std::cout<<"ok?"<<Std::endl;
		BMmom[cnt] = BM;
		ECCmom[cnt] = MCS;
		cnt++;
		std::cout << "BM = " << BM<< ", MCS = " << MCS << std::endl;

	}
	std::cout << " Muon prediction : " << cnt << std::endl;

	for(Int_t n = cnt; n < 20000; n++){
		BMmom[cnt] = -40000;
		ECCmom[cnt] = -40000;

	}

	//nt1.ResetBranchAddresses();

	TGraph *grp = new TGraph(NPOINT, BMmom, ECCmom);
	grp->SetTitle(" Muon Prediction ; BM momentum [MeV/c]; ECC MCS momentum [MeV/c]");
	grp->GetXaxis()->SetRangeUser(0,2500);
	grp->GetYaxis()->SetRangeUser(0,2500);
	grp->SetMarkerStyle(20);
	grp->SetMarkerColor(1);
	grp->Draw("AP");
	grp->SetName("grp");
	

	TFile f(output,"RECREATE");
	grp->Write();

}