// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       


#include "ecoc.h"
#define THEMIS_HEIGHT 850001

namespace ecoc {

  int GetPoSReward(int height) {
    int reward ;
    if (height < THEMIS_HEIGHT) {
      reward = 50;
      return reward;
    } else {
      reward = 5 - int((height -THEMIS_HEIGHT)/rewardSession);
    }
    if (height > 4850000) {
      reward = 1;
    }
    if (height > 48850000) {
      reward = 0;
    }
    return reward;
  }
    void ecocLog(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: %s\n", message);
    }
  }

  void ecocLogNL(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: %s", message);
    }
  }
  
  void ecocLogNL(int i) {
    if (debug) {
      LogPrintf("ecoc: %d", i);
    }
  }

  void ecocLog(int i) {
    if (debug) {
      LogPrintf("ecoc: %d\n", i);
    }
  }

  void ecocLogFun(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: Entering function %s\n", message);
    }
  }
}

