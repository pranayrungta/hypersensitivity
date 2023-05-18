#include "common_base.cpp"

class Small_World : public topology_base
{public:

    Small_World(const int n, const int k):isRandom(n)
    {	nbr = vector<vector<int>>( n, vector<int>(k) );	}

    //function to evolve links
    void evolve_links(const double p);

    bool isRand(const int i) const
    {   return isRandom[i];    }

	ostream& display(ostream& os)const;

private:
    vector<bool> isRandom ;
};
ostream& operator<<(ostream& os, const Small_World& network)
{	return network.display(os);	}



int mainsw()
{
    Small_World s(10,4);
    s.evolve_links(0.5);

    cout<<"Node 0 "<<s[0]<<endl;
    cout<<"one neighbor : "<<s[0][1]<<endl;
	cout<<endl;
	cout<<s;
	cout<<"size = "<<s.size()<<endl;

	return 0;
}








///------------implementation of class functions----------------

//function to evolve links
void Small_World:: evolve_links(const double p)
{
    int n=nbr.size();
    int k=nbr[0].size();
    int k_left= k/2;
    int k_right= (k%2==0)?k/2: k/2+1;

    uniform_real_distribution<double>  probability_distribution(0, 1);
    float r=0;
    for(int i=0; i<n; i++)
    {
        r=probability_distribution(generator) ;
        if(p<r)
        {   //regular neighbors
            int j=0, c=0;
            for(j=-k_left;j<0; j++)
            {
                nbr[i][c]=(n+i+j)%n ;
                c++;
            }
            for(j=1;j<=k_right; j++)
            {
                nbr[i][c]=(n+i+j)%n ;
                c++;
            }
            isRandom[i]=0;
        }
        else
        {   //random neighbors
            nbr[i] = sample(0,n-1,k,i);
            isRandom[i] = 1;
        }
    }
}

ostream& Small_World::display(ostream& os)const
{
	os<<"Connections :"<<endl;
	for(int i=0; i<nbr.size(); i++)
	{
		os<<"Node "<<i<<" : ";
		os<<nbr[i];
		os<< "\t isRandom = "<<isRandom[i];
		os<< endl;
	}
	return os;
}
