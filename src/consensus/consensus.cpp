#include "consensus.h"
#include "primitives/transaction.h"
#include "policy/policy.h"

/** The maximum allowed size for a serialized block, in bytes (only for buffer size limits) */
unsigned int MaxBlockSerSize = WITNESS_SCALE_FACTOR * ecoc::blockSizeLimit;
/** The maximum allowed weight for a block, see BIP 141 (network rule) */
unsigned int MaxBlockWeight = WITNESS_SCALE_FACTOR * ecoc::blockSizeLimit;
/** The maximum allowed size for a block excluding witness data, in bytes (network rule) */
unsigned int MaxBlockBaseSize = ecoc::blockSizeLimit;
unsigned int MaxBlockSize = ecoc::blockSizeLimit;

/** The maximum allowed number of signature check operations in a block (network rule) */
int64_t MaxBlockSigOps = WITNESS_SCALE_FACTOR * MaxBlockBaseSize/100;
unsigned int MaxProtoMsgLength = WITNESS_SCALE_FACTOR  * ecoc::blockSizeLimit;
unsigned int MaxTxSigOps = MaxBlockSigOps/5;
