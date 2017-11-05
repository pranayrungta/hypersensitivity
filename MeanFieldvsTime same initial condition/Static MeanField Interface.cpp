#include "./../Small_World.cpp"
namespace parameter
{
    vector<int>    nRange {100};         /// enumerated
    vector<int>    kRange {2};                  /// enumerated

    vector<double> pRange { 0, 0.8 } ;             /// enumerated
    vector<double> bRange {-0.075 } ;   /// enumerated
    vector<double> cRange { 1 };     /// enumerated

    vector<int> n1Range { 0, 1  };  /// enumerated

    double et = 40;
    double dt = 0.01;
}
#include "MeanField static.cpp"
