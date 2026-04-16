void SetStyle()
{
	//gErrorIgnoreLevel = 2000 ;
	gStyle->SetGridColor(17) ;
	gStyle->SetPadGridX(1) ;
	gStyle->SetPadGridY(1) ;
	gPad->SetGrid();
	
	gStyle->SetTitleAlign(23);
	gStyle->SetTitleSize(0.06);             //Title box(の左上角) の X 座標（Canvasの左下原点、0~1）
	gStyle->SetTitleX(0.50);             //Title box(の左上角) の X 座標（Canvasの左下原点、0~1）
	gStyle->SetTitleY(0.985);         //Title box(の左上角) の Y 座標（Canvasの左下原点、0~1）
	gStyle->SetTitleXSize(0.04);
	gStyle->SetTitleYSize(0.04);
	gStyle->SetTitleOffset(1.0, "X");
	gStyle->SetTitleOffset(1.4, "Y");

	//gStyle->SetOptStat("emou");
	gStyle->SetOptStat("e"); 
	gStyle->SetStatX(0.99);       //統計boxの右上角のX座標（左下を(0,0),右上を(1,1)）
	gStyle->SetStatY(0.99); 
	gStyle->SetStatH(0.30);
	gStyle->SetStatW(0.28) ;
	//gStyle->SetStatFontSize(0.04) ;
	//gStyle->SetOptFit(1) ;
	
	//c1->SetRightMargin(0.5);
	c->SetLeftMargin(0.13);
	gStyle->SetHistLineColor(kAzure-3);
	gStyle->SetHistLineWidth(2);
	gStyle->SetHistFillColor(kAzure-3);
	gStyle->SetHistFillStyle(3445);
	
	gStyle->SetMarkerColor(kPink-3);
	gStyle->SetMarkerStyle(3);
	gStyle->SetMarkerSize(1.5);
	
	c->Modified();
	c->Update();
	//	c->UseCurrentStyle();
}


void Legend(TH2D* sig, TH2D* noi)
{
	TLegend* legend = new TLegend(0.80, 0.63, 0.98, 0.78); 
	legend->AddEntry(sig,"Signal","p"); // AddEntry( pointer , "interpretation" , "option" ) // option は　"f"=box, "l"="L"=line, "p"=marker
	legend->AddEntry(noi,"Noise","p"); // AddEntry( pointer , "interpretation" , "option" ) // option は　"f"=box, "l"="L"=line, "p"=marker
	legend->Draw();
	//gPad->BuildLegend();
	//c->Update();
}
void SetYMax(TH1D* h,Int_t &yaxis_max)
{	//get most large bin entry
	Int_t tmp=0;
	for(Int_t i=0;i<=h->GetXaxis()->GetNbins();i++){
		
		if(tmp<h->GetBinContent(i)){
			tmp=h->GetBinContent(i);
		}
	}
	
	yaxis_max=tmp;
	cout<<"    Bin contents max : "<<tmp<<endl;
}

Int_t comp_ymax(Int_t y1,Int_t y2)
{
	Int_t ys,y=0;

	if(y1>=y2){
		y=y1;
	}
	else{
		y=y2;
	}
	
	cout<<"      Yaxis max "<<y<<" --> ";
	//	y=(y/10+1)*10;
	ys=y+y*0.15;
	if(ys==y){
		y=y*0.5;
		ys=ys+y;
		cout<<ys<<endl;
	}
	else{
		cout<<ys<<endl;
	}
	return ys;
}
void StatsBox1(TCanvas* c1, TH2D* hd)
{	
	c1->Update();
	TPaveStats *st = (TPaveStats*)hd->FindObject("stats");
	//st1->SetX1NDC(0.80); //x座標の始点、４行あるときの初期位置は0.78?
	//st1->SetX2NDC(0.98); //x座標の終点、４行あるときの初期位置は0.98?
	st->SetX1NDC(0.80); //x座標の始点、４行あるときの初期位置は0.78?
	st->SetX2NDC(0.98); //x座標の終点、４行あるときの初期位置は0.98?
	st->SetY1NDC(0.90); //y座標の始点、４行あるときの初期位置は0.775?
	st->SetY2NDC(0.98); //y座標の終点、４行あるときの初期位置は0.935?
	c1->Modified(); //オブジェクトの設定変更を伝える

}
void StatsBox2(TCanvas* c1, TH2D* hf)
{	
	c1->Update();
	TPaveStats *st1 = (TPaveStats*)hf->FindObject("stats");
	//st1->SetX1NDC(0.80); //x座標の始点、４行あるときの初期位置は0.78?
	//st1->SetX2NDC(0.98); //x座標の終点、４行あるときの初期位置は0.98?
	st1->SetX1NDC(0.80); //x座標の始点、４行あるときの初期位置は0.78?
	st1->SetX2NDC(0.98); //x座標の終点、４行あるときの初期位置は0.98?
	st1->SetY1NDC(0.80); //y座標の始点、４行あるときの初期位置は0.775?
	st1->SetY2NDC(0.88); //y座標の終点、４行あるときの初期位置は0.935?
	c1->Modified(); //オブジェクトの設定変更を伝える

}
void Plot_ip_vs_md(TTree *tree, TCanvas *c, TString output_path, Int_t pidflg, Double_t nbins, Double_t x_min, Double_t x_max, Double_t nbins, Double_t y_min,Double_t y_max);
void Plot_mom_vs_md(TTree *tree, TCanvas *c, TString output_path, Int_t pidflg, Double_t nbins, Double_t x_min, Double_t x_max, Double_t nbins, Double_t y_min,Double_t y_max);

void HistGram(TString indata = "", TString output = ""){

    if(output == ""){
        std::cerr << "usage: in_data.root output_path" << std::endl;
        exit(0);
    }

    TFile *file = new TFile(indata, "read");
    TTree *tree = static_cast<TTree*>(file->Get("tree"));

    TCanvas *c = new TCanvas("c","c",600,450);
   	//c->Print( output + "[" , "pdf" ) ;
    SetStyle();
    //c->Print( output + "]" , "pdf" ) ;
    c->cd();
    Plot_ip_vs_md(tree,c,output,2212,100,0,500,100,0,2400);
    Plot_ip_vs_md(tree,c,output,211,100,0,500,100,0,2400);
    Plot_ip_vs_md(tree,c,output,0,100,0,500,100,0,2400);

    Plot_mom_vs_md(tree,c,output,2212,100,0,1500,100,0,500);
    Plot_mom_vs_md(tree,c,output,211,100,0,800,100,0,800);
    Plot_mom_vs_md(tree,c,output,0,100,600,3000,100,0,500);

    Plot_length_vs_npl(tree,c,output,2212,100,0,1500,133,0,133);
    Plot_length_vs_npl(tree,c,output,211,100,0,800,133,0,133);
    Plot_length_vs_npl(tree,c,output,0,100,600,3000,133,0,133);
}
void Plot_ip_vs_md(TTree *tree, TCanvas *c, TString output_path, Int_t pidflg, Double_t nbins, Double_t x_min, Double_t x_max, Double_t nbins, Double_t y_min,Double_t y_max)
{

    TString htitle,pngname,output;
    TString str_sig,str_noi;
    TCut cut_sig, cut_noi;
    str_sig.Form("charge>-2&&pid==%d",pidflg);
    str_noi.Form("charge<-1&&pid==%d",pidflg);
    cut_sig = str_sig.Data();
    cut_noi = str_noi.Data();

    if(pidflg==211){
        htitle.Form("Pion;Minimum distance [#mum];Impact parameter [#mum]");
        pngname.Form("md_vs_ip_sn_pion.png");
    }
    else if(pidflg==2212){
        htitle.Form("Proton;Minimum distance [#mum];Impact parameter [#mum]");
        pngname.Form("md_vs_ip_sn_proton.png");
    }
    else if(pidflg==13){
        htitle.Form("Muon;Minimum distance [#mum];Impact parameter [#mum]");
        pngname.Form("md_vs_ip_sn_muon.png");
    }
    else{
        htitle.Form("Others;Minimum distance [#mum];Impact parameter [#mum]");
        pngname.Form("md_vs_ip_sn_others.png");
        str_sig.Form("charge>-2&&pid!=2212&&pid!=211&&pid!=13");
        str_noi.Form("charge<-1&&pid!=2212&&pid!=211&&pid!=13");
        cut_sig = str_sig.Data();
        cut_noi = str_noi.Data();
    }

    output.Form("%s/%s",output_path.Data(), pngname.Data());

    TH2D *sig = new TH2D("sig", htitle.Data(), nbins, x_min, x_max,nbins, y_min, y_max);
    TH2D *noi = new TH2D("noi", htitle.Data(), nbins, x_min, x_max,nbins, y_min, y_max);

    tree->Draw("ip:md>>sig", cut_sig, "colz");
    tree->Draw("ip:md>>noi", cut_noi, "colz");

    noi->SetMarkerColor(kAzure);
    noi->SetMarkerStyle(24);
    StatsBox2(c,noi);

    sig->SetMarkerColor(kPink);
    sig->SetMarkerStyle(3);
    sig->Draw();
    StatsBox1(c,sig);
    noi->Draw("same");
    gPad->Update(); 
    Legend(sig,noi);
    c->SaveAs(output);
    c->Clear();
}


void Plot_mom_vs_md(TTree *tree, TCanvas *c, TString output_path, Int_t pidflg, Double_t nbins, Double_t x_min, Double_t x_max, Double_t nbins, Double_t y_min,Double_t y_max)
{
    TString htitle,pngname,output;
    TString str_sig,str_noi;
    TCut cut_sig, cut_noi;
    str_sig.Form("charge>-2&&pid==%d",pidflg);
    str_noi.Form("charge<-1&&pid==%d",pidflg);
    cut_sig = str_sig.Data();
    cut_noi = str_noi.Data();

    if(pidflg==211){
        htitle.Form("Pion;MCS [MeV/c];Minimum distance [#mum]");
        pngname.Form("MCS_vs_md_sn_pion.png");
    }
    else if(pidflg==2212){
        htitle.Form("Proton;MCS [MeV/c];Minimum distance [#mum]");
        pngname.Form("MCS_vs_md_sn_proton.png");
    }
    else if(pidflg==13){
        htitle.Form("Muon;MCS [MeV/c];Minimum distance [#mum]");
        pngname.Form("MCS_vs_md_sn_muon.png");
    }
    else{
        htitle.Form("Others;MCS [MeV/c];Minimum distance [#mum]");
        pngname.Form("MCS_vs_md_sn_others.png");
        str_sig.Form("charge>-2&&pid!=2212&&pid!=211&&pid!=13");
        str_noi.Form("charge<-1&&pid!=2212&&pid!=211&&pid!=13");
        cut_sig = str_sig.Data();
        cut_noi = str_noi.Data();
    }

    output.Form("%s/%s",output_path.Data(), pngname.Data());

    TH2D *sig = new TH2D("sig",htitle.Data(), nbins, x_min, x_max,nbins, y_min, y_max);
    TH2D *noi = new TH2D("noi",htitle.Data(), nbins, x_min, x_max,nbins, y_min, y_max);

    tree->Draw("md:MCS>>sig", cut_sig, "colz");
    tree->Draw("md:MCS>>noi", cut_noi, "colz");

    noi->SetMarkerColor(kAzure);
    noi->SetMarkerStyle(24);
    StatsBox2(c,noi);
    sig->SetMarkerColor(kPink);
    sig->SetMarkerStyle(3);
    sig->Draw();
    StatsBox1(c,sig);
    noi->Draw("same");
    Legend(sig,noi);
    c->SaveAs(output);
    c->Clear();

}

void Plot_length_vs_npl(TTree *tree, TCanvas *c, TString output_path, Int_t pidflg, Double_t nbins, Double_t x_min, Double_t x_max, Double_t nbins, Double_t y_min,Double_t y_max)
{
    TString htitle,pngname,output;
    TString str_sig,str_noi;
    TCut cut_sig, cut_noi;
    str_sig.Form("charge>-2&&pid==%d",pidflg);
    str_noi.Form("charge<-1&&pid==%d",pidflg);
    cut_sig = str_sig.Data();
    cut_noi = str_noi.Data();

    if(pidflg==211){
        htitle.Form("Pion;MCS [MeV/c];npl");
        pngname.Form("MCS_vs_npl_sn_pion.png");
    }
    else if(pidflg==2212){
        htitle.Form("Proton;MCS [MeV/c];npl");
        pngname.Form("MCS_vs_npl_sn_proton.png");
    }
    else if(pidflg==13){
        htitle.Form("Muon;MCS [MeV/c];npl");
        pngname.Form("MCS_vs_npl_sn_muon.png");
    }
    else{
        htitle.Form("Others;MCS [MeV/c];npl");
        pngname.Form("MCS_vs_npl_sn_others.png");
        str_sig.Form("charge>-2&&pid!=2212&&pid!=211&&pid!=13");
        str_noi.Form("charge<-1&&pid!=2212&&pid!=211&&pid!=13");
        cut_sig = str_sig.Data();
        cut_noi = str_noi.Data();
    }

    output.Form("%s/%s",output_path.Data(), pngname.Data());

    TH2D *sig = new TH2D("sig",htitle.Data(), nbins, x_min, x_max,nbins, y_min, y_max);
    TH2D *noi = new TH2D("noi",htitle.Data(), nbins, x_min, x_max,nbins, y_min, y_max);

    tree->Draw("npl:MCS>>sig", cut_sig, "colz");
    tree->Draw("npl:MCS>>noi", cut_noi, "colz");

    noi->SetMarkerColor(kAzure);
    noi->SetMarkerStyle(24);
    StatsBox2(c,noi);
    sig->SetMarkerColor(kPink);
    sig->SetMarkerStyle(3);
    sig->Draw();
    StatsBox1(c,sig);
    noi->Draw("same");
    Legend(sig,noi);
    c->SaveAs(output);
    c->Clear();
}