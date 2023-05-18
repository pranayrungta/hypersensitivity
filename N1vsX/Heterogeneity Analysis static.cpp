#include "./../Small_World.cpp"
#include "./../Dynamics.cpp"
#include <fstream>
#include <sstream>

namespace parameter{
    const vector<int> n1_limits_in_percentage { 0, 60, 1 };  /// range
    constexpr double et = 20;
    constexpr double dt = 0.01;
    constexpr int repetitions = 10 ;
    constexpr int lp = 10; // last points 
}

class HeterogeneityAnalysis : private Dynamics
{public:

    HeterogeneityAnalysis(int n, int k)
    :Dynamics(n,k) {}

    void n1vsX(ostream& f, double p,  double b, double c);

private:
    //function to evolve static network and return the average value after lp points
    double evolveStaticNetwork(int n1, double p,  double b, double c);
};


string result; // can be called from python
extern "C" char* static_sw(int n, int k, double p, double b, double c)
{using namespace parameter;
    HeterogeneityAnalysis analyser(n, k);
    ostringstream f;
    analyser.n1vsX(f,p,b,c);
    result = f.str();
    return &result[0];
}





//------------implementation of class functions----------------

///function to write n1, aoic, stdev to the file f
void HeterogeneityAnalysis::n1vsX(ostream& f, double p,  double b, double c)
{using parameter::repetitions;
using parameter::n1_limits_in_percentage;

    f<<"N1,aoic,stdev"<<endl;
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
            avgValue = evolveStaticNetwork(n1,p,b,c);
            aoic += avgValue;
            aoic2 += avgValue*avgValue ;
        }
        aoic /= repetitions;
        aoic2 /= repetitions;
        stdev = sqrt( abs(aoic2 - aoic*aoic) );
        f<<n1<<","  <<aoic<<","  <<stdev<<endl;
    }
}

double HeterogeneityAnalysis::evolveStaticNetwork(int n1, double p,  double b, double c)
{using parameter::dt;
using parameter::et;
using parameter::lp;

    initialize();
    links.evolve_links(p);
    apply_heterogeneity(n1);

    int limit= (int) (et/dt) - lp;
    for(int i=1; i<=limit; i++)
        evolveNodes(dt,b,c);

    double avg=0;
    for(int i=1; i<=lp; i++)
    {
        evolveNodes(dt, b, c);
        avg += avgx();
    }
    avg/=lp;
    return avg;
}
