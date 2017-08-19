#include "constrained.hpp"

struct acceptable_limits : public limits<double>
{
   static constexpr double Min = -3.0;
   static constexpr double Max = 7.0;
};

int main()
{
    using namespace std;

    constrained_integral<int, 0, 3> n(2);
    constrained<double, acceptable_limits> f(0.5);
    normalized<float> m(0.7);
    positive<long long> l(30);
    negative<signed int> x(-30);

    return 0;
}
