void Draw_multiplicity_hist(TString input="",TString output=""){

    if(output==""){
        std::cerr << "usage: input-root-file.root output-png-name.png" << std::endl;
        exit(0);
    }

    TFile *f = new TFile(input, "read");
    TTree *t = static_cast<TTree*>(f->Get("tree"));

    TCanvas *c=new TCanvas("c","c",1600,900);
    c->Divide(2,2);
    c->cd(1);
    h1p->Draw();
    h1p->SetFillStyle(3002);
    h1p->SetFillColor(kAzure-3);
    gStyle->SetGridColor(17);
    gStyle->SetGridStyle(2);
    gPad->SetGrid();

    c->cd(2);
    h1pi->Draw();
    h1pi->SetFillColor(kAzure-3);
    h1pi->SetFillStyle(3002);
    gPad->SetGrid();

    c->cd(3);
    h1o->Draw();
    h1o->SetFillColor(kAzure-3);
    h1o->SetFillStyle(3002);
    gPad->SetGrid();

    c->cd(4);
    h1c->Draw();
    h1c->SetFillStyle(3002);
    h1c->SetFillColor(kAzure-3);
    gPad->SetGrid();

    c->SaveAs(output);

}