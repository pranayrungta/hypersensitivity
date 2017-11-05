#include "./../../Dynamics.cpp"
#include <fstream>
#include <sstream>
/*
    System starts from same initial condition
    for all parameter values !!!!

    Look for initialize functions...

    template<class topology>
    void Dynamics<topology>:: initialize()
*/
class spacetime : private Dynamics
{public:
    spacetime(int n, int k):
    	Dynamics(n,k) {}

	//function to evolve static network and return the average value after lp points
    void evolveStaticNetwork(ofstream& f, int n1, double p,  double b,double c)
	{using parameter::et;
	using parameter::dt;

		links.evolve_links(p);
		initialize_fixed_ic();
		apply_heterogeneity(n1);

		f<<"# time"<<"\t"<<"node"<<"\t"<<"value"<<endl;
		int limit= (int) (et/dt);
		for(int i=1; i<=limit; i++)
		{
			evolveNodes(dt,b,c);

			for(int j=0; j<x.size(); j++)
				f<<i*dt<<"\t"  <<j<<"\t"  <<x[j]<<endl;
			f<<endl;
		}
	}
};
