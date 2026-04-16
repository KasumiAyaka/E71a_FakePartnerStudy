Double_t nbins_ang = 20. ;
Double_t ang_min = -1.0 ;
Double_t ang_max = 1.0 ;
Double_t pnbins_ang = 18. ;
Double_t pang_min = 0.0 ;
Double_t pang_max = 180.0 ;

void mkrf_emission_angle_hist_selected_material(TString input = "", TString output = "", Int_t matflg = 0, Int_t pflg = 0){
	

	//nt1.ReadFile(input);
	TH1D h1cos_mu("h1cos_mu","muon;cos#theta;",nbins_ang,ang_min,ang_max);
	TH1D h1mu("h1mu","muon;arccos#theta [degree];",pnbins_ang,pang_min,pang_max);

	TH1D h1cos_p("h1cos_p","proton;cos#theta;",nbins_ang,ang_min,ang_max);
	TH1D h1p("h1p","proton;arccos#theta [degree];",pnbins_ang,pang_min,pang_max);

	TH1D h1cos_pi("h1cos_pi","pion;cos#theta;",nbins_ang,ang_min,ang_max);
	TH1D h1pi("h1pi","pion ;arccos#theta[degree];",pnbins_ang,pang_min,pang_max);

	TH1D h1cos_o("h1cos_o","Others;cos#theta;",nbins_ang,ang_min,ang_max);
	TH1D h1o("h1o","Others;argcos#theta[degree];",pnbins_ang,pang_min,pang_max);

	TH1D h1cos_c("h1cos_c","charged particle(all of partner track);cos#theta;",nbins_ang,ang_min,ang_max);
	TH1D h1c("h1c","charged particle(all partner track);argcos#theta[degree];",pnbins_ang,pang_min,pang_max);

	Int_t ecc,gid,cid,utime,pid,vpl,ntrk,pl0,pl1,rid,nseg,npl,vph;
	Double_t vx,vy,vz,dz,ip,mu_likelihood,p_likelihood,w;
	Double_t ax,ay,x,y,z;
	Double_t mux,muy,az;
	Double_t cos,arccos;

	Int_t bunch,material,ntrk_all,stop_flg,charge,BMflg,stopflg;
	Double_t MCS,MCSerrl,MCSerrh,BMrng,BMrngerrl,BMrngerrh,BMcur,BMcurerrl,BMcurerrh,pb,md,oa;
	w = 1.0000;
	int cnt=0;
	std::ifstream ifs(input);
	while(ifs>>ecc>>gid>>utime>>bunch>>vpl>>material>>ntrk>>ntrk_all>>vx>>vy>>vz>>dz>>cid>>pid>>stopflg>>
		charge>>MCS>>MCSerrl>>MCSerrh>>BMflg>>BMrng>>BMrngerrl>>BMrngerrh>>BMcur>>BMcurerrl>>BMcurerrh>>mu_likelihood>>p_likelihood>>
		pb>>nseg>>npl>>pl0>>pl1>>rid>>vph>>ax>>ay>>x>>y>>z>>ip>>md>>oa){

		if(material!=matflg)continue;// vertex material 0:water,2:iron, <0 : sandmuon, 2> :pack,base,etc.
		if(pid!=13&&charge<pflg)continue;//-5:range-momentum cut, -10:manual check, -1 remain
		if(ax*ax+ay*ay>4.0*4.0)continue;


		//if(ax*ax>5*5.0||ay*ay>5*5.0)continue;
		mux=0;
		muy=0;
        az=1;
		
		if(pid==13){
			//1/sqrt(ax*ax+ay*ay+1);
			cos=(ax*mux+ay*muy+1)/sqrt(ax*ax+ay*ay+1)/sqrt(mux*mux+muy*muy+1);
			arccos=acos(cos)*180/TMath::Pi();
			h1cos_mu.Fill(cos,w);
			h1mu.Fill(arccos,w);
			cnt++;
		}
		else if(pid==2212){
			//proton
			if(vpl-pl1>=0){
				//fwd

			}
			else{
				//bwd
				ax=-ax;
				ay=-ay;
				az=-1;
				//std::cout<<vpl<<" "<<pl<<" "<<cos<<std::endl;
			}
			cos=(ax*mux+ay*muy+az)/sqrt(ax*ax+ay*ay+1)/sqrt(mux*mux+muy*muy+1);
			arccos=acos(cos)*180/TMath::Pi();
			//if(MCS>100){
				//if(arccos<80||arccos>100){
				h1cos_p.Fill(cos,w);
				h1p.Fill(arccos,w);
					//std::cout<<vpl<<" "<<pl1<<"\t"<<ax<<" "<<ay<<"\t"<<mux<<" "<<muy<<" "<<cos<<"\t"<<arccos<<"\t"<<mom<<std::endl;
				//}
			//}
		}
		else if(pid==211){
			//pion
			if(vpl-pl1>=0){
				//fwd

			}
			else{
				//bwd
				ax=-ax;
				ay=-ay;
				az=-1;
				//std::cout<<vpl<<" "<<pl<<" "<<cos<<std::endl;
			}
			cos=(ax*mux+ay*muy+az)/sqrt(ax*ax+ay*ay+1)/sqrt(mux*mux+muy*muy+1);
			arccos=acos(cos)*180/TMath::Pi();

			//if(MCS>100){
				//if(arccos<80||arccos>100){
					h1cos_pi.Fill(cos,w);
					h1pi.Fill(arccos,w);
				//}
			//}
		}
		else{
			//cannot distinguish
			if(vpl-pl1>=0){
				//fwd

			}
			else{
				//bwd
				ax=-ax;
				ay=-ay;
				az=-1;
				//std::cout<<vpl<<" "<<pl<<" "<<cos<<std::endl;
			}
			cos=(ax*mux+ay*muy+az)/sqrt(ax*ax+ay*ay+1)/sqrt(mux*mux+muy*muy+1);
			arccos=acos(cos)*180/TMath::Pi();
			h1cos_o.Fill(cos,w);
			h1o.Fill(arccos,w);
		}

		if(pid!=13){
			//cannot distinguish
			if(vpl-pl1>=0){
				//fwd

			}
			else{
				//bwd
				ax=-ax;
				ay=-ay;
				az=-1;
				//std::cout<<vpl<<" "<<pl<<" "<<cos<<std::endl;
			}
			cos=(ax*mux+ay*muy+az)/sqrt(ax*ax+ay*ay+1)/sqrt(mux*mux+muy*muy+1);
			arccos=acos(cos)*180/TMath::Pi();
			h1cos_c.Fill(cos,w);
			h1c.Fill(arccos,w);
		}

	}
	std::cout<<" muon : "<< cnt << std::endl;

	//nt1.ResetBranchAddresses();

	TFile f(output,"RECREATE");
	h1cos_mu.Write();
	h1mu.Write();
	h1cos_p.Write();
	h1p.Write();
	h1cos_pi.Write();
	h1pi.Write();
	h1cos_o.Write();
	h1o.Write();

	h1cos_c.Write();
	h1c.Write();

}