#include "./../Dynamics.cpp"
#include <fstream>
#include <sstream>

int progress =0;

class meanField : private Dynamics
{public:

    meanField(int n, int k):
    	Dynamics(n,k) {}

    //function to evolve static network and return the average value after lp points
    void evolveStaticNetwork(ofstream& f, int n1, double p,  double b, double c)
	{using parameter::dt;
	using parameter::et;

		links.evolve_links(p);
		initialize_fixed_ic();
		apply_heterogeneity(n1);

		f<<"# time"<<"\t"<<"Avg_value"<<endl;
		int limit= (int) (et/dt);
		for(int i=1; i<=limit; i++)
		{
			evolveNodes(dt,b,c);
			f<<i*dt<<"\t" <<avgx()<<endl;
		}
	}

};



int main()
{using namespace parameter;
	cout<< " Total iterations = "<<( nRange.size()*kRange.size()*n1Range.size()*
                                     pRange.size()*bRange.size()*cRange.size() )
                                     << endl ;
    for(int n : nRange)
    for(int k : kRange)
    {
        meanField analyser(n, k);

        for(int n1  : n1Range)
        for(double p : pRange)
        for(double b : bRange)
        for(double c : cRange)
        {
            progress++ ;
            cout<< "\r progress = "<<progress<< "  "<<flush ;

            ostringstream parameters;
            parameters<<"static_c="<<c  <<"_k="<<k
                                     <<"_n="<<n  <<"_b="<<b
                                     <<"_p="<<p  <<"_N1="<<n1 ;
            ofstream f( parameters.str()+".txt" ) ;
            f<<"# "<<parameters.str()<< endl;
            f<<"#"<<endl;

			analyser.evolveStaticNetwork(f,n1,p,b,c);
        }
    }
}
