Double_t nbins_ang = 20. ;
Double_t ang_min = -1.0 ;
Double_t ang_max = 1.0 ;
Double_t pnbins_ang = 18. ;
Double_t pang_min = 0.0 ;
Double_t pang_max = 180.0 ;
Double_t nbins_mom = 50. ;
Double_t mom_min = 0.0 ;
Double_t mom_max = 1000.0 ;

void mkrf_emission_angle_tgraph(TString input="",TString output=""){
	

	//nt1.ReadFile(input);
	Int_t ecc,gid,cid,utime,pid,vpl,ntrk,pl0,pl1,rid,nseg,npl,vph;
	Double_t vx,vy,vz,dz,ip,mom,mu_likelihood,p_likelihood,w;
	Double_t ax,ay,x,y,z;
	Double_t mux,muy,az;
	Double_t cos,arccos;
	w = 1.0000;
	Int_t bunch,material,ntrk_all,stop_flg,charge,BMflg,stopflg;
	Double_t MCS,MCSerrl,MCSerrh,BMrng,BMrngerrl,BMrngerrh,BMcur,BMcurerrl,BMcurerrh,pb;

	const Int_t NPOINT=56;
	const Int_t pi_NPOINT=30;
	Double_t p_cos[NPOINT],p_mom[NPOINT],pi_cos[pi_NPOINT],pi_mom[pi_NPOINT];
	Int_t pcnt=0;
	Int_t picnt=0;
	std::ifstream ifs(input);
	//ecc/I:eid/I:utime/I:vpl/I:ntrk/I:vx/D:vy/D:vz/D:dz/D:cid/I:pl0/I:pl1/I:rid/I:nseg/I:npl/I:vph/I:pid/I:ax/D:ay/D:x/D:y/D:z/D:ip/D:mom/D:mu_likelihood/D:p_likelihood/D:w/D");
	while(ifs>>ecc>>gid>>utime>>bunch>>vpl>>material>>ntrk>>ntrk_all>>vx>>vy>>vz>>dz>>cid>>pid>>stopflg>>
		charge>>MCS>>MCSerrl>>MCSerrh>>BMflg>>BMrng>>BMrngerrl>>BMrngerrh>>BMcur>>BMcurerrl>>BMcurerrh>>mu_likelihood>>p_likelihood>>
		pb>>nseg>>npl>>pl0>>pl1>>rid>>vph>>ax>>ay>>x>>y>>z>>ip){

		std::cout<<pid<<std::endl;
		// dz cut
		//if(dz < -1900 || dz > -400)continue;
		//if(ntrk == 1)continue;
		// short partner cut
		//if(npl < 11)continue;
		// fillfactor cut
		//if( nseg / npl < 0.90 && pid != 13)continue;
		// multiplicity cut
		//if( ntrk - 1 > 3)continue;
		if(pid!=13&&charge<-1)continue;

		if(ax*ax>4*4.0||ay*ay>4*4.0)continue;
		mux=0;
		muy=0;
        az=1;
		
		if(pid==13){
			//mux=ax;
			//muy=ay;
			cos=(ax*mux+ay*muy+1)/sqrt(ax*ax+ay*ay+1)/sqrt(mux*mux+muy*muy+1);
			arccos=acos(cos)*180/TMath::Pi();
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
			if(mom>100){
				if(arccos<80||arccos>100){
					p_cos[pcnt]=cos;
					p_mom[pcnt]=mom;
					pcnt++;
				}
			}
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

			if(mom>100){
				if(arccos<80||arccos>100){
					pi_cos[picnt]=cos;
					pi_mom[picnt]=mom;
					picnt++;
				}
			}
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
		}

	}

	std::cout << "proton : " << pcnt << std::endl;
	std::cout << "pion   : " << picnt << std::endl;
	//nt1.ResetBranchAddresses();

	TGraph *grp = new TGraph(NPOINT, p_mom, p_cos);
	grp->SetTitle(" Proton ; Momentum [MeV/c]; cos#theta");
	grp->GetXaxis()->SetRangeUser(0,2000);
	grp->GetYaxis()->SetRangeUser(-1,1);
	grp->SetMarkerStyle(20);
	grp->SetMarkerColor(1);
	grp->Draw("AP");
	grp->SetName("grp");
	
	TGraph *grpi = new TGraph(pi_NPOINT, pi_mom, pi_cos);
	grpi->SetTitle(" Pion ; Momentum [MeV/c]; cos#theta");
	grpi->GetXaxis()->SetRangeUser(0,2000);
	grpi->GetYaxis()->SetRangeUser(-1,1);
	grpi->SetMarkerStyle(20);
	grpi->SetMarkerColor(1);
	grpi->Draw("AP");
	grpi->SetName("grpi");

	TFile f(output,"RECREATE");
	grp->Write();
	grpi->Write();

}