// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       

#ifndef ECOC_H
#define ECOC_H

#include "util.h"
//#include "libethcore/SealEngine.cpp"

namespace ecoc {
  const bool debug = true;
  const int LastPoWBlock = 1000 ; // turning block from PoW to PoS
  const int BlockTime= 32 ; // block time creation target
  const int granularity = 7;
  const int consensusMultisigners = 10;
  const int coinbaseMaturity = 500; //600*100/BlockTime; (formula proportional to bitcoin who has 600 secs and 100 blocks maturity)
  const std::string ecoUnit = "ECO";
  const int MinerSleepInSecs = 60; // delay the block creation for a minute
  const int StakerPollingPeriod = 5000; //STAKER_POLLING_PERIOD in miliseconds
  const int PoWReward = 100000 ; // reward of coins for each block at first phase (PoW)
  const int PoSReward = 1 ; // Starting PoS reward (before halving). Equals to around 1%/year for 100M coins and 32 secs block creation time
  const int maxHalvings = 7 ;
  const int rewardSession= 985500 ; // how many blocks for falving the PoS reward , about a year
  const int blockSizeLimit = 4*1000*1000 ; // blocksize limit 4M
  const int blockGasLimit= 20 * blockSizeLimit; // maximum gas per block , set it proportionally to blockSizeLimit
  const int minTxGas = 40;

  //  dev::eth::EVMSchedule GAS_SCHEDULE = dev::eth::EIP158Schedule;
  
  const std::string genesisBlockMainNet = "523db1d28b252258af6d353847e5143df930933cdefe6264159b2a062651fa5d";
  const std::string genesisBlockTestNet = "45c3a65f2a3cfced71af53d7081f4286b8efc7b339fb39ddb5ee189155886281";
  const std::string genesisBlockRegTest = "72904736917e5c9c4a493405b9a59dc35e86bcda145cbe38684109a3c1c23695";
  const std::string genesisMerkleRoot = "d56e5980fb608781d0694199ced021c3cd9c1acdf98ff05251aba661c7e49c13";
  
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
