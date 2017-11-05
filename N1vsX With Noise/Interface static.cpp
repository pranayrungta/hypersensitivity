#include "./../Small_world.cpp"
namespace parameter
{
    const vector<int>    nRange {100, 250, 500};         /// enumerated
    const vector<int>    kRange {2, 4};                  /// enumerated

    const vector<double> pRange { 0, 0.1, 0.3, 0.5, 0.7, 0.9 } ;             /// enumerated
    const vector<double> bRange { 0, -0.02, -0.04, -0.06, -0.08, -0.10 } ;   /// enumerated
    const vector<double> cRange { 1 };     /// enumerated

    const vector<int> n1_limits_in_percentage { 0, 60, 1 };  /// range
    constexpr int repetitions = 100 ;

    constexpr double et = 50;
    constexpr double dt = 0.01;
    constexpr double lp = 100;

    constexpr double noiseStrength = 0.1 ;
}
#include "Analysis static.cpp"
