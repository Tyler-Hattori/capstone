#pragma once

namespace racecar_simulator {

struct InterestingPoint {
  double x;
  double y;
  std::string frame;
  int interest;
};
  
struct SeenPoint {
  double index;
  int confidence;
};

}
