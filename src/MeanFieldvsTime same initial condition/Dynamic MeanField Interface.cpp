#include "./../Small_World.cpp"
namespace parameter
{
    vector<int>    nRange {100};         /// enumerated
    vector<int>    kRange {2};                  /// enumerated

    vector<double> pRange { 0, 0.8 } ;             /// enumerated
    vector<double> bRange { -0.035 } ;   /// enumerated
    vector<double> cRange { 1 };     /// enumerated

    vector<int> n1Range { 0, 1  };  /// enumerated

    int link_period = 10  ;  /// active only if variant is "dynamic"
    double et = 40;
    double dt = 0.01;
}
#include "MeanField dynamic.cpp"
