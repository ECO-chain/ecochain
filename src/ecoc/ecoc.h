// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       

#ifndef ECOC_H
#define ECOC_H

#include "util.h"
//#include "libethcore/SealEngine.cpp"

namespace ecoc {
  const bool debug = false;
  const int LastPoWBlock = 10000 ; // turning block from PoW to PoS
  const int BlockTime= 32 ; // block time creation target
  const int granularity = 7;
  const int consensusMultisigners = 10;
  const int coinbaseMaturity = (600*100)/(BlockTime); //600*100/BlockTime = 1875 ; (formula proportional to bitcoin who has 600 secs and 100 blocks maturity)
  const std::string ecoUnit = "ECO";
  const int MinerSleepInSecs = 60; // delay the block creation for a minute
  const int StakerPollingPeriod = 5000; //STAKER_POLLING_PERIOD in miliseconds
  const int PoWReward = 20000 ; // reward of coins for each block at first phase (PoW)
  const int PoSReward = 50 ; // PoS reward, doubling every epoch. After LastPoSBlock blocks reward is zero.
  const int maxHalvings = 4 ;// 4 POS epochs(sessions) , doubling until cap. Variable name (maxHalvings) stays unmodified for historical reasons (tribute to bitcoin)
  const int rewardSession= 2500000 ; // how many blocks for doubling the PoS reward , about two and a half years
  const int LastPoSBlock = 9812500 ; // LastPoWBlock + LastPoSBlock is the block height that gives the last reward (2 billion coins cap reached)
  const int blockSizeLimit = 4*1000*1000 ; // blocksize limit 4M
  const int blockGasLimit= 20 * blockSizeLimit; // maximum gas per block , set it proportionally to blockSizeLimit
  const int minTxGas = 40;

  const std::string genesisBlockMainNet = "0000009cbd44612c6e231a74c6d5ae65dcc4a55fa728cc5aa55f0558bdcc7268";
  const std::string genesisBlockTestNet = "0000005d73ef7042858df0f7fca1459d519ae0a209d68c9bf5701e61dd97fb42";
  const std::string genesisBlockRegTest = "52b4ddc1be5a40a1c5cf3ad2280baa8e7a25b5e3fe02b9d229c476bd0830c8d6";
  const std::string genesisMerkleRoot = "441bfed54efa3a027363d44aa74751180147bbad7e4a55f30213735b83a7d078";
  
  inline void ecocLog(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: %s\n", message);
    }
  }

  inline void ecocLogNL(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: %s", message);
    }
  }
  
  inline void ecocLogNL(int i) {
    if (debug) {
      LogPrintf("ecoc: %d", i);
    }
  }

  inline void ecocLog(int i) {
    if (debug) {
      LogPrintf("ecoc: %d\n", i);
    }
  }

  inline void ecocLogFun(const std::string message) {
    if (debug) {
      LogPrintf("ecoc: Entering function %s\n", message);
    }
  }
}

#endif // ECOC_H 
