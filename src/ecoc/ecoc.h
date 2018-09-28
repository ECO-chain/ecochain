// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details       

#ifndef ECOC_H
#define ECOC_H

#include "util.h"

namespace ecoc {
  const bool debug = true;
  const int LastPoWBlock = 1000 ; // turning block from PoW to PoS
  const int BlockTime= 2 * 64; // block time creation target
  const int granularity = 15;
  const int consensusMultisigners = 3;
  const int coinbaseMaturity = 500;
  const std::string ecoUnit = "ECO";
  const int MinerSleepInSecs = 60; // delay the block creation for a minute
  const int StakerPollingPeriod = 5000; //STAKER_POLLING_PERIOD in miliseconds
  const int PoWReward = 100000 ; // reward of coins for each block at first phase (PoW)
  const int PoSReward = 2 ; // Starting PoS reward (before halving). Equals to around 1%/year for 100M coins and 1 mimute block creation time
  const int maxHalvings = 7 ;
  const int rewardSession= 985500 ; // how many blocks for falving the PoS reward
  const int blockSizeLimit = 2000000 ; // blocksize limit

  const std::string genesisBlockMainNet = "a7a28c6e747327810ebb5d3b62beae2420f1417691594f45d289d64da2835bed";
  const std::string genesisBlockTestNet = "d78c882bd8433d357fd0a68c818444b9e33a377fed01bc9e6ce1e7fce883d917";
  const std::string genesisBlockRegTest = "1831dde9a594c08a342d9dd547c446e733a69e5ff511f1d50d9dc48a16e9f901";
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
