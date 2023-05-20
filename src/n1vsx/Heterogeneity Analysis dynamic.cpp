#include "./../Small_World.cpp"
#include "./../Dynamics.cpp"
#include <fstream>
#include <sstream>
#include <cstring>

namespace parameter{
    const vector<int> n1_limits_in_percentage { 0, 60, 1 };  /// range
    constexpr double et = 20;
    constexpr double dt = 0.01;
    constexpr int repetitions = 1 ;
    constexpr int lp = 10;
    constexpr int link_period = 10  ;
}

class HeterogeneityAnalysis : private Dynamics
{public:
    //Constructor
    HeterogeneityAnalysis(int n, int k)
    :Dynamics(n,k) {}

    ///function to write n1, aoic, stdev to the file f
    void n1vsX(ostream& f, double p,  double b, double c);

private:
    //function to evolve dynamic network and return the average value after lp points
    double evolveDynamicNetwork(int n1, double p,  double b, double c);
};



//char* alloc_memory(void) {
//    char* str = strdup("Hello World");
//    printf("Memory allocated...\n");
//    return str;
//}

extern "C" void free_memory(char* ptr)
{ free(ptr); }

//string result; // can be called from python
extern "C" char* dynamic_sw(int n, int k, double p, double b, double c)
{using namespace parameter;
    HeterogeneityAnalysis analyser(n, k);
    ostringstream f;
    analyser.n1vsX(f,p,b,c);

    string s = f.str();
    char* ch = strdup(&s[0]);
    return ch;
}

int main(){return 0;}



//------------implementation of class functions----------------

///function to write n1, aoic, stdev to the file f
void HeterogeneityAnalysis::n1vsX(ostream& f,double p,  double b, double c)
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
        	avgValue = evolveDynamicNetwork(n1,p,b,c);
            aoic += avgValue;
            aoic2 += avgValue*avgValue ;

        }
        aoic /= repetitions;
        aoic2 /= repetitions;
        stdev = sqrt( abs(aoic2 - aoic*aoic) );
        f<<n1<<","  <<aoic<<","  <<stdev<<endl;
    }
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
