// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       


#include "ecoc.h"
#include "chainparams.h"

namespace ecoc {

int getMultisigners(int height) {
  const Consensus::Params& params = Params().GetConsensus()

  if (height < params.ThemisHeight + 1) {
    return params.nOriginalMPoSRewardRecipients;
  }

  return params.nThemisMPoSRewardRecipients;
}

int getPoSReward(int height, const Consensus::Params& params) {
  const int ThemisHeight = params.ThemisHeight;
  const int lastRewardBlock = lastPoWBlock + params.lastPOSBlock;
  const int lastEpoch = ThemisHeight + 4*1000*1000;
  const int ThemisBlockReward = 5;

  if (height < ThemisHeight + 1) {
    return 50;
  }

  if (height > lastEpoch) {
    return 1;
  }

  if (height > lastRewardBlock) {
    return 0;
  }

  int rewardReduction = int((height - (ThemisHeight + 1)) / rewardSession);
  return (ThemisBlockReward - rewardReduction);
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
} // namespace ecoc
