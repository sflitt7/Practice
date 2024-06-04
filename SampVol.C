#include <TRandom.h>
void Cube(Int_t n){
	TRandom r;
	TH3F* h=new TH3F("h","title; x axis; y axis; z axis",100,0,1,100,0,1,100,0,1);//TH then number of dimensions then histogram name, then here h is the title and in the brackets is histogram table name, histogram title, number of bins for x axis, going from 0 to 1 and then for y axis from 0 to 1.
	for(Int_t i=0; i<=n;i++){
		Double_t x=r.Rndm();
		Double_t y=r.Rndm();
		Double_t z=r.Rndm();
		h->Fill(x,y,z);
	}
	h->Draw();
}
#include <TRandom.h>
void Square(Int_t n){
	TRandom r;
	TH2F* h=new TH2F("f", "title; x-axis; y-axis",100,0,1,100,0,1);
	for(Int_t i=0; i<=n; i++){
		Double_t x= r.Rndm();
		Double_t y= r.Rndm();
		h->Fill(x,y);
	}
	h->Draw();
}

#include <TRandom.h>
#include <TMath.h>
void Circle(Int_t n){
	TRandom r;
	TH2F* h=new TH2F("h","title; x-axis, y-axis",100,-1,1,100,-1,1);
	for(Int_t i=0; i<=n; i++){
		Double_t R=r.Rndm();
		Double_t theta=r.Rndm()*360*TMath::DegToRad();
		Double_t x=R*cos(theta);
		Double_t y=R*sin(theta);
		h->Fill(x,y);
	}
	h->Draw();
}

void BetterC(Int_t n){
	TRandom r;
	TH2F* h=new TH2F("h","title; x-axis, y-axis",100,-1,1,100,-1,1);
	for(Int_t i=0; i<=n; i++){
		Double_t R=TMath::Sqrt(r.Rndm());
		Double_t theta=r.Rndm()*360*TMath::DegToRad();
		Double_t x=R*cos(theta);
		Double_t y=R*sin(theta);
		h->Fill(x,y);
	}
	h->Draw();}

#include <TRandom.h>
#include <TMath.h>	
void Sphere(Int_t n){
	TRandom r;
	TH3F* h=new TH3F("h","title; x-axis, y-axis; z-axis",100,-1,1,100,-1,1,100,-1,1);
	for(Int_t i=0; i<=n; i++){
		Double_t R=r.Rndm();
		Double_t row=TMath::Power(R,1/(Double_t)3);
		Double_t theta=TMath::ACos(2*r.Rndm()-1);
		Double_t phi=r.Rndm()*360*TMath::DegToRad();
		Double_t x=row*sin(theta)*cos(phi);
		Double_t y=row*sin(theta)*sin(phi);
		Double_t z=row*cos(theta);
		h->Fill(x,y,z);
	}
	h->Draw();}
