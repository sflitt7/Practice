#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TRandom.h>
void mass(Int_t n){

//The photon energy will be 200MeV and the target will be a proton.

	Double_t mp=938;
	Double_t k=200;

//	TLorentzVector kv;
//	kv.SetPxPyPzE(0,0,k,k);
//	TLorentzVector pv;
//	pv.SetPxPyPzE(0,0,0,mp);

//Crystal ball angular resolution is 2.5 (polar)

	TH1F* h = new TH1F("h","mass; x-axis; y-axis",100,0,180);

	for(Int_t i = 1; i<=n; i++){
		
		TF1* f1 = new TF1("f1","29.006+(-17.8545)*TMath::Cos(x)+(10.5726)*TMath::Cos(x)*TMath::Cos(x))",-1,1);
		Double_t th = TMath::ACos(f1->GetRandom());
	
		Double_t egp = k/(1+(k/mp)*(1-TMath::Cos(th)));

		TF1* f4 = new TF1("f4", "gaus(2.5)",0,5);
		f4->SetParameter(1,2.5);
		f4->SetParameter(2,0.5);

		TF1* f5 = new TF1("f5", "gaus(0.0027)",0,1);
		f5->SetParameter(1,0.0027);
		f5->SetParameter(2,0.0001);

		Double_t s = f4->GetRandom();
		Double_t sth = s + th;

		Double_t e = f5->GetRandom();
		Double_t ep = egp + e;



	//	TLorentzVector kp;
	//	kp.SetPxPyPzE(kx,ky,kz,egp);

	//	TLorentzVector kp;
	//	kp.SetPxPyPzE(kx,ky,kz,egp);

	//	pf=kv+pv-kp;

		h->Fill(sth);
		}	
cout<<"here"<<endl;
//	TF1* f2 = new TF1("f2","TMath::Gaus(x,0,2.5/2.35)",0,10);
	
//	TF1* f3 = new TF1("f3","TMath::Gaus(x,0,0.0027/2.35)",0,10);
//
	h->Draw();
//	f2->Draw("SAME");
}
