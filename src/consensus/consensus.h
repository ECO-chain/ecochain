// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_CONSENSUS_H
#define BITCOIN_CONSENSUS_CONSENSUS_H

#include <stdint.h>
#include "ecoc/ecoc.h"

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
extern unsigned int MaxBlockSerSize;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
extern unsigned int MaxBlockWeight;
/** The maximum allowed size for a block excluding witness data, in bytes (network rule) */
extern unsigned int MaxBlockBaseSize;

extern unsigned int MaxBlockSize;

/** The maximum allowed number of signature check operations in a block (network rule) */
extern int64_t MaxBlockSigOps;

extern unsigned int MaxProtoMsgLength;

extern unsigned int MaxTxSigOps;

/** Coinbase transaction outputs can only be spent after this number of new blocks (network rule) */
static const int COINBASE_MATURITY = ecoc::coinbaseMaturity; //default is 100 for bitoin (10 minutes/block, close to 17hours maturity)

static const int MAX_TRANSACTION_BASE_SIZE = 1000000; // ecoc: leave it 1M

/** Flags for nSequence and nLockTime locks */
enum {
    /* Interpret sequence numbers as relative lock-time constraints. */
    LOCKTIME_VERIFY_SEQUENCE = (1 << 0),

    /* Use GetMedianTimePast() instead of nTime for end point timestamp. */
    LOCKTIME_MEDIAN_TIME_PAST = (1 << 1),
};

#endif // BITCOIN_CONSENSUS_CONSENSUS_H
