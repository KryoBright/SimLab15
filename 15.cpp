#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

struct WeatherProcess
{

	int state;

	double **transitions=new double*[3];

	WeatherProcess()
	{
		int i=0;
		while (i<3)
		{
			int j=0;
			transitions[i]=new double[3];
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
		cout<<"Stabilized probabilities are:"<<endl;
		cout<<static_probs[0]/allTime<<"  "<<static_probs[1]/allTime<<"  "<<static_probs[2]/allTime<<"  ";
		if (acTime<time(0))
		{
			acTime=time(0)+weather.getStayTime();
			weather.changeState();
		}
	}
}
