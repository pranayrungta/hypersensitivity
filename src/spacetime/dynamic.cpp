#include "./../Small_World.cpp"
#include "./../Dynamics.cpp"
#include <sstream>
/*
    System starts from same initial condition
    for all parameter values !!!!

    Look for initialize functions...

    template<class topology>
    void Dynamics<topology>:: initialize()
*/
class Dynamic_sw : private Dynamics
{public:
	Dynamic_sw(int n,int k):
		Dynamics(n,k){};

    //function to evolve dynamic network and return the average value after lp points
	void spacetime(ostream& f, int n1, double p,  double b, double c)
	{
        const double et = 25;
        const double dt = 0.01;
        const int link_period = 10  ;

		initialize_fixed_ic();
		apply_heterogeneity(n1);

		f<<"time,node,value"<<endl;
		int limit= (int) (et/dt);
		for(int i=0; i<limit; i++)
		{
			if(i%link_period==0)
				links.evolve_links(p);
			evolveNodes(dt,b,c);

			for(int j=0; j<x.size(); j++)
				f<<i*dt<<","  <<j<<","  <<x[j]<<endl;
		}
	}

	void meanfield(ostream& f, int n1, double p,  double b, double c)
	{
        const double et = 40;
        const double dt = 0.01;
        const int link_period = 10  ;

		initialize_fixed_ic();
		apply_heterogeneity(n1);

		f<<"time,Avg_value"<<endl;
		int limit= (int) (et/dt);
		for(int i=0; i<limit; i++)
		{
			if(i%link_period==0)
				links.evolve_links(p);
			evolveNodes(dt,b,c);
			f<<i*dt<<"," <<avgx()<<endl;
		}
	}
};



string result; // can be called from python
extern "C" char* dynamic_sw(int n, int k, int n1, double p, double b, double c)
{
    Dynamic_sw analyser(n, k);
    ostringstream f;
    analyser.spacetime(f,n1,p,b,c);
    result = f.str();
    return &result[0];
}

extern "C" char* dynamic_sw_mean(int n, int k, int n1, double p, double b, double c)
{
    Dynamic_sw analyser(n, k);
    ostringstream f;
    analyser.meanfield(f,n1,p,b,c);
    result = f.str();
    return &result[0];
}

//int main(){return 0;}
