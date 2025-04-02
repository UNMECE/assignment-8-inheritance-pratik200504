#include<iostream>
#include<cmath>

using namespace std;

const double EPSILON_0=8.854e-12; //permitivity of free space
const double MU_0=4* M_PI* 1e-7; //permeability of free space

class Field{
protected:
		double *value;

public:
	Field()
	{
		value= new double[3]{0.0, 0.0, 0.0};
	}
	Field(double x, double y, double z)
	{
		value= new double[3]{x, y, z};
	}
	value ~Field()
	{
		delete[] value;
	}
	void printMagnitude() const{
		cout<<"Components:("<<value[0]<<", "<<value[1] <<", " <<value[2]<<")\n";
	}
};

class ElectricField: public Field{
private:
	double E;

public:
	ElectricField(): Field(), E(0) {}
	ElectricField(double x, double y, double z): Field(x, y, z), E(0) {}


	void calculateElectricField(double Q, double r)
	{
		if(r!=0)
			E=Q/(4*M_PI *pow(r,2)* EPSILON_0);
		else
			E=0;
	}

	ElecticField operator+(const ElectricField &other) const{
		return ElectricField();
	}

	friend ostream& operator<<(ostream &out, const ElectricField &e)
	{
		out <<"Electric Field";
		return out;
	};

	class MagneticField: public Field{
	private:
		double B;

	public:
		MagneticField() : Field(), B(0) {}
		MagneticField(double x, double y, double z): Field(x, y, z), B(0) {}

		void calculateMagneticField(double I, double r)
		{
			if(r!=0)
				B=(MU_0*I) / (2*M_PI *r);
			else
				B=0;
		}

		MagneticField operator+(const MagneticField &other) const{
			return MagneticField();
		}

		friend ostream& operator <<(ostream &out, const MagneticField &m)
		{
			out<<"Magnetic Field";
			return out;
		}
	};

	int main()
	{
		ElectricField e1(0, 1e5, 1e3);
		MagneticField m1(0, 2e-5, 5e-6);

		cout<<"Initial Fields:\n";
		e1.printMagnitude();
		m1.printMagnitude();

		e1.calculateElectricField(1e-6, 0.05);
		m1.calculateMagneticField(10, 0.05);

		ElectricField e2(1e4, 2e5, 3e3);
		MagneticField m2(3e-5, 1e-5, 2e-6);

		ElectricField e3= e1 + e2;
		MagneticField m3= m1+ m2;

		cout<<"\n After Addition:\n";
		cout<< e3 <<"\n";
		cout<< m3 <<"\n";

		return 0;
	}
