#include <TMath.h>
#include <TF1.h>
#include <TLorentzVector.h>

void mass2(Int_t n){

	Double_t mp=938;
	Double_t k=200;
	TLorentzVector kv;
	TLorentzVector pv;
	kv.SetPxPyPzE(0,0,k,k);
	pv.SetPxPyPzE(0,0,0,mp);

	TH1F* h = new TH1F("h","missing mass;x-axis;y-axis",100,937.6,938.4);
	Double_t sum = 0;

	for(Int_t i = 0; i<n; i++){

	TF1* f1 = new TF1("f1", "29.006+(-17.8545*(cos(x)))+(10.5726*(cos(x)*cos(x)))",-1,1);
	Double_t th = TMath::ACos(f1->GetRandom());
//For angle smear
	TF1* f2 = new TF1("f2", "TMath::Gaus(x,0,2.5/2.35)",-10,10);
	Double_t l = f2->GetRandom();
	Double_t lth = l + th;
//Scattered photon energy in lab frame
	Double_t egf = k/(1+(k/mp*(1-cos(lth))));
//For energy smear
	TF1* f3 = new TF1("f3","TMath::Gaus(x,0,(0.027/0.2)/2.35)",-10,10);
	Double_t r = f3->GetRandom();
	Double_t re = r + egf;
//Scattered photon components in lab frame
	Double_t kx = re*TMath::Sin(lth);
	Double_t ky = 0;
	Double_t kz = re*TMath::Cos(lth);
//Lorentz vector in lab frame
	TLorentzVector kvp;
	kvp.SetPxPyPzE(kx,ky,kz,re);
//Final proton 4-vector
	TLorentzVector pvp = kv + pv - kvp;
//Square of partlicle's 4-momentum is its mass
	Double_t mpf = TMath::Sqrt(pvp.Dot(pvp));

	Double_t mism = mpf;
	h->Fill(mism);
	cout<<mism<<endl;
	sum += mism;
	}
//TF1* f7 = new TF1("f7","[0]*TMath::Gaus(x,[1],[2])",90,110);
//f7->SetParLimits(1,937.6,938.4);
//f7->SetParLimits(2,0.065,0.075);
h->Fit("gaus");
Double_t FWHM = 2.35*(0.07053);
cout<<"The FWHM is "<<FWHM<<endl;
h->Draw();
}
