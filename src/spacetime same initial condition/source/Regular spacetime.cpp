#include "spacetime.cpp"

int progress=0;
int main()
{using namespace parameter;

    cout<< " Total iterations = "<<( nRange.size()*kRange.size()*n1Range.size()*
                                     bRange.size()*cRange.size() )<< endl ;
    for(int n : nRange)
    for(int k : kRange)
    {
        spacetime analyser(n, k);

        for(int n1  : n1Range)
        for(double b : bRange)
        for(double c : cRange)
        {
            progress++ ;
            cout<< "\r progress = "<<progress<< "  "<<flush ;

            ostringstream parameters;
            parameters<<"regular_c="<<c  <<"_k="<<k<<"_n="
                       <<n  <<"_b="<<b<<"_N1="<<n1 ;
            ofstream f( parameters.str()+".txt" ) ;
            f<<"# "<<parameters.str()<< endl;
            f<<"#"<<endl;

			analyser.evolveStaticNetwork(f,n1,0,b,c);
            f.close();
        }
    }
}
