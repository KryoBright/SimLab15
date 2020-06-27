#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

// This functions finds the determinant of Matrix
double determinantOfMatrix(double mat[3][3])
{
	double ans;
	ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])
	      - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])
	      + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
	return ans;
}

// This function finds the solution of system of
// linear equations using cramer's rule
void findSolution(double coeff[3][3])
{
	// Matrix d using coeff as given in cramer's rule
	double d[3][3] =
	{
		{ coeff[0][0], coeff[0][1], coeff[0][2] },
		{ coeff[1][0], coeff[1][1], coeff[1][2] },
		{ 1, 1, 1 },
	};
	// Matrix d1 using coeff as given in cramer's rule
	double d1[3][3] =
	{
		{ 0, coeff[0][1], coeff[0][2] },
		{ 0, coeff[1][1], coeff[1][2] },
		{ 1, 1, 1 },
	};
	// Matrix d2 using coeff as given in cramer's rule
	double d2[3][3] =
	{
		{ coeff[0][0], 0, coeff[0][2] },
		{ coeff[1][0], 0, coeff[1][2] },
		{ 1, 1, 1 },
	};
	// Matrix d3 using coeff as given in cramer's rule
	double d3[3][3] =
	{
		{ coeff[0][0], coeff[0][1], 0 },
		{ coeff[1][0], coeff[1][1], 0 },
		{ 1, 1, 1 },
	};

	// Calculating Determinant of Matrices d, d1, d2, d3
	double D = determinantOfMatrix(d);
	double D1 = determinantOfMatrix(d1);
	double D2 = determinantOfMatrix(d2);
	double D3 = determinantOfMatrix(d3);

	// Coeff have a unique solution. Apply Cramer's Rule
	double x = D1 / D;
	double y = D2 / D;
	double z = D3 / D; // calculating z using cramer's rule
	cout<<x<<"  "<<y<<"  "<<z;
}


struct WeatherProcess
{

	int state;

	double transitions[3][3];

	WeatherProcess()
	{
		int i=0;
		while (i<3)
		{
			int j=0;
			while (j<3)
			{
				transitions[i][j]=0;
				j++;
			}
			i++;
		}

		state=rand()%3;
	}

	double getStayTime()
	{
		int i=0;
		double s=0;
		s=transitions[state][state];
		return log(rand()*1.0/RAND_MAX)/s;
	}

	void changeState()
	{
		int i=0;
		double s=0;
		double a=rand()*1.0/RAND_MAX;
		s=transitions[state][state];
		i=0;
		while (a>0)
		{
			if (i!=state)
			{
				a+=transitions[state][i]/s;
			}
			i=(i+1)%3;
		}
		state=(i+2)%3;
	}

	void reset()
	{

		state=rand()%3;
	}
};

int main()
{
	cout.flush();
	srand(time(0));
	double static_probs[3];
	int acTime=time(0);
	WeatherProcess weather;
	cout<<"Enter transition probabilities"<<endl;
	int i=0;
	while (i<3)
	{
		static_probs[i]=0;
		int j=0;
		while(j<3)
		{
			cin>>weather.transitions[i][j];
			j++;
		}
		i++;
	}
	int t=1000;
	int ef=10000;
	while (t>0)
	{
		weather.changeState();
		t--;
	}
	double allTime=0;
	while (ef>0)
	{
		weather.changeState();
		double t_tmp=weather.getStayTime();
		static_probs[weather.state]+=t_tmp;
		allTime+=t_tmp;
		ef--;
	}
	int stTime=time(0);

	while (true)
	{
		system("cls");
		cout<<"The weather now is ";
		switch (weather.state)
		{
			case 0:
				cout<<"Sunny";
				break;
			case 1:
				cout<<"Foggy";
				break;
			default:
				cout<<"Rainy";
				break;
		}
		cout<<endl;
		int days=(time(0)-stTime)/24;
		int hours=(time(0)-stTime)%24;
		cout<<"Time is "<<days<<" days and "<<hours<<" hours since start";
		cout<<endl<<endl;
		cout<<"Theoretical probabilities are:"<<endl;
		findSolution(weather.transitions);
		cout<<endl;
		cout<<"Stabilized probabilities are:"<<endl;
		cout<<static_probs[0]/allTime<<"  "<<static_probs[1]/allTime<<"  "<<static_probs[2]/allTime<<"  ";
		if (acTime<time(0))
		{
			acTime=time(0)+weather.getStayTime();
			weather.changeState();
		}
	}
}
