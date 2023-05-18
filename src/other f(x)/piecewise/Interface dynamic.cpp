#include "./../../Small_World.cpp"
#include "piecewise.cpp"
namespace parameter
{
    const vector<int>    nRange {100};         /// enumerated
    const vector<int>    kRange {2};                  /// enumerated

    const vector<double> pRange { 0, 0.1, 0.3, 0.5, 0.7, 0.9 } ;             /// enumerated
    const vector<double> bRange { 0, -0.02, -0.04, -0.06, -0.08, -0.10 } ;   /// enumerated
    const vector<double> cRange { 1 };     /// enumerated

    const vector<int> n1_limits_in_percentage { 0, 60, 1 };  /// range

    constexpr double et = 20;
    constexpr double dt = 0.01;
    constexpr int repetitions = 1 ;
    constexpr int lp = 10;

    constexpr int link_period = 10  ;
}
#include "./../Heterogeneity Analysis dynamic.cpp"
