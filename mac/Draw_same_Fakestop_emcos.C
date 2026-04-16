
void SetStyle()
{
	//gErrorIgnoreLevel = 2000 ;
	gStyle->SetGridColor(17) ;
	gStyle->SetPadGridX(1) ;
	gStyle->SetPadGridY(1) ;
	gPad->SetGrid();
	
	gStyle->SetTitleAlign(23);
	gStyle->SetTitleX(0.50);             //Title box(の左上角) の X 座標（Canvasの左下原点、0~1）
	gStyle->SetTitleY(0.985);         //Title box(の左上角) の Y 座標（Canvasの左下原点、0~1）
	//gStyle->SetTitleXSize(0.15);
	//gStyle->SetTitleYSize(0.05);
	gStyle->SetTitleOffset(0.75, "XY");

	//gStyle->SetOptStat("emou");
	gStyle->SetOptStat("e"); 
	gStyle->SetStatX(0.99);       //統計boxの右上角のX座標（左下を(0,0),右上を(1,1)）
	gStyle->SetStatY(0.99); 
	gStyle->SetStatH(0.30);
	gStyle->SetStatW(0.28) ;
	//gStyle->SetStatFontSize(0.04) ;
	//gStyle->SetOptFit(1) ;
	
	//c1->SetRightMargin(0.5);
	//c1->SetLeftMargin(0.5);
	gStyle->SetHistLineColor(kAzure-3);
	gStyle->SetHistLineWidth(2);
	gStyle->SetHistFillColor(kAzure-3);
	gStyle->SetHistFillStyle(3445);
	
	gStyle->SetMarkerColor(kPink-3);
	gStyle->SetMarkerStyle(3);
	gStyle->SetMarkerSize(2);
	
	c->Modified();
	c->Update();
	//	c->UseCurrentStyle();
}


void Legend(TH1D* Data, TH1D* MC)
{
	TLegend* legend = new TLegend(0.80, 0.75, 0.99, 0.90); 
	legend->AddEntry(Data,"Data","p"); // AddEntry( pointer , "interpretation" , "option" ) // option は　"f"=box, "l"="L"=line, "p"=marker
	legend->AddEntry(MC,"MC","l"); // AddEntry( pointer , "interpretation" , "option" ) // option は　"f"=box, "l"="L"=line, "p"=marker
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
	ys=y+y*0.30;
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
void StatsBoxData(TCanvas* c1, TH1D* hd)
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
void StatsBoxFake(TCanvas* c1, TH1D* hf)
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

void Draw_same_Fakestop_emcos(TString data1="", TString data2="", TString data3="", TString output=""){

    if(output==""){
        std::cerr << "usage: data.root mc.root fake.root out.pdf" << std::endl;
        exit(0);
    }
 //   TString data1,data2,data3,data0;
 //   data0.Form("%s.root",indata1.Data());// no cut
 //   data1.Form("%s.root",indata2.Data());// cut man-check-rej-trk
 //   data2.Form("%s.root",indata3.Data());// after fin chk
    //data3.Form("%s_cutall.root",indata.Data()); // only cut trk
    TFile *f_all = TFile::Open(data1);
    TFile *f_after_manchk = TFile::Open(data2);
    TFile *f_remain = TFile::Open(data3);
    
    TCanvas *c = new TCanvas("c","c",600,450);
   	c->Print( output + "[" , "pdf" ) ;
    SetStyle();
    gStyle->SetHistLineWidth(2);
    //c->SetRightMargin(0.15);
    proton(f_all,f_after_manchk,f_remain,c,output);
    pion(f_all,f_after_manchk,f_remain,c,output);
    others(f_all,f_after_manchk,f_remain,c,output);
    muon(f_all,f_after_manchk,f_remain,c,output);
   	c->Print( output + "]" , "pdf" ) ;

}

void proton(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{

    Int_t yd,yf,ymax;
    c->Clear();
    gPad->SetGrid();

    // Data
    org->cd();
    h1cos_p->SetMarkerColor(kPink-3);
    h1cos_p->SetMarkerStyle(8);
    h1cos_p->Draw();
    SetYMax(h1cos_p,ymax);


    THStack *hs = new THStack("hs","proton");
    // MC
    aftmanchk->cd();
    h1cos_p->SetLineColor(kAzure-3);
    h1cos_p->SetFillColor(kAzure-3);
    h1cos_p->SetFillStyle(3245);
    SetYMax(h1cos_p,yd);
    hs->Add(h1cos_p);

    // Fake
    remain->cd();
    h1cos_p->SetLineColor(kSpring - 1);
    h1cos_p->SetFillColor(kSpring - 1);
    h1cos_p->SetFillStyle(3445);
    SetYMax(h1cos_p,yf);
    hs->Add(h1cos_p);
    
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    hs->GetYaxis()->SetRangeUser(0,ymax);
    org->cd();
    h1cos_p->GetYaxis()->SetRangeUser(0,ymax);
    h1cos_p->Draw("E same");
 
    TLegend *le = new TLegend(0.85,0.65,0.98,0.98);
    org->cd();
    le->AddEntry(h1cos_p,"Data","p");
    aftmanchk->cd();
    le->AddEntry(h1cos_p,"True","f");
    remain->cd();
    le->AddEntry(h1cos_p,"Fake","f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);

}

void pion(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{
    Int_t yd,yf,ymax;
    c->Clear();
    gPad->SetGrid();
    // Data
    org->cd();
    h1cos_pi->SetMarkerColor(kPink-3);
    h1cos_pi->SetMarkerStyle(8);
    h1cos_pi->Draw();
    SetYMax(h1cos_pi,ymax);


    THStack *hs = new THStack("hs","pion");
    // MC
    aftmanchk->cd();
    h1cos_pi->SetLineColor(kAzure-3);
    h1cos_pi->SetFillColor(kAzure-3);
    h1cos_pi->SetFillStyle(3245);
    SetYMax(h1cos_pi,yf);
    hs->Add(h1cos_pi);

    // Fake
    remain->cd();
    h1cos_pi->SetLineColor(kSpring - 1);
    h1cos_pi->SetFillColor(kSpring - 1);
    h1cos_pi->SetFillStyle(3445);
    SetYMax(h1cos_pi,yd);
    hs->Add(h1cos_pi);
    
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    hs->GetYaxis()->SetRangeUser(0,ymax);
    org->cd();
    h1cos_pi->GetYaxis()->SetRangeUser(0,ymax);
    hs->Draw("E same");
    h1cos_pi->Draw("E same");

    TLegend *le = new TLegend(0.85,0.65,0.98,0.98);
    org->cd();
    le->AddEntry(h1cos_pi,"Data","p");
    aftmanchk->cd();
    le->AddEntry(h1cos_pi,"True","f");
    remain->cd();
    le->AddEntry(h1cos_pi,"Fake","f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);


}

void muon(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{

    Int_t yd,yf,ymax;
    c->Clear();
    gPad->SetGrid();
    // Data
    org->cd();
    h1cos_mu->SetMarkerColor(kPink-3);
    h1cos_mu->SetMarkerStyle(8);
    h1cos_mu->Draw("E");
    SetYMax(h1cos_mu,ymax);


    // MC
    aftmanchk->cd();
    h1cos_mu->SetLineColor(kAzure-3);
    h1cos_mu->SetFillColor(kAzure-3);
    h1cos_mu->SetFillStyle(3245);
    SetYMax(h1cos_mu,yd);
    ymax =comp_ymax(ymax,yd);
    h1cos_mu->GetYaxis()->SetRangeUser(0,ymax);
    h1cos_mu->Draw("");
    h1cos_mu->Draw("E same");
 
    org->cd();
    h1cos_mu->GetYaxis()->SetRangeUser(0,ymax);
    h1cos_mu->Draw("E same");
    h1cos_mu->Draw("E same");
 
    TLegend *le = new TLegend(0.85,0.75,0.98,0.90);
    org->cd();
    le->AddEntry(h1cos_mu,"Data","p");
    aftmanchk->cd();
    le->AddEntry(h1cos_mu,"True","f");

    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);

}

void others(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{
    Int_t yd,yf,ymax;

    // Data
    org->cd();
    h1cos_o->SetMarkerColor(kPink-3);
    h1cos_o->SetMarkerStyle(8);
    h1cos_o->Draw();
    SetYMax(h1cos_o,ymax);


    THStack *hs = new THStack("hs","Others");
    // MC
    aftmanchk->cd();
    h1cos_o->SetLineColor(kAzure-3);
    h1cos_o->SetFillColor(kAzure-3);
    h1cos_o->SetFillStyle(3245);
    SetYMax(h1cos_o,yd);
    hs->Add(h1cos_o);

    // Fake
    remain->cd();
    h1cos_o->SetLineColor(kSpring - 1);
    h1cos_o->SetFillColor(kSpring - 1);
    h1cos_o->SetFillStyle(3445);
    SetYMax(h1cos_o,yf);
    hs->Add(h1cos_o);
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    hs->GetYaxis()->SetRangeUser(0,ymax);
    org->cd();
    h1cos_o->GetYaxis()->SetRangeUser(0,ymax);
    hs->Draw("E same");
    h1cos_o->Draw("E same");
 
    TLegend *le = new TLegend(0.85,0.65,0.98,0.98);
    org->cd();
    le->AddEntry(h1cos_o,"Data","p");
    aftmanchk->cd();
    le->AddEntry(h1cos_o,"True","f");
    remain->cd();
    le->AddEntry(h1cos_o,"Fake","f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);


}