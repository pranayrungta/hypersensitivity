#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<algorithm>
#include<stdexcept>
#include<cmath>
using namespace std ;

mt19937 generator(time(NULL));//(12345);

class topology_base
{public:
    const vector<int>& operator[](const int i) const
    {   return nbr[i];  }

    int size() const
    {   return nbr.size(); }

protected:
    vector<vector<int>>  nbr;
};



template<typename T>
ostream& operator<<(ostream& os, const vector<T> var);

vector<int> sample_by_random_pickup(const int& lower, const int& upper, const int& no_of_samples, const int& except);

vector<int> sample_by_shuffle(const int& lower, const int& upper, const int& no_of_samples, const int& except, const int& size);

vector<int> sample(const int& lower, const int& upper, const int& no_of_samples, const int& except);


int main_toTest2()
{
	topology_base a;
}



///-------implementation of common functions-------

template<typename T>
ostream& operator<<(ostream& os, const vector<T> var)
{
    os<<"[ ";
    if(var.size()>0)
    {
        os<< var[0];
        for(int i=1; i<var.size(); i++)
            os<<", "<<var[i];
    }
    os<<" ]";
    return os;
}

//function to generate set of distinct random numbers excluding one number
vector<int> sample_by_random_pickup(const int& lower, const int& upper, const int& no_of_samples, const int& except)
{
    uniform_int_distribution<int> dis(lower, upper);
    bool flag=0;
    vector<int> result(no_of_samples);
    int c=0, r=0;
    while(c<no_of_samples)
    {
        r=dis(generator);
        flag=0;
        for(int i=0; i<c; i++)
        if (r==result[i]){ flag=1; break;}
        if (flag==0 && r!=except) {result[c]=r; c++; }
    }
    return result;
}

vector<int> sample_by_shuffle(const int& lower, const int& upper, const int& no_of_samples, const int& except, const int& size)
{
    if(   ( (except<=upper && except>=lower) && no_of_samples>size-1 )
        ||(no_of_samples>size)   )
    throw runtime_error("cannot sample : more numbers requested than available range");
    vector<int> x;
    x.reserve(size);

    for(int i=lower; i<=upper; i++)
        if(i!=except) x.push_back(i);
    shuffle(x.begin(), x.end(), generator);
    x.resize(no_of_samples);
    return x;
}

vector<int> sample(const int& lower, const int& upper, const int& no_of_samples, const int& except)
{
    int size = upper-lower+1;
    if( (no_of_samples*100.0)/size > 15)
        return sample_by_shuffle(lower,upper,no_of_samples,except,size);
    else
        return sample_by_random_pickup(lower,upper,no_of_samples,except);
}

