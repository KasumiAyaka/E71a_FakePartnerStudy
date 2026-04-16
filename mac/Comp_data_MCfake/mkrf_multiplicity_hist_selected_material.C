Double_t nbins = 11.0;
Double_t n_min = -0.5;
Double_t n_max = 10.5;


void mkrf_multiplicity_hist_selected_material(TString input = "", TString output = "", Int_t matflg = 0, Int_t pflg = 0,Double_t eve = 1, Double_t mceve = 1){
	

	TH1D h1mu("h1mu","muon;# of muon;",nbins,n_min,n_max);
	TH1D h1p("h1p","proton;# of p;",nbins,n_min,n_max);
	TH1D h1pi("h1pi","pion;# of #pi;",nbins,n_min,n_max);
	TH1D h1o("h1o","Cannot Distinguish;# of others;",nbins,n_min,n_max);
	TH1D h1c("h1c","All partner(#pi,p,others);;",nbins,n_min,n_max);


	Int_t ecc,gid,cid,utime,pid,vpl,pl,ntrk,pl0,pl1,rid,nseg,npl,vph;
	Double_t vx,vy,vz,dz,ip,mu_likelihood,p_likelihood,w,w0;
	Double_t x,y,z,ax,ay;

	Int_t tmp_g,munum,pnum,pinum,onum;
	Int_t cnt=0;
	Int_t bunch,material,ntrk_all,stop_flg,charge,BMflg,stopflg;
	Double_t MCS,MCSerrl,MCSerrh,BMrng,BMrngerrl,BMrngerrh,BMcur,BMcurerrl,BMcurerrh,pb,md,oa;
	Double_t ffactor;
	std::ifstream ifs(input);
	w0 = eve / mceve;
	munum=0;
	pnum=0;
	pinum=0;
	onum=0;

	while(ifs>>ecc>>gid>>utime>>w>>vpl>>material>>ntrk>>ntrk_all>>vx>>vy>>vz>>dz>>cid>>pid>>stopflg>>
		charge>>MCS>>MCSerrl>>MCSerrh>>BMflg>>BMrng>>BMrngerrl>>BMrngerrh>>BMcur>>BMcurerrl>>BMcurerrh>>mu_likelihood>>p_likelihood>>
		pb>>nseg>>npl>>pl0>>pl1>>rid>>vph>>ax>>ay>>x>>y>>z>>ip>>md>>oa){

		pid = int(pid % 10000);
		w = w0 * w;
		ffactor = 1.0 * nseg / npl;
		
		if(material!=matflg)continue;// vertex material 0:water,2:iron, <0 : sandmuon, 2> :pack,base,etc.
		if(pid!=13&&charge < pflg)continue;// pflg==-10:no cut, -5:after manchk, ==-1:final data
		if(ax*ax+ay*ay>4.0*4.0)continue;
		if(pid==211){
			if(md>300.0){
				//std::cout<<" --> erase(md)"<<std::endl;
				continue;
			}
			if(ffactor<0.55){
				//std::cout<<" --> erase(fillfactor)"<<std::endl;
				continue;
			}
		}

		if(tmp_g!=gid&&cnt>0){
			h1mu.Fill(munum,w);
			h1p.Fill(pnum,w);
			h1pi.Fill(pinum,w);
			h1o.Fill(onum,w);
			h1c.Fill(pnum+pinum+onum,w);
			munum=0;
			pnum=0;
			pinum=0;
			onum=0;
		}
	
		if(pid==13){
			munum++;
		}
		else if(pid==2212){
			//proton
			pnum++;
		}
		else if(pid==211){
			//pion
			pinum++;
		}
		else{
			//cannot distinguish
			onum++;
		}

		tmp_g=gid;
		cnt++;
	}


	h1mu.Fill(munum,w);
	h1p.Fill(pnum,w);
	h1pi.Fill(pinum,w);
	h1o.Fill(onum,w);
	h1c.Fill(pnum+pinum+onum,w);
	//nt1.ResetBranchAddresses();

	TFile f(output,"RECREATE");
	h1mu.Write();
	h1p.Write();
	h1pi.Write();
	h1o.Write();
	h1c.Write();
}