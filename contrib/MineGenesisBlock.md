To mine the geneis block you need to add the following code inside the file src/chainparams.cpp:

```C++
bool CheckProofOfWork(uint256 hash, unsigned int nBits, const Consensus::Params& params) {
    bool fNegative;
    bool fOverflow;
    arith_uint256 bnTarget;

    bnTarget.SetCompact(nBits, &fNegative, &fOverflow);

    // Check proof of work matches claimed amount
    if (UintToArith256(hash) > bnTarget) {
        return false;
    }
    return true;
}

* mine genesis block */
	
	while(!CheckProofOfWork(genesis.GetHash(), genesis.nBits, Params().GetConsensus())) { 
       ++genesis.nNonce;
       }
       printf("nonce: %u\n",genesis.nNonce);

```

This should prinrt the nonce after a while (depending on CPU power and nbits). After that, remove the above code and set it as second argument at  CreateGenesisBlock() :

```C++
genesis = CreateGenesisBlock(<timestamp> , <nonce> , <nbit>, 1, 50 * COIN);
```
restart the deamon and check the debug.log file. You should be able to see the hash of the genesis block. Place it at ecoc/ecoc.h:
```C++
const std::string genesisBlockMainNet = "<hashHere>";
```
 Stop the daemon, remove all chain data, recompile and start again. 
 Done! 