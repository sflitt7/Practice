#include <TMath.h>
void sub(){

	Double_t P = 1000;
	Double_t Pe =TMath::Sqrt(P);

	Double_t R = 2500;
	Double_t Re = TMath::Sqrt(R);

	Double_t wP = 50;
	Double_t wR = 250;

	Double_t r = wP/wR;
	cout<<"the ratio is: "<<r<<endl;

	cout<<"the yield with no random is: "<<P<<endl;

	Double_t Y = P-r*R;
	cout<<"the subtracted yield is: "<<Y<<endl;

	Double_t Ye = TMath::Sqrt(P+(r*r*R));
	cout<<"the subtracted yield error is: "<<Ye<<endl;

	Double_t Yer = Ye/Y;
	cout<<"the relative yield error is: "<<Yer<<endl;

	Double_t Ys = P;
	Double_t Yse = Pe/Ys;	
	cout<<"relative error (slow): "<<Yse<<endl;

//2 hour experiment
	Double_t P2 = 2000;
	Double_t Pe2 =TMath::Sqrt(P2);

	Double_t R2 = 5000;
	Double_t Re2 = TMath::Sqrt(R2);

	Double_t wP2 = 50;
	Double_t wR2 = 250;

	Double_t r2 = wP2/wR2;
	cout<<"the ratio is: "<<r2<<endl;

	Double_t Y2 = P2-r2*R2;
	cout<<"the subtracted yield is: "<<Y2<<endl;
	cout<<"the yield with no random is: "<<P2<<endl;

	Double_t Ye2 = TMath::Sqrt(P2+(r2*r2*R2));
	cout<<"the subtracted yield error is: "<<Ye2<<endl;

	Double_t Yer2 = Ye2/Y2;
	cout<<"the relative yield error is: "<<Yer2<<endl;

	Double_t Ys2 = P2;
	Double_t Yse2 = Pe2/Ys2;
	cout<<"relative error (slow): "<<Yse2<<endl;


//Changing the electron current
	Double_t P3 = 3000;
	Double_t Pe3 =TMath::Sqrt(P3);

	Double_t R3 = 10000;
	Double_t Re3 = TMath::Sqrt(R3);

	Double_t wP3 = 50;
	Double_t wR3 = 250;

	Double_t r3 = wP3/wR3;
	cout<<"the ratio is: "<<r3<<endl;

	Double_t Y3 = P3-r3*R3;
	cout<<"the subtracted yield is: "<<Y3<<endl;
	cout<<"the yield with no random is: "<<P3<<endl;



	Double_t Ye3 = TMath::Sqrt(P3 + (r3*r3*R3));
	cout<<"the subtracted yield error is: "<<Ye3<<endl;


	Double_t Yer3 = Ye3/Y3;
	cout<<"the relative yield error is: "<<Yer3<<endl;

	Double_t Ys3 = P3;
	Double_t Yse3 = Pe3/Ys3;
	cout<<"relative error (slow): "<<Yse3<<endl;



}
