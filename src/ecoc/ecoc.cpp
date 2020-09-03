// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details

#include "ecoc.h"
#include "chainparams.h"

namespace ecoc
{
int getMultisigners(int height) {
    const Consensus::Params& params = Params().GetConsensus();
    const int ThemisHeight = params.ThemisHeight;

    if (height < ThemisHeight + 1) {
        return params.nOriginalMPoSRewardRecipients;
    }

    return params.nThemisMPoSRewardRecipients;
}

int getPoSReward(int height, const Consensus::Params& params)
{
    const int ThemisHeight = params.ThemisHeight;
    const int lastRewardBlock = lastPoWBlock + params.lastPOSBlock;
    const int lastEpoch = ThemisHeight + (4 * rewardSession);
    const int ThemisBlockReward = 5;

    /* redundant check */
    if (height > lastRewardBlock) {
        return 0;
    }

    if (height < ThemisHeight + 1) {
        return 50;
    }

    if (height > lastEpoch) {
        return 1;
    }

    int rewardReduction = int((height - (ThemisHeight + 1)) / rewardSession);
    return ThemisBlockReward - rewardReduction;
}

uint64_t getActualSupply(int height)
{
    const Consensus::Params& params = Params().GetConsensus();
    const int ThemisHeight = params.ThemisHeight;
    int epochPeriod = rewardSession;
    uint64_t actualSupply;

    if (height <= lastPoWBlock) {
        actualSupply = height * PoWReward;
    }
    else if (height <= ThemisHeight) {
        actualSupply = lastPoWBlock * PoWReward + (height - lastPoWBlock) * 50;
    }
    else if (height > ThemisHeight && height <= lastPoWBlock + params.lastPOSBlock) {
        actualSupply = lastPoWBlock * PoWReward + (ThemisHeight - lastPoWBlock) * 50; /* actualy supply at themis height*/
        for (int epoch = 1; epoch <= 5; epoch++) {
            if (epoch == 5) {
                epochPeriod = lastPoWBlock + params.lastPOSBlock - ThemisHeight - 4 * epochPeriod;
            }
            actualSupply += std::max(0, (6 - epoch) * std::min(epochPeriod, height - ThemisHeight - (epoch - 1) * rewardSession));
        }
    }
    else {
        actualSupply = 300 * 1000 * 1000;
    }

    return actualSupply;
}

void ecocLog(const std::string message)
{
    if (debug) {
        LogPrintf("ecoc: %s\n", message);
    }
}

void ecocLogNL(const std::string message)
{
    if (debug) {
        LogPrintf("ecoc: %s", message);
    }
}

void ecocLogNL(int i)
{
    if (debug) {
        LogPrintf("ecoc: %d", i);
    }
}

void ecocLog(int i)
{
    if (debug) {
        LogPrintf("ecoc: %d\n", i);
    }
}

void ecocLogFun(const std::string message)
{
    if (debug) {
        LogPrintf("ecoc: Entering function %s\n", message);
    }
}
} // namespace ecoc
