#pragma once

#include <map>
#include <type_traits>
#include <utility>
#include <vector>

template <typename fp, typename = std::enable_if_t<std::is_floating_point_v<fp>>>
class Variation
{
using function = std::tuple<fp, fp>(*)(fp, fp);

public:
   Variation(function _func, fp _a, fp _b, fp _c, fp _d, fp _e, fp _f) :
      func(_func),
      a(_a),
      b(_b),
      c(_c),
      d(_d),
      e(_e),
      f(_f)
   {}

   std::tuple<fp, fp> operator()(const fp x, const fp y)
   {
      std::tuple<fp,fp> value {0.0, 0.0};
      for (const auto &v : blend)
      {
          auto unblended {func(a*x + b*y + c, d*x + e*y + f)};
          std::get<0>(value) += v.second * std::get<0>(unblended);
          std::get<1>(value) += v.second * std::get<1>(unblended);
      }
      return value;
   }

   fp get_color() const {return color;}
   void set_color(const fp _color) {color = _color;}

   fp get_blend(const Variation* _variation) {return blend[_variation];}
   void set_blend(const Variation* _variation, fp _blend_coeff) {blend[_variation] = _blend_coeff;}

private:
    function func;
    fp a {1.0};
    fp b {0.0};
    fp c {0.0};
    fp d {0.0};
    fp e {1.0};
    fp f {0.0};
    fp color {0.0};
    std::map<const Variation*, fp> blend {{this, 1.0}};
};