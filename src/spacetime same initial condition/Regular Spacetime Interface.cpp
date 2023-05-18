#include "./../Small_World.cpp"
namespace parameter
{
    const vector<int>    nRange {100};         /// enumerated
    const vector<int>    kRange {2};                  /// enumerated

    const vector<double> bRange { -0.035 } ;   /// enumerated
    const vector<double> cRange { 1 };     /// enumerated

    const vector<int> n1Range { 0,1,30  };  /// enumerated
    constexpr double et = 25;
    constexpr double dt = 0.01;
}
#include "source/Regular spacetime.cpp"
