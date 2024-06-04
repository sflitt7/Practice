#include <TRandom.h>
#include <TMath.h>
void Gaus(Int_t n){
	TRandom r;
	TH1F* h1=new TH1F("h1","Resolution; x axis; y axis",100,90,110);
	TH1F* h2=new TH1F("h2","Resolution;x axis;y axis",100,90,110);

	
	for(Int_t i=0; i<n;i++){
	Double_t x1 = r.Gaus(100,3.25/2.35);
	Double_t x2 = r.Gaus(95.6,3.25/2.35);
	h1->Fill(x1);
	h2->Fill(x2);
	}

	
	TH1F* hAdd = new TH1F("hAdd","Resolution; Energy (MeV);Frequency",100,90,110);
	//below after h1,h2 are scaling factors
	hAdd->Add(h1,h2,1,0.2);

	hAdd->SetFillColor(38);

	TF1* f1 = new TF1("h","[0]*TMath::Gaus(x,[1],[2])+[3]*TMath::Gaus(x,[4],[5])",90,110);
	f1->SetParLimits(1,98,102);//function parameter number(from TF1 above),lower limit,upper limit
	f1->SetParLimits(2,3/2.35,3.5/2.35);		
	//f1->SetParLimits(3,,);
	f1->SetParLimits(4,92,100);	
	f1->SetParLimits(5,3/2.35,3.5/2.35);

	f1->SetLineColor(1);

	hAdd->Fit(f1);

	TF1* gaus1 = new TF1("gaus1","gaus",90,110);
	gaus1->SetLineColor(8);

	TF1* gaus2 = new TF1("gaus2","gaus",90,110);
	gaus2->SetLineColor(6);


	gaus1->FixParameter(0,f1->GetParameter(0));
	gaus1->FixParameter(1,f1->GetParameter(1));
	gaus1->FixParameter(2,f1->GetParameter(2));
	gaus2->FixParameter(0,f1->GetParameter(3));
	gaus2->FixParameter(1,f1->GetParameter(4));
	gaus2->FixParameter(2,f1->GetParameter(5));

	hAdd->Draw();
	gaus1->Draw("SAME");
	gaus2->Draw("SAME");

	TLegend* leg = new TLegend(0.7,0.4,0.88,0.68);
	leg->AddEntry(hAdd,"Combined histogram","f");
	leg->AddEntry(f1,"Combined Fit","l");
	leg->AddEntry("gaus1","Contribution A","l");
	leg->AddEntry("gaus2","Contribution B","l");
	leg->Draw();
}
