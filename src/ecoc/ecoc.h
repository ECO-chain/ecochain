// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       

#ifndef ECOC_H
#define ECOC_H

#include "util.h"
//#include "libethcore/SealEngine.cpp"

namespace ecoc {
  const bool debug = true;
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

  const std::string genesisBlockMainNet = "b1795f27caef43cb48ce1168d88a3bd1d3d925aeee6c34c695efc884a5b55278";
  const std::string genesisBlockTestNet = "b5656481d7f922e468dd4024b3e4c9be2486e5273ae1dacfa7d35eaa5c068fed";
  const std::string genesisBlockRegTest = "0af3850116f580171375d0fb852b43b36f1ae15b2c2eee0068d27d8440e294d4";
  const std::string genesisMerkleRoot = "4dbbe328a35a2ab40dbb6603e778feaae2153a55b5fe051ccff705804f34aae8";
  
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
