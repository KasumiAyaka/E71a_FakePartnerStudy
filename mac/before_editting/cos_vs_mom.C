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

void cos_vs_mom(TString indata="", TString in_mc="", TString output=""){

    if(output==""){
        std::cerr << "usage: in_data.root in_mc.root out.pdf" << std::endl;
        exit(0);
    }

    TFile *f_data = TFile::Open(indata);
    TFile *f_mc = TFile::Open(in_mc);
    
    TCanvas *c = new TCanvas("c","c",600,450);
   	c->Print( output + "[" , "pdf" ) ;
    SetStyle();

    proton(f_data,f_mc,c,output);
    pion(f_data,f_mc,c,output);
   	c->Print( output + "]" , "pdf" ) ;

}
void proton(TFile *data,TFile *mc,TCanvas *c, TString output){

    Int_t yd,yf,ymax;
    c->Clear();
    gPad->SetGrid();

    // mc
    mc->cd();
    h1cos_p->Draw("colz");

    // data
    data->cd();
    grp->Draw("P same");

    c->Update();
	c->Print(output);

}

void pion(TFile *data,TFile *mc,TCanvas *c, TString output){

    Int_t yd,yf,ymax;
    c->Clear();
    gPad->SetGrid();

    // mc
    mc->cd();
    h1cos_pi->Draw("colz");

    // data
    data->cd();
    grpi->Draw("P same");

    c->Update();
	c->Print(output);

}
