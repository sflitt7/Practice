#include <TMath.h>
void graphs(){

	TCanvas* c1 = new TCanvas("c1","title",0,0,4000,3000);
	c1->Divide(2,2);
	c1->cd(1);

	TGraph* g1 = new TGraph();
	TGraph* g2 = new TGraph();

	for(int i=0; i<20; i++){
	double v = TMath::Sqrt(i);
	double w = TMath::Power((double)i,2.0);
	g1->AddPoint(i,v);
	g2->AddPoint(i,w);

	}
g1->Draw("APL");
c1->cd(2);
g2->Draw("APL");
}
