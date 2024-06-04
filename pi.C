#include <TRandom.h>
void MonteCarlo(Int_t n){
	TRandom r;
	Int_t counter=0;

	for (Int_t i=0; i<=n;i++){
		Double_t y=r.Rndm();
		Double_t x=r.Rndm();
		Double_t z=x*x + y*y;
		if(z<=1){
			counter++;}}
	Double_t ratio=counter/(Double_t)n*4;
	cout<<ratio<<endl;


}
