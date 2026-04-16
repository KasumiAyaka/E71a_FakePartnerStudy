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
	gStyle->SetStatW(0.22) ;
	//gStyle->SetStatFontSize(0.04) ;
	//gStyle->SetOptFit(1) ;
	
	//c1->SetRightMargin(0.5);
	c->SetLeftMargin(0.07);
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

void mkpl_vtx_dz(Int_t eccnum = 0){

    if(eccnum == 0){
        std::cerr << "usage: eccnum" << std::endl;
        exit(0);
    }

    TString all,manchk,rngmom,output0,output1,output2,mat;
    TCanvas *c = new TCanvas("c","c",600,450);
   	//c->Print( output + "[" , "pdf" ) ;


    mat.Form("water");
    all.Form("ECC%d/data/%s.root",eccnum,mat.Data());
    manchk.Form("ECC%d/data_alltrk/%s_manchkcut.root",eccnum,mat.Data());
    rngmom.Form("ECC%d/data_alltrk/%s_manchk_momrngcut.root",eccnum,mat.Data());

    TFile *file0 = new TFile(all, "read");
    TFile *file1 = new TFile(manchk, "read");
    TFile *file2 = new TFile(rngmom, "read");

    TTree *t_all = static_cast<TTree*>(file0->Get("tree"));
    TTree *t_manchk = static_cast<TTree*>(file1->Get("tree"));
    TTree *t_rngmom = static_cast<TTree*>(file2->Get("tree"));

    output0.Form("ECC%d/plot_alltrk/%s/dz_of_material.png",eccnum,mat.Data());
    output1.Form("ECC%d/plot_alltrk/%s/dz_of_material_manchk_cut.png",eccnum,mat.Data());
    output2.Form("ECC%d/plot_alltrk/%s/dz_of_material_manchk_momrng_cut.png",eccnum,mat.Data());

    SetStyle();
    Draw_all_water(t_all,c,output0);
    Draw_cut_water(t_manchk,c,output1);
    Draw_cut_water(t_rngmom,c,output2);
    
    mat.Form("iron");
    all.Form("ECC%d/data/%s.root",eccnum,mat.Data());// no cut
    manchk.Form("ECC%d/data_alltrk/%s_manchkcut.root",eccnum,mat.Data());// man cut
    rngmom.Form("ECC%d/data_alltrk/%s_manchk_momrngcut.root",eccnum,mat.Data());// mom cut

    TFile *file0 = new TFile(all, "read");
    TFile *file1 = new TFile(manchk, "read");
    TFile *file2 = new TFile(rngmom, "read");

    TTree *t_all = static_cast<TTree*>(file0->Get("tree"));
    TTree *t_manchk = static_cast<TTree*>(file1->Get("tree"));
    TTree *t_rngmom = static_cast<TTree*>(file2->Get("tree"));

    output0.Form("ECC%d/plot_alltrk/%s/dz_of_material.png",eccnum,mat.Data());
    output1.Form("ECC%d/plot_alltrk/%s/dz_of_material_manchk_cut.png",eccnum,mat.Data());
    output2.Form("ECC%d/plot_alltrk/%s/dz_of_material_manchk_momrng_cut.png",eccnum,mat.Data());

    Draw_all_iron(t_all,c,output0);
    Draw_cut_iron(t_manchk,c,output1);
    Draw_cut_iron(t_rngmom,c,output2);
    //c->Print( output + "]" , "pdf" ) ;
    c->cd();
}
void Draw_all_water(TTree *tree, TCanvas *c, TString output)
{
    Int_t n;
    TString nwt,nIr,nbs,nem;
    THStack *hs = new THStack("hs","dz ( -->#nu); [#mum];");

    tree->Draw("dz>>wt(100,-3500,100)","pid==13&&ntrk_all>1&&material==0");
    tree->Draw("dz>>Ir(100,-3500,100)","pid==13&&ntrk_all>1&&material==2");
    tree->Draw("dz>>em(100,-3500,100)","pid==13&&ntrk_all>1&&material==5");
    tree->Draw("dz>>bs(100,-3500,100)","pid==13&&ntrk_all>1&&material==1");
    gStyle->SetGridColor(17);
    gPad->SetGrid();

    wt->SetFillColor(kAzure-3);
    wt->SetFillStyle(3002);
    wt->Draw();
    wt->SetTitle("dz ( -->#nu); [#mum];");
    n = wt->GetEntries();
    nwt.Form("water %d events", n);

    Ir->SetFillColor(kPink-3);
    Ir->SetFillStyle(3001);
    Ir->Draw("same");
    n = Ir->GetEntries();
    nIr.Form("Iron %d events", n);
    n = Ir->GetEntries();
    nIr.Form("Iron %d events", n);

    em->SetFillColor(kTeal-3);
    em->SetFillStyle(3001);
    em->Draw("same");
    n = em->GetEntries();
    nem.Form("emulsion %d events", n);

    bs->SetFillColor(kYellow);
    bs->SetFillStyle(3001);
    bs->Draw("same");
    n = bs->GetEntries();
    nbs.Form("base %d events", n);
    n = bs->GetEntries();
    nbs.Form("base %d events", n);

    hs->Add(wt);
    hs->Add(Ir);
    hs->Add(em);
    hs->Add(bs);
    hs->Draw();
    Draw_mat_boader_water();

    TLegend *leg =  new TLegend(0.08,0.72,0.40,0.99);
    leg->AddEntry("wt",nwt.Data(),"f");
    leg->AddEntry("Ir",nIr.Data(),"f");
    leg->AddEntry("em",nem.Data(),"f");
    leg->AddEntry("bs",nbs.Data(),"f");
    leg->Draw();



    c->SaveAs(output);
    c->Clear();

}
void Draw_cut_water(TTree *tree, TCanvas *c, TString output)
{
    Int_t n;
    TString nwt,nIr,nbs,nem;
    tree->Draw("dz>>wt(100,-3500,100)","pid==13&&ntrk>1&&material==0");
    tree->Draw("dz>>Ir(100,-3500,100)","pid==13&&ntrk>1&&material==2");
    tree->Draw("dz>>em(100,-3500,100)","pid==13&&ntrk>1&&material==5");
    tree->Draw("dz>>bs(100,-3500,100)","pid==13&&ntrk>1&&material==1");
    gStyle->SetGridColor(17);
    gPad->SetGrid();

    wt->SetFillColor(kAzure-3);
    wt->SetFillStyle(3002);
    wt->Draw();
    wt->SetTitle("dz ( -->#nu); [#mum];");
    n = wt->GetEntries();
    nwt.Form("water %d events", n);

    Ir->SetFillColor(kPink-3);
    Ir->SetFillStyle(3001);
    Ir->Draw("same");
    n = Ir->GetEntries();
    nIr.Form("Iron %d events", n);

    em->SetFillColor(kTeal-3);
    em->SetFillStyle(3001);
    em->Draw("same");
    n = em->GetEntries();
    nem.Form("emulsion %d events", n);


    bs->SetFillColor(kYellow);
    bs->SetFillStyle(3001);
    bs->Draw("same");
    n = bs->GetEntries();
    nbs.Form("base %d events", n);

    THStack *hs = new THStack("hs","dz ( -->#nu); [#mum];");
    hs->Add(wt);
    hs->Add(Ir);
    hs->Add(em);
    hs->Add(bs);
    hs->Draw();
    Draw_mat_boader_water();

    TLegend *leg =  new TLegend(0.08,0.72,0.40,0.99);
    leg->AddEntry("wt",nwt.Data(),"f");
    leg->AddEntry("Ir",nIr.Data(),"f");
    leg->AddEntry("em",nem.Data(),"f");
    leg->AddEntry("bs",nbs.Data(),"f");
    leg->Draw();


    c->SaveAs(output);
    c->Clear();

}    // man chk cut

// iron
void Draw_all_iron(TTree *tree, TCanvas *c, TString output)
{
    Int_t n;
    TString nwt,nIr,nbs,nem;
    // iron
    //data_alltrk
    tree->Draw("dz>>wt(75,-1200,100)","pid==13&&ntrk_all>1&&material==0");
    tree->Draw("dz>>Ir(75,-1200,100)","pid==13&&ntrk_all>1&&material==2");
    tree->Draw("dz>>em(75,-1200,100)","pid==13&&ntrk_all>1&&material==5");
    tree->Draw("dz>>bs(75,-1200,100)","pid==13&&ntrk_all>1&&material==1");


    Ir->SetFillColor(kPink-3);
    Ir->SetFillStyle(3002);
    Ir->Draw();
    n = Ir->GetEntries();
    nIr.Form("Iron %d events", n);

    wt->SetFillColor(kAzure-3);
    wt->SetFillStyle(3001);
    wt->Draw("same");
    wt->SetTitle("dz ( -->#nu); [#mum];");
    n = wt->GetEntries();
    nwt.Form("water %d events", n);

    em->SetFillColor(kTeal-3);
    em->SetFillStyle(3001);
    em->Draw("same");
    n = em->GetEntries();
    nem.Form("emulsion %d events", n);


    bs->SetFillColor(kYellow);
    bs->SetFillStyle(3001);
    bs->Draw("same");
    n = bs->GetEntries();
    nbs.Form("base %d events", n);

    THStack *hs = new THStack("hs","dz ( -->#nu); [#mum];");
    hs->Add(wt);
    hs->Add(Ir);
    hs->Add(em);
    hs->Add(bs);
    hs->Draw();
    Draw_mat_boader_iron();

    TLegend *leg =  new TLegend(0.08,0.72,0.40,0.99);
    leg->AddEntry("Ir",nIr.Data(),"f");
    leg->AddEntry("wt",nwt.Data(),"f");
    leg->AddEntry("em",nem.Data(),"f");
    leg->AddEntry("bs",nbs.Data(),"f");
    leg->Draw();



    c->SaveAs(output);
    c->Clear();
}

// iron
void Draw_cut_iron(TTree *tree, TCanvas *c, TString output)
{
    Int_t n;
    TString nwt,nIr,nbs,nem;
    // iron
    //data_alltrk
    tree->Draw("dz>>wt(75,-1200,100)","pid==13&&ntrk>1&&material==0");
    tree->Draw("dz>>Ir(75,-1200,100)","pid==13&&ntrk>1&&material==2");
    tree->Draw("dz>>em(75,-1200,100)","pid==13&&ntrk>1&&material==5");
    tree->Draw("dz>>bs(75,-1200,100)","pid==13&&ntrk>1&&material==1");

    gStyle->SetGridColor(17);
    gPad->SetGrid();

    Ir->SetFillColor(kPink-3);
    Ir->SetFillStyle(3002);
    Ir->Draw();
    n = Ir->GetEntries();
    nIr.Form("Iron %d events", n);

    wt->SetFillColor(kAzure-3);
    wt->SetFillStyle(3001);
    wt->Draw("same");
    wt->SetTitle("dz ( -->#nu); [#mum];");
    n = wt->GetEntries();
    nwt.Form("water %d events", n);

    em->SetFillColor(kTeal-3);
    em->SetFillStyle(3001);
    em->Draw("same");
    n = em->GetEntries();
    nem.Form("emulsion %d events", n);


    bs->SetFillColor(kYellow);
    bs->SetFillStyle(3001);
    bs->Draw("same");
    n = bs->GetEntries();
    nbs.Form("base %d events", n);


    THStack *hs = new THStack("hs","dz ( -->#nu); [#mum];");
    hs->Add(wt);
    hs->Add(Ir);
    hs->Add(em);
    hs->Add(bs);
    hs->Draw();
    Draw_mat_boader_iron();

    TLegend *leg =  new TLegend(0.08,0.72,0.40,0.99);
    leg->AddEntry("Ir",nIr.Data(),"f");
    leg->AddEntry("wt",nwt.Data(),"f");    
    leg->AddEntry("em",nem.Data(),"f");
    leg->AddEntry("bs",nbs.Data(),"f");
    leg->Draw();



    c->SaveAs(output);
    c->Clear();
}
void Draw_mat_boader_water(){
    TLine *l = new TLine(0,0,0,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-70,0,-70,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-179,0,-179,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-2479,0,-2479,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-2588,0,-2588,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-2658,0,-2658,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-2868,0,-2868,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();


    TLine *l = new TLine(-2938,0,-2938,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();


    TLine *l = new TLine(-3438,0,-3438,4.2);
    l->SetLineColor(kGray+1);
    l->Draw();
}
void Draw_mat_boader_iron(){

    TLine *l = new TLine(0,0,0,5);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-70,0,-70,5);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-570,0,-570,5);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-640,0,-640,5);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-850,0,-850,5);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-920,0,-920,5);
    l->SetLineColor(kGray+1);
    l->Draw();

    TLine *l = new TLine(-1029,0,-1029,5);
    l->SetLineColor(kGray+1);
    l->Draw();

}
