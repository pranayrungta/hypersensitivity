#include "./../../Small_World.cpp"
#include "synthetic_genetic_network.cpp"
namespace parameter
{
    const vector<int>    nRange {100};         /// enumerated
    const vector<int>    kRange {2};                  /// enumerated

    const vector<double> pRange { -0.6} ;/// enumerated
    const vector<double> bRange { -0.1 } ;/// enumerated
    const vector<double> cRange { 1 };     /// enumerated

    const vector<int> n1_limits_in_percentage { 0, 60, 1 };  /// range

    constexpr double et = 20;
    constexpr double dt = 0.01;
    constexpr int repetitions = 10 ;
    constexpr int lp = 10;
}
#include "./../Heterogeneity Analysis static.cpp"
