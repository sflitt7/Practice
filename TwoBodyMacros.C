/* 
 * TwoBodyMacros
 *
 * This macro does all sorts of great stuff and has been updated numerous time
 * over the last 15 years.
 * 
 * DLH
 *
 */

#include "physics.h"

Double_t energy( Double_t mom, Double_t m)
{
	return( sqrt(mom*mom + m*m));
}

Double_t momentum( Double_t en, Double_t m)
{
	if ( en >= m) return( sqrt( en*en - m*m));
	else return( -1);
}

Double_t Sqr( Double_t x)
{
	return( x*x);
}

/* 
 * qp
 *
 * Simple photoproduction from an at-rest target.
 *
 * Momentum of produced particle as a function of incident photon energy,
 * target mass, scattered theta, and scattered particle mass.
 *
 * Note that the target particle must also exist in the final state, i.e. this
 * routine does not work for charged production.
 *
 */
Double_t qp( Double_t ke, Double_t pm, Double_t qth, Double_t qm)
{
	Double_t qmom;
	Double_t W, S;
	Double_t A, B, C, a, b, c;

	W = ke + pm;
	S = 2*ke*pm + pm*pm;

	A = S - pm*pm + qm*qm;
	B = 2*ke*cos( qth);
	C = 2*W;

	a = C*C - B*B;
	b = -2*A*B;
	c = Sqr( C*qm) - A*A;

	qmom = (-b + sqrt( b*b - 4*a*c))/2/a;
	cout<<qmom<<endl;

	if ( qmom != qmom) return( -1);
	else return( qmom);
}

/* 
 * pp
 *
 * Simple photoproduction from an at-rest target.
 *
 * Momentum of target recoil as a function of incident photon energy, target
 * mass, target recoil theta, and scattered particle mass.
 *
 * Note that the target particle must also exist in the final state, i.e. this
 * routine does not work for charged production.
 *
 */
Double_t pp( Double_t ke, Double_t pm, Double_t pth, Double_t qm)
{
	Double_t pmom;
	Double_t W, S;
	Double_t A, B, C, a, b, c;

	W = ke + pm;
	S = 2*ke*pm + pm*pm;

	A = S + pm*pm - qm*qm;
	B = 2*ke*cos( pth);
	C = 2*W;

	a = C*C - B*B;
	b = -2*A*B;
	c = Sqr( C*pm) - A*A;

	pmom = (-b + sqrt( b*b - 4*a*c))/2/a;

	if ( pmom != pmom) return( -1);
	else return( pmom);
}

void TwoBodyLab( Double_t ke = 200, Double_t qth = 45) {

	Double_t km, Ek, kmom;
	Double_t pm;
	Double_t qm, qph, qmom;
	Double_t qx, qy, qz, qe;
	Double_t ang;
	TLorentzVector k, p, p1, q;
	TString name;
	
// Beam is a photon
	km = 0;
// Beam is a charged pion
//	km = kMPI_MEV;

	Ek = ke + km;
	kmom = momentum( Ek, km);

// Target is a proton at rest
	pm = kMP_MEV;
// Target is a C12 nucleus at rest
//	pm = kM_C12_MEV;

// Set beam energy and momentum;
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, kmom, Ek);

// Target is at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Set mass of particle to
//	qm = kMPI0_MEV;		// pi0
//	qm = kMPI_MEV;			// charged pion
	qm = 0;					// photon

// Convert theta to radians; default is pi/4
// Phi is zero since we are dealing with two-body kinematics and no
// polarization.
	qth *= kD2R;
	qph = 0;

// Calculate momentum using kinematics function
	qmom = qp( k.E(), p.E(), qth, qm);
// Calculate energy
	qe = energy( qmom, qm);

// Calculate momentum components
	qx = qmom*sin( qth)*cos( qph);
	qy = qmom*sin( qth)*sin( qph);
	qz = qmom*cos( qth);

// Set 4-momentum
	q.SetPxPyPzE( qx, qy, qz, qe);

// Calculate recoil 4-momentum using 4-mom conservation
	p1 = k + p - q;

// Calculate angle between two vectors for fun
	ang = q.Vect().Angle(p1.Vect());

// Output
	cout << "      E     m       p    theta   phi " << endl;

// Beam photon
	name = Form( "k:  %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", k.E(), k.M(),
			k.Vect().Mag(), k.Theta()/kD2R, k.Phi()/kD2R);
	cout << name;

// Target
	name = Form( "p:  %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", p.E(), p.M(),
			p.Vect().Mag(), p.Theta()/kD2R, p.Phi()/kD2R);
	cout << name;

// Produced particle
	name = Form( "q:  %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", q.E(), q.M(),
			q.Vect().Mag(), q.Theta()/kD2R, q.Phi()/kD2R);
	cout << name;

// Recoiling target
	name = Form( "p1: %5.1f  %5.1f  %5.1f  %5.1f  %5.1f\n", p1.E(), p1.M(),
			p1.Vect().Mag(), p1.Theta()/kD2R, p1.Phi()/kD2R);
	cout << name;

//	cout << p1.Px() << " " << q.Px() << endl;
//	cout << p1.Py() << " " << q.Py() << endl;
//	cout << k.Pz() << " " << p1.Pz() + q.Pz() << endl;

}

/*
 * TwoBodyCM
 *
 * This is the same as the function above except that as input it uses the CM
 * scattered angle instead of the lab scattered angle.  Moreover, all CM
 * quantities are also calculated and output.  This function makes heavy use of
 * the boosting capability of the TLorentzVectors, and is quite a bit more
 * elegant that the above function.  Note also that inputing the CM angle
 * instead of the lab angle gives you a different result!
 *
 * DLH 02.05.2007
 *
 */

void TwoBodyCM( Double_t ke = 200, Double_t qth_cm = 45) {

	TLorentzVector k, p, p1, q, pIn;
	TLorentzVector k_cm, p_cm, p1_cm, q_cm;
	TVector3 cmBoost, labBoost;
	
	Double_t qm, qph_cm, mom_cm;
	Double_t qx_cm, qy_cm, qz_cm, qe_cm;
	Double_t pm, S;
	Double_t ang;
	Double_t W;

	TString name;

	pm = kMP_MEV;
// Set photon energy and momentum; default is 200 MeV;
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);
// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Total incoming 4-momentum
	pIn = k + p;
// The 3-vector boosts to and from the lab and CM frames
	labBoost = pIn.BoostVector();
	cmBoost = -pIn.BoostVector();
// Boosting the initial state particles' 4-momentum to the CM frame
	k_cm = k;
	k_cm.Boost( cmBoost);
	p_cm = p;
	p_cm.Boost( cmBoost);

// Set mass to:
	qm = kMPI0_MEV;		// neutral pion
//	qm = 0;					// photon

// Convert angle to radians
	qth_cm *= kD2R;

// Phi symmetry, so set phi to zero
	qph_cm = 0;

// Calculate cm energy
	S = 2*ke*pm + pm*pm;
	W = sqrt( S);
	name = Form( "W = %6.1f\n", W);
	cout << name;
	qe_cm = (S - pm*pm + qm*qm)/2/sqrt( S);

// Calculate cm momentum (it is the same for both the produced particle and
// the target by definition!)
	mom_cm = momentum( qe_cm, qm);

// Calculate cm momentumm components
	qx_cm = mom_cm*sin( qth_cm)*cos( qph_cm);
	qy_cm = mom_cm*sin( qth_cm)*sin( qph_cm);
	qz_cm = mom_cm*cos( qth_cm);

// Set cm 4-momentum
	q_cm.SetPxPyPzE( qx_cm, qy_cm, qz_cm, qe_cm);

// Calculate the lab parameters by boosting the cm 4-momentum to the lab
// frame
	q = q_cm;
	q.Boost( labBoost);

// Calculate recoil proton 4-momentum using 4-mom conservation
	p1 = k + p - q;

// Calculate the recoil proton cm parameters by boosting the lab 4-momentum to
// the cm frame
	p1_cm = p1;
	p1_cm.Boost( cmBoost);

// Calculate angle between two vectors for fun
	ang = q.Vect().Angle( p1.Vect());

// Output
	cout << "          E     m      T    p    theta   phi " << endl;

// Lab
// Beam photon
	name = Form( "k:     %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", k.E(), k.M(),
			k.E()-k.M(), k.Vect().Mag(), k.Theta()/kD2R, k.Phi()/kD2R);
	cout << name;

// Target
	name = Form( "p:     %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p.E(), p.M(),
			p.E()-p.M(), p.Vect().Mag(), p.Theta()/kD2R, p.Phi()/kD2R);
	cout << name;

// Produced particle
	name = Form( "q:     %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", q.E(), q.M(),
			q.E()-q.M(), q.Vect().Mag(), q.Theta()/kD2R, q.Phi()/kD2R);
	cout << name;

// Recoiling target
	name = Form( "p1:    %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p1.E(), p1.M(),
			p1.E()-p1.M(), p1.Vect().Mag(), p1.Theta()/kD2R, p1.Phi()/kD2R);
	cout << name;

// CM
// Beam photon
	name = Form( "k_cm:  %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", k_cm.E(),
			k_cm.M(), k_cm.E()-k_cm.M(), k_cm.Vect().Mag(), k_cm.Theta()/kD2R,
			k_cm.Phi()/kD2R);
	cout << name;

// Target
	name = Form( "p_cm:  %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p_cm.E(),
			p_cm.M(), p_cm.E()-p_cm.M(), p_cm.Vect().Mag(), p_cm.Theta()/kD2R,
			p_cm.Phi()/kD2R);
	cout << name;

// Produced particle
	name = Form( "q_cm:  %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", q_cm.E(),
			q_cm.M(), q_cm.E()-q_cm.M(), q_cm.Vect().Mag(), q_cm.Theta()/kD2R,
			q_cm.Phi()/kD2R);
	cout << name;

// Recoiling target
	name = Form( "p1_cm: %6.1f  %5.1f  %5.1f %5.1f  %5.1f  %5.1f\n", p1_cm.E(),
			p1_cm.M(), p1_cm.E()-p1_cm.M(), p1_cm.Vect().Mag(),
			p1_cm.Theta()/kD2R, p1_cm.Phi()/kD2R);
	cout << name;

}

//
// TwoBodyCMOut
//
// This function outputs either lab recoil theta or kinetic energy as a
// function of scattered CM theta for a fixed incident photon energy.
//
Double_t TwoBodyCMOut( Double_t *x, Double_t *par)
{

	TLorentzVector k, p, p1, q, pIn;
	TLorentzVector k_cm, p_cm, p1_cm, q_cm;
	TVector3 cmBoost, labBoost;
	
	UInt_t flag;
	Double_t ke, qth_cm;
	Double_t qm, qph_cm, mom_cm;
	Double_t qx_cm, qy_cm, qz_cm, qe_cm;
	Double_t pm, S;
	Double_t ang;

// Scattered particle angle in CM frame
	qth_cm = x[0];

// Incident photon energy
	ke = par[0];

// Flag determining output theta or KE
	flag = (int) par[1];

// Target mass
	pm = kMP_MEV;

// Set photon energy and momentum
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);

// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Total incoming 4-momentum
	pIn = k + p;

// The 3-vector boosts to and from the lab and CM frames
	labBoost = pIn.BoostVector();
	cmBoost = -pIn.BoostVector();

// Boosting the initial state particles' 4-momentum to the CM frame
	k_cm = k;
	k_cm.Boost( cmBoost);
	p_cm = p;
	p_cm.Boost( cmBoost);

// Set mass to:
	qm = kMPI0_MEV;		// neutral pion
//	qm = 0;					// photon

// Convert angle to radians
	qth_cm *= kD2R;

// Phi symmetry, so set phi to zero
	qph_cm = 0;

// Calculate CM energy
	S = 2*ke*pm + pm*pm;
	qe_cm = (S - pm*pm + qm*qm)/2/sqrt(S);

// Calculate CM momentum (it is the same for both the scattered particle and
// target recoil by definition!)
	mom_cm = momentum( qe_cm, qm);

// Calculate CM momentumm components
	qx_cm = mom_cm*sin( qth_cm)*cos(qph_cm);
	qy_cm = mom_cm*sin( qth_cm)*sin(qph_cm);
	qz_cm = mom_cm*cos( qth_cm);

// Set CM 4-momentum
	q_cm.SetPxPyPzE( qx_cm, qy_cm, qz_cm, qe_cm);

// Calculate the lab parameters by boosting the CM 4-momentum to the lab
// frame
	q = q_cm;
	q.Boost( labBoost);

// Calculate recoil proton 4-momentum using 4-mom conservation
	p1 = k + p - q;

	if ( flag == 0) return( p1.Theta()/kD2R);
	else return( p1.E()-p1.M());
}

//
// TwoBodyLabOut
//
// This function outputs either lab scattered theta or kinetic energy as a
// function of recoil lab theta for a fixed incident photon energy.
//
Double_t TwoBodyLabOut( Double_t *x, Double_t *par)
{
	UInt_t flag;
	Double_t pth, ke;
	Double_t pm, pph, pmom;
	Double_t px, py, pz, pe;
	Double_t qm;
	TLorentzVector k, p, p1, q, pIn;
	
// Recoil particle angle in lab frame
	pth = x[0];

// Incident photon energy
	ke = par[0];

// Flag determining output theta or KE
	flag = UInt_t( par[1]);

// Target mass
	pm = kMP_MEV;

// Set mass to:
//	qm = kMPI0_MEV;		// neutral pion
	qm = 0;					// photon

// Convert angle to radians
	pth *= kD2R;

// Phi symmetry, so set phi to zero
	pph = 0;

// Set photon energy and momentum
// Beam direction is along z
	k.SetPxPyPzE( 0, 0, ke, ke);

// Set target to a proton at rest
	p.SetPxPyPzE( 0, 0, 0, pm);

// Calculate recoil momentum using kinematics function
	pmom = pp( k.E(), p.M(), pth, qm);
// Calculate energy
	pe = energy( pmom, pm);

// Calculate momentum components
	px = pmom*sin( pth)*cos( pph);
	py = pmom*sin( pth)*sin( pph);
	pz = pmom*cos( pth);

// Set 4-momentum
	p1.SetPxPyPzE( px, py, pz, pe);

// Calculate recoil 4-momentum using 4-mom conservation
	q = k + p - p1;

	if ( flag == 0) return( q.Theta()/kD2R);
	else if ( flag == 1) return( q.E()-q.M());
	else return( p1.E()-p1.M());
}
