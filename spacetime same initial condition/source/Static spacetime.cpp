#include "spacetime.cpp"

int progress =0;
int main()
{using namespace parameter;

    cout<< " Total iterations = "<<( nRange.size()*kRange.size()*n1Range.size()*
                                     pRange.size()*bRange.size()*cRange.size() )
                                     << endl ;
    for(int n : nRange)
    for(int k : kRange)
    {
        spacetime analyser(n, k);

        for(int n1  : n1Range)
        for(double p : pRange)
        for(double b : bRange)
        for(double c : cRange)
        {
            progress++ ;
            cout<< "\r progress = "<<progress<< "  "<<flush ;

            ostringstream parameters;
            parameters <<"static_c="<<c<<"_k="<<k<<"_n="<<n  <<"_b="<<b<<"_p="<<p  <<"_N1="<<n1 ;
            ofstream f( parameters.str()+".txt" ) ;
            f<<"# "<<parameters.str()<< endl;
            f<<"#"<<endl;

			analyser.evolveStaticNetwork(f,n1,p,b,c);
            f.close();
        }
    }
}
