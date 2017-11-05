//#include "Small_World.cpp"
class Dynamics
{public:
    Small_World links;
    vector<double> x, a, Dx;

    Dynamics(int n, int k):
        links(n,k),x(n),Dx(n),a(n){}

    void initialize();
	void initialize_fixed_ic();
    /// heterogeneity should be only supplied right after initialization
    void apply_heterogeneity(int N1);

	void calculate_derivatives(double b, double c);
    void evolveNodes(double dt, double b, double c);
    ///evolve sites with unit variance Gaussian noise
    void evolveNodes_gaussianNoise(double dt, double b, double c, double gaussianStrength);

    double avgx()const;
    double msdx()const;

    void display_details()const;
};


int maindy()
{
    Dynamics net(20,2);

    net.links.evolve_links(0.2);
    cout<<net.links;

    net.initialize();
    net.apply_heterogeneity(5);

    for(int i=0 ; i<2000; i++)
        net.evolveNodes(0.1,0,0);
    net.display_details();

    cout<<net.msdx()<< endl;
    cout<< net.avgx();
}



//------------implementation of class functions----------------
void Dynamics:: initialize()
{
    uniform_real_distribution<double>  distribution(-1, 1);
    for(int i=0; i<links.size() ; i++)
    {
        x[i]= distribution(generator) ;
        a[i]= 0.0;
        Dx[i]=0;
    }
}

void Dynamics::initialize_fixed_ic()
{
	mt19937 sameRandom(12345);
	uniform_real_distribution<double>  distribution(-1, 1);
	for(int i=0; i<x.size() ; i++)
	{
		x[i]= distribution(sameRandom) ;
		a[i]= 0.0;
		Dx[i]=0;
	}
}

/// heterogeneity should be only supplied right after initialization
void Dynamics::apply_heterogeneity(int N1)
{
    vector<int> n1a = sample(0,x.size()-1, N1,-1);
    for(int i=0; i<n1a.size() ; i++)
        a[ n1a[i] ] =1.0;
}

void Dynamics::calculate_derivatives(double b, double c)
{
    for(int i=0; i<links.size(); i++)
    {
        double nf=0;
        for(int j=0; j<links[i].size(); j++ )
            nf+=x[ links[i][j] ];
        nf /= links[i].size();

        Dx[i] = ( x[i]- x[i]*x[i]*x[i] ) +
                c*(nf- x[i]) + b + a[i] ;
    }
}

void Dynamics::evolveNodes(double dt, double b, double c)
{
	calculate_derivatives(b,c);
    for(int i=0; i<links.size(); i++)
        x[i] += Dx[i] * dt  ;
}

///evolve sites with unit variance Gaussian noise
void Dynamics::evolveNodes_gaussianNoise(double dt, double b, double c, double noiseStrength)
{
    normal_distribution<double> gaussianNoise(0,1);
    double noiseTerm = noiseStrength*sqrt(dt) ;

	calculate_derivatives(b,c);
    for(int i=0; i<links.size(); i++)
    {
        double noise = gaussianNoise(generator);
        x[i] += Dx[i]*dt  + noiseTerm*noise ;
    }
}

double Dynamics::msdx()const
{
    int n= x.size() ;
    double x1=0, x2=0, msd=0;
    for(int i=0; i<n; i++)
    {
        x1+=x[i];
        x2+=x[i]*x[i];
    }
    msd = abs( x2/n - x1*x1/(n*n) );
    return sqrt(msd);
}

double Dynamics::avgx()const
{
    double average =0;
    for(int i=0; i<x.size(); i++)
        average+=x[i];
    average /= x.size();
    return average;
}

void Dynamics::display_details()const
{
    cout<< endl;
    for(int i=0; i<links.size(); i++)
    {
        cout<< "x = "<<x[i]
			<< "\tDx = "<<Dx[i]
			<< "\ta = "<<a[i]
            << endl;
    }
    cout<< endl;
}

