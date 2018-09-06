/**
 * Simple driver that defines and produces the Sierpinksi Gasket. Saves the fractal data to disk
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <vector>

#include "model/algorithm/flame.h"
#include "model/variations/variations.h"

std::tuple<double, double> f1(double x, double y)
{
   return {x/2.0, y/2.0};
}
std::tuple<double, double> f2(double x, double y)
{
   return {(x+1.0)/2.0, y/2.0};
}
std::tuple<double, double> f3(double x, double y)
{
   return {x/2.0, (y+1.0)/2.0};
}

int main()
{
   Variation<double> v1 (
       f1, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0
   );
   v1.set_color(0.9);
   Variation<double> v2 (
       f2, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0
   );
   v2.set_color(0.65);
   Variation<double> v3 (
       f3, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0
   );
   v3.set_color(0.8);

   Flame<double> flame;
   flame.add_variation(v1);
   flame.add_variation(v2);
   flame.add_variation(v3);

   std::ofstream data("data.dat");
   data << std::fixed << std::setprecision(16);
   auto points = flame();
   for (const auto &p: points)
   {
       data << std::get<0>(p) << " " << std::get<1>(p) << " " << std::get<2>(p) << '\n';
   }
   data << std::flush;
}
