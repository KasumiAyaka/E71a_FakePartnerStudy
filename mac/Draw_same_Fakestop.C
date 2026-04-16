
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

void Draw_same_Fakestop(TString data1="", TString data2="", TString data3="", TString output=""){

    if(output==""){
        std::cerr << "usage: data.root mc.root fake.root out.pdf" << std::endl;
        exit(0);
    }
 //   TString data1,data2,data3,data0;
 //   data0.Form("%s.root",indata1.Data());// no cut
 //   data1.Form("%s.root",indata2.Data());// cut man-check-rej-trk
 //   data2.Form("%s.root",indata3.Data());// after fin chk
    //data3.Form("%s_cutall.root",indata.Data()); // only cut trk
    TFile *f_all = TFile::Open(data1);//data
    TFile *f_after_manchk = TFile::Open(data2);//mc
    TFile *f_remain = TFile::Open(data3);//fake
    
    TCanvas *c = new TCanvas("c","c",600,450);
   	c->Print( output + "[" , "pdf" ) ;
    SetStyle();
    gStyle->SetHistLineWidth(2);
    //c->SetRightMargin(0.15);
    proton(f_all,f_after_manchk,f_remain,c,output);
    pion(f_all,f_after_manchk,f_remain,c,output);
    others(f_all,f_after_manchk,f_remain,c,output);
    partners(f_all,f_after_manchk,f_remain,c,output);
    muon(f_all,f_after_manchk,f_remain,c,output);
   	c->Print( output + "]" , "pdf" ) ;

}

void proton(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{

    Int_t yd,yf,ymax;
    Int_t n1,n2,n3;
    TString name1,name2,name3;
    c->Clear();
    gPad->SetGrid();

    // Data
    org->cd();
    h1p->SetMarkerColor(kPink-3);
    h1p->SetLineColor(kPink-3);
    h1p->SetMarkerStyle(8);
    h1p->Draw();
    n1=h1p->GetEntries();
    SetYMax(h1p,ymax);


    THStack *hs = new THStack("hs","proton");
    // MC
    aftmanchk->cd();
    h1p->SetLineColor(kAzure-3);
    h1p->SetFillColor(kAzure-3);
    h1p->SetFillStyle(3245);
    n2=h1p->GetEntries();
    SetYMax(h1p,yd);
    hs->Add(h1p);

    // Fake
    remain->cd();
    h1p->SetLineColor(kSpring - 1);
    h1p->SetFillColor(kSpring - 1);
    h1p->SetFillStyle(3445);
    n3=h1p->GetEntries();
    SetYMax(h1p,yf);
    hs->Add(h1p);
    
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    //hs->GetYaxis()->SetRangeUser(0,ymax);
    hs->SetMinimum(0.0);
    hs->SetMaximum(ymax);
    //hs->SetBinErrorOption(TH1::kPoisson);
    org->cd();
    h1p->GetYaxis()->SetRangeUser(0,ymax);
    h1p->SetBinErrorOption(TH1::kPoisson);
    hs->Draw("E1 same");
    h1p->Draw("E same");

    name1.Form("Data %d trks",n1);
    name2.Form("True %d trks",n2 * 83 / 77);
    name3.Form("Fake %d trks",n3 * 83 / 77);

    TLegend *le = new TLegend(0.78,0.65,0.98,0.98);
    //org->cd();
    //le->AddEntry(h1p,"Data","p");
    //aftmanchk->cd();
    //le->AddEntry(h1p,"True","f");
    //remain->cd();
    //le->AddEntry(h1p,"Fake","f");
    org->cd();
    le->AddEntry(h1p,name1,"p");
    aftmanchk->cd();
    le->AddEntry(h1p,name2,"f");
    remain->cd();
    le->AddEntry(h1p,name3,"f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);

}

void pion(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{
    Int_t yd,yf,ymax;
    Int_t n1,n2,n3;
    TString name1,name2,name3;
    c->Clear();
    gPad->SetGrid();
    // Data
    org->cd();
    h1pi->SetMarkerColor(kPink-3);
    h1pi->SetLineColor(kPink-3);
    h1pi->SetMarkerStyle(8);
    h1pi->Draw();
    n1=h1pi->GetEntries();
    SetYMax(h1pi,ymax);


    THStack *hs = new THStack("hs","pion");
    // MC
    aftmanchk->cd();
    h1pi->SetLineColor(kAzure-3);
    h1pi->SetFillColor(kAzure-3);
    h1pi->SetFillStyle(3245);
    n2=h1pi->GetEntries();
    SetYMax(h1pi,yf);
    hs->Add(h1pi);

    // Fake
    remain->cd();
    h1pi->SetLineColor(kSpring - 1);
    h1pi->SetFillColor(kSpring - 1);
    h1pi->SetFillStyle(3445);
    n3=h1pi->GetEntries();
    SetYMax(h1pi,yd);
    hs->Add(h1pi);
    
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    hs->SetMinimum(0.0);
    hs->SetMaximum(ymax);
    org->cd();
    h1pi->GetYaxis()->SetRangeUser(0,ymax);
    h1pi->SetBinErrorOption(TH1::kPoisson);
    hs->Draw("E1 same");
    h1pi->Draw("E same");

    name1.Form("Data %d trks",n1);
    name2.Form("True %d trks",n2 * 83 / 77);
    name3.Form("Fake %d trks",n3 * 83 / 77);


    TLegend *le = new TLegend(0.78,0.65,0.98,0.98);
    org->cd();
    le->AddEntry(h1pi,name1,"p");
    aftmanchk->cd();
    le->AddEntry(h1pi,name2,"f");
    remain->cd();
    le->AddEntry(h1pi,name3,"f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);


}

void muon(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{

    Int_t yd,yf,ymax;
    Int_t n1,n2,n3;
    TString name1,name2,name3;
    c->Clear();
    gPad->SetGrid();
    // Data
    org->cd();
    h1mu->SetMarkerColor(kPink-3);
    h1mu->SetLineColor(kPink-3);
    h1mu->SetMarkerStyle(8);
    n1=h1mu->GetEntries();
    h1mu->Draw("E");
    SetYMax(h1mu,ymax);


    // MC
    aftmanchk->cd();
    h1mu->SetLineColor(kAzure-3);
    h1mu->SetFillColor(kAzure-3);
    h1mu->SetFillStyle(3245);
    n2=h1mu->GetEntries();
    SetYMax(h1mu,yd);
    ymax =comp_ymax(ymax,yd);
    h1mu->GetYaxis()->SetRangeUser(0,ymax);
    h1mu->Draw("");
    h1mu->Draw("E1 same");
    h1mu->SetBinErrorOption(TH1::kPoisson);
 
    org->cd();
    h1mu->GetYaxis()->SetRangeUser(0,ymax);
    h1mu->Draw("E same");
 

    name1.Form("Data %d trks",n1);
    name2.Form("True %d trks",n2 * 83 / 77);

    TLegend *le = new TLegend(0.78,0.75,0.98,0.90);
    org->cd();
    //le->AddEntry(h1mu,"Data","p");
    //aftmanchk->cd();
   // le->AddEntry(h1mu,"True","f");
    //org->cd();
    le->AddEntry(h1mu,name1,"p");
    aftmanchk->cd();
    le->AddEntry(h1mu,name2,"f");

    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);

}

void others(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{
    Int_t yd,yf,ymax;
    Int_t n1,n2,n3;
    TString name1,name2,name3;

    // Data
    org->cd();
    h1o->SetMarkerColor(kPink-3);
    h1o->SetLineColor(kPink-3);
    h1o->SetMarkerStyle(8);
    h1o->Draw();
    n1=h1o->GetEntries();
    SetYMax(h1o,ymax);


    THStack *hs = new THStack("hs","Others");
    // MC
    aftmanchk->cd();
    h1o->SetLineColor(kAzure-3);
    h1o->SetFillColor(kAzure-3);
    h1o->SetFillStyle(3245);
    n2=h1o->GetEntries();
    SetYMax(h1o,yd);
    hs->Add(h1o);

    // Fake
    remain->cd();
    h1o->SetLineColor(kSpring - 1);
    h1o->SetFillColor(kSpring - 1);
    h1o->SetFillStyle(3445);
    n3=h1o->GetEntries();
    SetYMax(h1o,yf);
    hs->Add(h1o);
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    hs->SetMinimum(0.0);
    hs->SetMaximum(ymax);
    org->cd();
    h1o->GetYaxis()->SetRangeUser(0,ymax);
    h1o->SetBinErrorOption(TH1::kPoisson);
    hs->Draw("E1 same");
    h1o->Draw("E same");
 

    name1.Form("Data %d trks",n1);
    name2.Form("True %d trks",n2 * 83 / 77);
    name3.Form("Fake %d trks",n3 * 83 / 77);

    TLegend *le = new TLegend(0.78,0.65,0.98,0.98);
    org->cd();
    org->cd();
    le->AddEntry(h1o,name1,"p");
    aftmanchk->cd();
    le->AddEntry(h1o,name2,"f");
    remain->cd();
    le->AddEntry(h1o,name3,"f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);


}


void partners(TFile *org, TFile *aftmanchk, TFile *remain, TCanvas *c, TString output)
{
    Int_t yd,yf,ymax;
    Int_t n1,n2,n3;
    TString name1,name2,name3;

    // Data
    org->cd();
    h1c->SetMarkerColor(kPink-3);
    h1c->SetLineColor(kPink-3);
    h1c->SetMarkerStyle(8);
    h1c->Draw();
    n1=h1c->GetEntries();
    SetYMax(h1c,ymax);


    THStack *hs = new THStack("hs","Partners");
    // MC
    aftmanchk->cd();
    h1c->SetLineColor(kAzure-3);
    h1c->SetFillColor(kAzure-3);
    h1c->SetFillStyle(3245);
    n2=h1c->GetEntries();
    SetYMax(h1c,yd);
    hs->Add(h1c);

    // Fake
    remain->cd();
    h1c->SetLineColor(kSpring - 1);
    h1c->SetFillColor(kSpring - 1);
    h1c->SetFillStyle(3445);
    n3=h1c->GetEntries();
    SetYMax(h1c,yf);
    hs->Add(h1c);
    hs->Draw();
    ymax =comp_ymax(ymax,yf+yd);
    hs->SetMinimum(0.0);
    hs->SetMaximum(ymax);
    org->cd();
    h1c->GetYaxis()->SetRangeUser(0,ymax);
    h1c->SetBinErrorOption(TH1::kPoisson);
    hs->Draw("E1 same");
    h1c->Draw("E same");
 

    name1.Form("Data %d trks",n1);
    name2.Form("True %d trks",n2 * 83 / 77);
    name3.Form("Fake %d trks",n3 * 83 / 77);

    TLegend *le = new TLegend(0.78,0.65,0.98,0.98);
    org->cd();
    le->AddEntry(h1c,name1,"p");
    aftmanchk->cd();
    le->AddEntry(h1c,name2,"f");
    remain->cd();
    le->AddEntry(h1c,name3,"f");
    le->SetFillColor(0);
    le->Draw();

    //c->SaveAs("Proton_multiplicity.png");
	c->Update();
	c->Print(output);


}