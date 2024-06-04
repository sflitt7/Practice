#include <TMath.h>
void photon(Double_t x, Double_t theta){
	Double_t ProMoI=0;
	Double_t ProEnI=938;
	Double_t PhoEnI=x;
	Double_t Beta=PhoEnI/(x+ProEnI);
	Double_t Gamma=1/TMath::Sqrt(1-Beta*Beta);
	cout<<"beta= "<<Beta<<" and gamma= "<<Gamma<<endl;

	cout<<"Next in the CM frame."<<endl;
	Double_t p=Gamma*Beta*ProEnI;
	Double_t k=Gamma*(PhoEnI-Beta*PhoEnI);
	Double_t E_p=Gamma*ProEnI;
	Double_t E_g=Gamma*(PhoEnI-Beta*PhoEnI);
	cout<<"p'= "<<p<<endl;
	cout<<" k'= "<<k<<endl;
	cout<<"proton energy= "<<E_p<<endl;
	cout<<"photon energy= "<<E_g<<endl;

	cout<<"Finding the components."<<endl;
	Double_t E_g_f = E_g/(1+E_g/ProEnI*(1-TMath::Cos(theta)));
	cout<<"final photon energy= "<<E_g_f<<endl;
	Double_t k_x = E_g_f*TMath::Cos(theta);
	Double_t k_y = E_g_f*TMath::Sin(theta);
	Double_t E_p_f = TMath::Sqrt((E_g_f*E_g_f)+938*938);
	cout<<"This is the CM frame so the proton quantities must match the photon quantities as they are in opposite directions."<<endl;
	cout<<"x-comp.= "<<k_x<<" and the y-comp.= "<<k_y<<endl;
	cout<<"egf"<<E_g_f<<endl;
	cout<<"epf"<<E_p_f<<endl;

	cout<<"Back to the lab frame."<<endl;
	Double_t ProMoFx = Gamma*(k_x+Beta*E_p_f);
	Double_t PhoMoFx = Gamma*(k_x+Beta*E_g_f);
	Double_t ProEnF = Gamma*(E_p_f+Beta*k_x);
	Double_t PhoEnF = Gamma*(E_g_f+Beta*k_x);
	
	Double_t ProMoF = TMath::Sqrt(ProMoFx*ProMoFx+k_y*k_y);
	Double_t PhoMoF = TMath::Sqrt(PhoMoFx*PhoMoFx+k_y*k_y);

	cout<<"p_f= "<<ProMoF<<endl;
	cout<<" k_f= "<<PhoMoF<<endl;
	cout<<"proton energy= "<<ProEnF<<endl;
	cout<<"photon energy= "<<PhoEnF<<endl;


	TCanvas* c1=new TCanvas("c1","c1",100,0,2000,3000);
	c1->Divide(1,3);
	c1->cd(1);
	TGraph* g1 = new TGraph();
	TGraph* g2 = new TGraph();
	TGraph* g3 = new TGraph();



	for(Int_t i=1;i<181;i++){
		//scattered photon energy
		Double_t SPE=x/(1+x/ProEnI*(1-TMath::Cos(i*3.14/360)));

		//recoil proton kinetic energy
		Double_t kxf = SPE*TMath::Cos(i*3.14/360);
		Double_t kyf = SPE*TMath::Sin(i*3.14/360);
		Double_t pfx = x-kxf;

		Double_t KE = TMath::Sqrt(TMath::Power(pfx,2)+TMath::Power((kyf),2));
		Double_t ke = x-SPE;

		//recoil proton angle
		Double_t phi = TMath::ATan(-kyf/pfx);

		g1->AddPoint(i, SPE);
		g2->AddPoint(i, ke);
		g3->AddPoint(i, phi);
	}

	c1->cd(1);
	g1->GetXaxis()->SetRangeUser(0,180);
	g1->GetYaxis()->SetRangeUser(0,170);
	g1->SetMarkerStyle(8);
	g1->SetMarkerColor(4);
	g1->SetTitle("Scattered Photon Energy");
	g1->Draw("ALP");

	c1->cd(2);
	g2->GetXaxis()->SetRangeUser(0,180);
	g2->GetYaxis()->SetRangeUser(0,30);
	g2->SetMarkerStyle(8);
	g2->SetMarkerColor(4);
	g2->SetTitle("Recoil Proton K.E.");
	g2->Draw("ALP");

	c1->cd(3);
	g3->GetXaxis()->SetRangeUser(0,180);
	g3->Draw("APL");
	g3->SetMarkerStyle(8);
	g3->SetMarkerColor(4);
	g3->SetTitle("Recoil Proton Angle");

	c1->SaveAs("test_canvas.png");

}
