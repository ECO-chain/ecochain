# ECOchain
**Official website**: [ecoc.io](https://ecoc.io)

ECOchain is a public (permissionless) blockchain. The ECO stands for eco-friendly, e-commerce and economy. Our ambition is to attract decentralized applications that are targeting the business world.

There are a bunch of projects involved in this repository:
- Bitcoin
- Ethereum
- Proof of Stake (PoS) consensus algorithm of Blackcoin

## Project highlights

**Bitcoin:**
Bitcoin uses the unspent transaction output (UTXO) account model, which is a method of verifying if a transaction is included in a block without downloading it. This is called Simplified Payment Verification (SPV), and allows wallets to be thin.

**Ethereum:**
Because Bitcoin has no smart contract functionality, Ethereum adds turing complete functionality, making smart contracts possible.

**Blackckoin:**
Bitcoin and Ethereum are based on Proof of Work (PoW). Blackckoin provides the Proof of Stake (PoS) consensus algorithm. Blackckoin is a descendant of peercoin, but removed the coinage factor completely to make the algorithm safer.

Additionally, Account Abstract Layer (AAL) allows integration of EVM with Bitcoin blockchains.

## ECOchain's goals
- To be trusted by people and businesses, real decentralization is needed. Bitcoin's codebase and consensus protocol guarantees this.
- Easy to use for developers and companies. Because of turing completeness of EVM and Ethereum's large community base, complete documentation, tutorials, there is an abundance of knowledge on solidity. Also, there are a lot of avilable tools for Ethereum and Ethereum Virtual Machine (EVM).
- User friendly for the consumer. We need wallets that can run on any agent, including mobile phones without using 3rd party applications and/or services for security reasons. This is possible because of the UTXO account model of Bitcoin which SPV implements. No need for the agent to download the whole chain in order to make transactions.
- Not wasting resources valuable to humanity. Public awareness and regulators are sensitive to this issue. With Proof of Stake no "mining" is needed for maintenance and growth of the chain.
- Financially sound solution.High TpS (Transactions per second)can be achieved on-chain and very high off-chain. On-chain transaction speed is about 540 TpS while off-chain practically umlimited and is based on a second  second layer network and can bring fast and private transactions for the user of the blockchain. This layer is not necessary to be installed if the user do not wish to use off-chain transactions. Offchain is targeting to smart contracs (tokens or Dapp functions).

## ECOchain's special features
- Tuned public chain, trully decentralized (can sustain myriads of nodes), which is suitable for commercial dApps. Relatively fast block creation, enough transactions per second, easy of development etc.
- Option for off-chain transactions for dApps, which brings more privacy, instant transactions and no fees (a fixed fee only to open and close the channel, not being affected by the number of transactions).
- Modified smart contract compiler to give option to developers for non-turing complete mode. Adds more security features using the safe-subset version of eco-solidity compiler. So the developers can choose the turing complete mode or the self-restricted but more secure non-turing complete mode. This is a bug breakthrough as smart contract develpment is plagued today with many security vulernabilities. 


**License**
Any files that are not explicitly refer to a license are considered under [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html).

