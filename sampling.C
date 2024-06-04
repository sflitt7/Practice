#include <TMath.h>
#include <TRandom.h>
void cube(int i){
	TRandom r;
	TH3F* h=new TH3F("h","Cube; x axis; y axis; z axis",100,0,1,100,0,1,100,0,1);
	for(int n=0; n<i; n++){
		double x=r.Rndm();
		double y=r.Rndm();
		double z=r.Rndm();
		h->Fill(x,y,z);
	}
	h->Draw();
}

#include <TMath.h>
#include <TRandom.h>
void circle(int i){
	TRandom r;
	TH2F* h=new TH2F("h","Circle; x axis; y axis",100,-1,1,100,-1,1);
	for(int n=0; n<i; n++){
		double R=TMath::Sqrt(r.Rndm());
		double th=r.Rndm()*360*TMath::DegToRad();
		double x=R*TMath::Cos(th);
		double y=R*TMath::Sin(th);
		h->Fill(x,y);
	}
	h->Draw();
}


#include <TMath.h>
#include <TRandom.h>
void sphere(int i){
	TRandom r;
	TH3F* h=new TH3F("h","Sphere; x axis; y axis; z axis",100,-1,1,100,-1,1,100,-1,1);
	for(int n=0; n<i; n++){
		double R1=r.Rndm();
		double R=TMath::Power(R1,1/(double)3);
		double th=TMath::ACos(2*r.Rndm()-1);
		double phi=r.Rndm()*360*TMath::DegToRad();
		double x=R*TMath::Cos(th)*TMath::Sin(phi);
		double y=R*TMath::Sin(th)*TMath::Sin(phi);
		double z=R*TMath::Cos(phi);
		h->Fill(x,y,z);
	}
	h->Draw();
}
