// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       


#include "ecoc.h"
#include "chainparams.h"

namespace ecoc {

  int getMultisigners(int height) {
    const int ThemisHeight = Params().GetConsensus().ThemisHeight;
    int multisigners = 10;
    if (height > ThemisHeight) {
      multisigners = 5;
    }
    return multisigners;
  }

  int GetPoSReward(int height) {
    const int ThemisHeight = Params().GetConsensus().ThemisHeight;
    const int lastRewardBlock = LastPoWBlock + Params().GetConsensus().lastPOSBlock;
    int reward ;
    int lastEpoch = ThemisHeight + 4*1000*1000 ;
    if (height < ThemisHeight+1) {
      reward = 50;
      return reward;
    } else {
      reward = 5 - int((height -(ThemisHeight + 1))/rewardSession);
    }
    if (height > lastEpoch) {
      reward = 1;
    }
    if (height > lastRewardBlock ) {
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

