#pragma once

#include <random>
#include <tuple>
#include <type_traits>
#include <vector>
#include <iostream>
#include "model/variations/variations.h"

template <typename fp, typename = std::enable_if_t<std::is_floating_point_v<fp>>>
class Flame
{
using function = std::tuple<fp, fp>(*)(fp, fp);

public:
   std::vector<std::tuple<fp, fp, fp>> operator()()
   {
      std::mt19937_64 rng;
      std::uniform_real_distribution<fp> biunit_dis(-1.0, 1.0);
      std::uniform_int_distribution<size_t> variation_index_dis(0, variations.size()-1);

      std::tuple<fp, fp> point
      {
          biunit_dis(rng),
          biunit_dis(rng)
      };

      fp x {std::get<0>(point)};
      fp y {std::get<1>(point)};
      fp c {biunit_dis(rng)};

      for (int i {0}; i < 20; ++i)
      {
         size_t varidx {variation_index_dis(rng)};
         c = (c + variations[varidx].get_color()) / 2.0;
         std::tie(x, y) = variations[varidx](x, y);
      }

      std::vector<std::tuple<fp, fp, fp>> points;
      for (int i {0}; i < 9980; ++i)
      {
         size_t varidx {variation_index_dis(rng)};
         std::tie(x, y) = variations[varidx](x, y);
         c = (c + variations[varidx].get_color()) / 2.0;
         points.push_back({x, y, c});
      }
      return points;
   }

   void add_variation(Variation<fp> variation)
   {
      variations.push_back(variation);
   }

private:
    std::vector<Variation<fp>> variations;
};