// Copyright (c) 2018 The Eco Chain team
// Distributed under the GPLv3 software license, check
// https://www.gnu.org/licenses/gpl-3.0.en.html for details

#ifndef ECOC_H
#define ECOC_H

#include "util.h"
#include "chainparams.h"

namespace ecoc {
const bool debug = true;

const int lastPoWBlock = 10000; // turning block from PoW to PoS
const int blockTime = 32; // block time creation target
const int granularity = 7;
// const int consensusMultisigners = 10;
const int coinbaseMaturity = (600 * 100) / (blockTime); //600*100/blockTime = 1875 ; (formula proportional to bitcoin who has 600 secs and 100 blocks maturity)
const std::string ecoUnit = "ECOC";
const int minerSleepInSecs = 60; // delay the block creation for a minute
const int stakerPollingPeriod = 5000; // STAKER_POLLING_PERIOD in miliseconds
const int PoWReward = 20000; // reward of coins for each block at first phase (PoW)
// const int PoSReward = 50;                   // PoS reward, replaced with GetPosReward(height) at Themis hardfork
// const int maxHalvings = 4;                  // Number of doubling epochs, removes at Themis hardfork
const int rewardSession = 1 * 1000 * 1000; // how many blocks for reward reduction , about a year
const int blockSizeLimit = 4 * 1000 * 1000; // blocksize limit 4M
const int blockGasLimit = 20 * blockSizeLimit; // maximum gas per block , set it proportionally to blockSizeLimit
const int minTxGas = 40;

const std::string genesisBlockMainNet = "0000009cbd44612c6e231a74c6d5ae65dcc4a55fa728cc5aa55f0558bdcc7268";
const std::string genesisBlockTestNet = "0000005d73ef7042858df0f7fca1459d519ae0a209d68c9bf5701e61dd97fb42";
const std::string genesisBlockRegTest = "52b4ddc1be5a40a1c5cf3ad2280baa8e7a25b5e3fe02b9d229c476bd0830c8d6";
const std::string genesisMerkleRoot = "441bfed54efa3a027363d44aa74751180147bbad7e4a55f30213735b83a7d078";

void ecocLog(const std::string message);
void ecocLogNL(const std::string message);
void ecocLogNL(int i);
void ecocLog(int i);
void ecocLogFun(const std::string message);

int getPoSReward(int height, const Consensus::Params& params);
int getMultisigners(int height);
uint64_t getActualSupply(int height);
} // namespace ecoc

#endif // ECOC_H
