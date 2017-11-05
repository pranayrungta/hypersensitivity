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
class dynamic_spacetime : private Dynamics
{public:
	dynamic_spacetime(int n,int k):
		Dynamics(n,k){};

    //function to evolve dynamic network and return the average value after lp points
	void evolveDynamicNetwork(ofstream& f, int n1, double p,  double b, double c)
	{using parameter::et;
	using parameter::dt;
	using parameter::link_period;

		initialize_fixed_ic();
		apply_heterogeneity(n1);

		f<<"# time"<<"\t"<<"node"<<"\t"<<"value"<<endl;
		int limit= (int) (et/dt);
		for(int i=0; i<limit; i++)
		{
			if(i%link_period==0)
				links.evolve_links(p);
			evolveNodes(dt,b,c);

			for(int j=0; j<x.size(); j++)
				f<<i*dt<<"\t"  <<j<<"\t"  <<x[j]<<endl;
			f<<endl;
		}
	}
};


int progress =0;
int main()
{using namespace parameter;

    cout<< " Total iterations = "<<( nRange.size()*kRange.size()*n1Range.size()*
                                     pRange.size()*bRange.size()*cRange.size() )
                                     << endl ;
    for(int n : nRange)
    for(int k : kRange)
    {
        dynamic_spacetime analyser(n, k);

        for(int n1  : n1Range)
        for(double p : pRange)
        for(double b : bRange)
        for(double c : cRange)
        {
            progress++ ;
            cout<< "\r progress = "<<progress<< "  "<<flush ;

            ostringstream parameters;
            parameters <<"dynamic_c="<<c  <<"_k="<<k
                                     <<"_n="<<n  <<"_b="<<b
                                     <<"_p="<<p  <<"_N1="<<n1 ;
            ofstream f( parameters.str()+".txt" ) ;
            f<<"# "<<parameters.str()<< endl;
            f<<"#"<<endl;

			analyser.evolveDynamicNetwork(f,n1,p,b,c);
            f.close();
        }
    }
}
