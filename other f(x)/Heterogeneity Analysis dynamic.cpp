#include "otherDynamics.cpp"
#include <fstream>
#include <sstream>

int progress =0;


class HeterogeneityAnalysis : private Dynamics
{public:
    //Constructor
    HeterogeneityAnalysis(int n, int k)
    :Dynamics(n,k) {}

    ///function to write n1, aoic, stdev to the file f
    void n1vsX(ofstream& f, double p,  double b, double c);

private:
    //function to evolve dynamic network and return the average value after lp points
    double evolveDynamicNetwork(int n1, double p,  double b, double c);
};



int main()
{using namespace parameter;
    cout<< " Total iterations = "<<( nRange.size()*kRange.size()*  repetitions*
                                     pRange.size()*bRange.size()*cRange.size() )
                                     << endl ;
    for(int n : nRange)
    for(int k : kRange)
    {
        HeterogeneityAnalysis analyser(n, k);

        for(double p : pRange)
        for(double b : bRange)
        for(double c : cRange)
        {
            ostringstream parameters;
            parameters <<"dynamic"   <<"_c="<<c    <<"_k="<<k
					   <<"_n="<<n    <<"_b="<<b    <<"_p="<<p ;
            ofstream f( parameters.str()+".txt" ) ;
            f<<"# "<<parameters.str()<< endl;
            f<<"#"<<endl;
            analyser.n1vsX(f,p,b,c);
            f.close();
        }
    }
}





//------------implementation of class functions----------------

///function to write n1, aoic, stdev to the file f
void HeterogeneityAnalysis::n1vsX(ofstream& f,double p,  double b, double c)
{using parameter::repetitions;
using parameter::n1_limits_in_percentage;
    f<<"# N1"<<"\t"   <<"aoic"<<"\t"   <<"stdev"<<endl;
    double avgValue, stdev;

    int n1begin = round( n1_limits_in_percentage[0]/100.0 * x.size() );
    int n1end   = round( n1_limits_in_percentage[1]/100.0 * x.size() );
    int n1steps = round( n1_limits_in_percentage[2]/100.0 * x.size() );
    n1steps     = (n1steps<1)? 1 : n1steps ;
    for(int n1=n1begin; n1<=n1end; n1+=n1steps)
    {
        double aoic = 0;
        double aoic2 =0;
        for(int repetition_no=1; repetition_no<=repetitions; repetition_no++)
        {
        	avgValue = evolveDynamicNetwork(n1,p,b,c);
            aoic += avgValue;
            aoic2 += avgValue*avgValue ;

        }
        aoic /= repetitions;
        aoic2 /= repetitions;
        stdev = sqrt( abs(aoic2 - aoic*aoic) );
        f<<n1<<"\t"  <<aoic<<"\t"  <<stdev<<endl;
    }
    progress+= repetitions;
    cout<< "\r progress = "<<progress<< "  "<<flush ;
}


//function to evolve dynamic links and return the average value after lp points
double HeterogeneityAnalysis::
evolveDynamicNetwork(int n1, double p,  double b, double c)
{using parameter::dt;
using parameter::et;
using parameter::lp;
using parameter::link_period;

    initialize();
    apply_heterogeneity(n1);

    int limit= int( (et/dt) - lp );
    for(int i=0; i<limit; i++)
    {
        if(i%link_period==0)
            links.evolve_links(p);
        evolveNodes(dt,b,c);
    }
    double avg=0;
    for(int i=limit; i<=limit+lp; i++)
    {
        evolveNodes(dt, b, c);
        if(i%link_period==0)
            links.evolve_links(p);
        avg += avgx();
    }
    avg/=lp;
    return avg;
}
