Double_t nbins_ang = 11. ;
Double_t nbins_angp = 10. ;
Double_t ang_min = 0.0 ;
Double_t ang_max = 2200.0 ;
Double_t ang_maxp = 1000.0 ;
void mkrf_momentum_hist_selected_material (TString input = "", TString output = "", Int_t matflg = 0, Int_t pflg = 0,Double_t eve = 1, Double_t mceve = 1){
	

	//nt1.ReadFile(input);
	TH1D h1mu("h1mu","muon;[MeV/c];",nbins_ang,ang_min,ang_max);
	TH1D h1p("h1p","proton;[MeV/c];",nbins_angp,ang_min,ang_maxp);
	TH1D h1pi("h1pi","pion;[MeV/c];",nbins_angp,ang_min,ang_maxp);
	TH1D h1o("h1o","Others;[MeV/c];",nbins_ang,ang_min,ang_max);
	TH1D h1c("h1c","Partners;[MeV/c];",nbins_ang,ang_min,ang_max);

	Int_t ecc,gid,cid,utime,pid,vpl,pl,ntrk,pl0,pl1,rid,nseg,npl,vph;
	Double_t vx,vy,vz,dz,ip,mu_likelihood,p_likelihood,w;
	Double_t ax,ay,x,y,z;
	w = eve / mceve;
	Double_t chk=0;
	Int_t bunch,material,ntrk_all,stop_flg,charge,BMflg,stopflg;
	Double_t MCS,MCSerrl,MCSerrh,BMrng,BMrngerrl,BMrngerrh,BMcur,BMcurerrl,BMcurerrh,pb,md,oa;

	int i=0;int j=0;int k=0;int l=0;
	std::ifstream ifs(input);
	while(ifs>>ecc>>gid>>utime>>bunch>>vpl>>material>>ntrk>>ntrk_all>>vx>>vy>>vz>>dz>>cid>>pid>>stopflg>>
		charge>>MCS>>MCSerrl>>MCSerrh>>BMflg>>BMrng>>BMrngerrl>>BMrngerrh>>BMcur>>BMcurerrl>>BMcurerrh>>mu_likelihood>>p_likelihood>>
		pb>>nseg>>npl>>pl0>>pl1>>rid>>vph>>ax>>ay>>x>>y>>z>>ip>>md>>oa){
		
		pid = int(pid % 10000);
		if(pid==13){
		i++;
		}
		if(material!=matflg)continue;// vertex material 0:water,2:iron, <0 : sandmuon, 2> :pack,base,etc.
		if(pid!=13&&charge<pflg)continue;//-5:fin check -10:man check, -1 remain
		if(ax*ax+ay*ay>4.0*4.0)continue;
		if(pid==13){
		j++;
		}

		if(MCS<=0.0){
			MCS=50.0;
		}
		if(MCS>2000.0000){
			MCS=2100.0;
		}

		//std::cout<<MCS<<std::endl;
		if(pid==13){
			h1mu.Fill(MCS,w);
			chk=chk+w;
		}
		else if(pid==2212){
			//proton
			h1p.Fill(MCS,w);
		}
		else if(pid==211){
			//pion
			h1pi.Fill(MCS,w);
		}
		else{
			//cannot distinguish
			h1o.Fill(MCS,w);
		}
		if(pid!=13){
			// all partner tracks
			h1c.Fill(MCS,w);
		}

	}
	std::cout<<"waited event num = " << chk<<std::endl;
	std::cout << "muon : " << i << "-->" << j <<std::endl;
	//nt1.ResetBranchAddresses();

	TFile f(output,"RECREATE");
	h1mu.Write();
	h1p.Write();
	h1pi.Write();
	h1o.Write();
	h1c.Write();
}