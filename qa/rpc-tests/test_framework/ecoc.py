# helpers for ecochain
from test_framework.util import *
from test_framework.script import *
from test_framework.mininode import *
from test_framework.blocktools import *
from test_framework.key import *
from test_framework.address import *
import io
import time
import struct

# Default min gas price in satoshis
ECOC_MIN_GAS_PRICE = 40
ECOC_MIN_GAS_PRICE_STR = "0.00000040"

MPOS_PARTICIPANTS = 10
LAST_POW_BLOCK = 1000


def make_vin(node, value):
    addr = node.getrawchangeaddress()
    txid_hex = node.sendtoaddress(addr, value/COIN)
    txid = int(txid_hex, 16)
    node.generate(1)
    raw_tx = node.getrawtransaction(txid_hex, 1)

    for vout_index, txout in enumerate(raw_tx['vout']):
        if txout['scriptPubKey']['addresses'] == [addr]:
            break
    else:
        assert False

    return CTxIn(COutPoint(txid, vout_index), nSequence=0)

def make_op_call_output(value, version, gas_limit, gas_price, data, contract):
    scriptPubKey = CScript()
    scriptPubKey += version
    scriptPubKey += gas_limit
    scriptPubKey += gas_price
    scriptPubKey += data
    scriptPubKey += contract
    scriptPubKey += OP_CALL
    return CTxOut(value, scriptPubKey)

def make_transaction(node, vin, vout):
    tx = CTransaction()
    tx.vin = vin
    tx.vout = vout
    tx.rehash()
    
    unsigned_raw_tx = bytes_to_hex_str(tx.serialize_without_witness())
    signed_raw_tx = node.signrawtransaction(unsigned_raw_tx)['hex']
    return signed_raw_tx

def make_op_create_output(node, value, version, gas_limit, gas_price, data):
    scriptPubKey = CScript()
    scriptPubKey += version
    scriptPubKey += gas_limit
    scriptPubKey += gas_price
    scriptPubKey += data
    scriptPubKey += OP_CREATE
    return CTxOut(value, scriptPubKey)

def assert_vout(tx, expected_vout):
    assert_equal(len(tx['vout']), len(expected_vout))
    matches = []
    for expected in expected_vout:
        for i in range(len(tx['vout'])):
            if i not in matches and expected[0] == tx['vout'][i]['value'] and expected[1] == tx['vout'][i]['scriptPubKey']['type']:
                matches.append(i)
                break
    assert_equal(len(matches), len(expected_vout))

def assert_vin(tx, expected_vin):
    assert_equal(len(tx['vin']), len(expected_vin))
    matches = []
    for expected in expected_vin:
        for i in range(len(tx['vin'])):
            if i not in matches and expected[0] == tx['vin'][i]['scriptSig']['asm']:
                matches.append(i)
                break
    assert_equal(len(matches), len(expected_vin))


def rpc_sign_transaction(node, tx):
    ret = node.signrawtransaction(bytes_to_hex_str(tx.serialize()))
    assert(ret['complete'])
    tx_signed_raw_hex = ret['hex']
    f = io.BytesIO(hex_str_to_bytes(tx_signed_raw_hex))
    tx_signed = CTransaction()
    tx_signed.deserialize(f)
    return tx_signed


def collect_prevouts(node, amount=None):
    blocks = []
    for block_no in range(1, node.getblockcount()+1):
        blocks.append(node.getblock(node.getblockhash(block_no)))


    staking_prevouts = []
    for unspent in node.listunspent():
        for block in blocks:
            if unspent['txid'] in block['tx']:
                tx_block_time = block['time']
                break
        else:
            assert(False)

        if unspent['confirmations'] > COINBASE_MATURITY and (not amount or amount == unspent['amount']):
            staking_prevouts.append((COutPoint(int(unspent['txid'], 16), unspent['vout']), int(unspent['amount']*COIN), tx_block_time))
    return staking_prevouts


def create_unsigned_pos_block(node, staking_prevouts, nTime=None):
    tip = node.getblock(node.getbestblockhash())
    if not nTime:
        current_time = int(time.time()) + 16
        nTime = current_time & 0xfffffff0

    parent_block_stake_modifier = int(tip['modifier'], 16)
    coinbase = create_coinbase(tip['height']+1)
    coinbase.vout[0].nValue = 0
    coinbase.vout[0].scriptPubKey = b""
    coinbase.rehash()
    block = create_block(int(tip['hash'], 16), coinbase, nTime)
    block.hashStateRoot = int(tip['hashStateRoot'], 16)
    block.hashUTXORoot = int(tip['hashUTXORoot'], 16)

    if not block.solve_stake(parent_block_stake_modifier, staking_prevouts):
        return None

    txout = node.gettxout(hex(block.prevoutStake.hash)[2:], block.prevoutStake.n)
    # input value + block reward
    out_value = int((float(str(txout['value'])) + INITIAL_BLOCK_REWARD) * COIN) // 2

    # create a new private key used for block signing.
    block_sig_key = CECKey()
    block_sig_key.set_secretbytes(hash256(struct.pack('<I', random.randint(0, 0xff))))
    pubkey = block_sig_key.get_pubkey()
    scriptPubKey = CScript([pubkey, OP_CHECKSIG])
    stake_tx_unsigned = CTransaction()

    stake_tx_unsigned.vin.append(CTxIn(block.prevoutStake))
    stake_tx_unsigned.vout.append(CTxOut())

    # Split the output value into two separate txs
    stake_tx_unsigned.vout.append(CTxOut(int(out_value), scriptPubKey))
    stake_tx_unsigned.vout.append(CTxOut(int(out_value), scriptPubKey))

    stake_tx_signed_raw_hex = node.signrawtransaction(bytes_to_hex_str(stake_tx_unsigned.serialize()))['hex']
    f = io.BytesIO(hex_str_to_bytes(stake_tx_signed_raw_hex))
    stake_tx_signed = CTransaction()
    stake_tx_signed.deserialize(f)
    block.vtx.append(stake_tx_signed)
    block.hashMerkleRoot = block.calc_merkle_root()
    return (block, block_sig_key)


def create_unsigned_mpos_block(node, staking_prevouts, nTime=None, block_fees=0):
    mpos_block, block_sig_key = create_unsigned_pos_block(node, staking_prevouts, nTime)
    tip = node.getblock(node.getbestblockhash())

    # The block reward is constant for regtest
    stake_per_participant = int(INITIAL_BLOCK_REWARD*COIN+block_fees) // MPOS_PARTICIPANTS

    for i in range(MPOS_PARTICIPANTS-1):
        partipant_block = node.getblock(node.getblockhash(tip['height']-500-i))
        participant_tx = node.getrawtransaction(partipant_block['tx'][1], True)
        participant_pubkey = hex_str_to_bytes(participant_tx['vout'][1]['scriptPubKey']['asm'].split(' ')[0])
        mpos_block.vtx[1].vout.append(CTxOut(stake_per_participant, CScript([OP_DUP, OP_HASH160, hash160(participant_pubkey), OP_EQUALVERIFY, OP_CHECKSIG])))

    # the input value
    txout = node.gettxout(hex(mpos_block.prevoutStake.hash)[2:], mpos_block.prevoutStake.n)

    # Reward per output
    main_staker_reward = (int(float(str(txout['value']))*COIN) + stake_per_participant)

    mpos_block.vtx[1].vout[1].nValue = main_staker_reward // 2
    mpos_block.vtx[1].vout[2].nValue = main_staker_reward // 2

    stake_tx_signed_raw_hex = node.signrawtransaction(bytes_to_hex_str(mpos_block.vtx[1].serialize()))['hex']
    f = io.BytesIO(hex_str_to_bytes(stake_tx_signed_raw_hex))
    stake_tx_signed = CTransaction()
    stake_tx_signed.deserialize(f)
    mpos_block.vtx[1] = stake_tx_signed
    mpos_block.hashMerkleRoot = mpos_block.calc_merkle_root()
    return mpos_block, block_sig_key

# Generates 4490 - blockheight PoW blocks + 510 PoS blocks,
# i.e. block height afterwards will be 5000 and we will have valid MPoS participants.
def activate_mpos(node, use_cache=True):
    if not node.getblockcount():
        node.setmocktime(int(time.time()) - 1000000)
    node.generate(4490-node.getblockcount())
    staking_prevouts = collect_prevouts(node)

    for i in range(510):
        nTime = (node.getblock(node.getbestblockhash())['time']+45) & 0xfffffff0
        node.setmocktime(nTime)
        block, block_sig_key = create_unsigned_pos_block(node, staking_prevouts, nTime=nTime)
        block.sign_block(block_sig_key)
        block.rehash()
        block_count = node.getblockcount()
        assert_equal(node.submitblock(bytes_to_hex_str(block.serialize())), None)
        assert_equal(node.getblockcount(), block_count+1)

        # Remove the staking prevout so we don't accidently reuse it
        for j in range(len(staking_prevouts)):
            prevout = staking_prevouts[j]
            if prevout[0].serialize() == block.prevoutStake.serialize():
                staking_prevouts.pop(j)
                break


def make_vin_from_unspent(node, unspents=None, value=2000000000000, address=None):
    if not unspents:
        unspents = node.listunspent()
    for i in range(len(unspents)):
        unspent = unspents[i]
        if unspent['amount'] == value/COIN and (not address or address == unspent['address']):
            unspents.pop(i)
            return CTxIn(COutPoint(int(unspent['txid'], 16), unspent['vout']), nSequence=0)
    return None


def read_evm_array(node, address, abi, ignore_nulls=True):
    arr = []
    index = 0
    ret = node.callcontract(address, abi + hex(index)[2:].zfill(64))
    while ret['executionResult']['excepted'] == 'None':
        if int(ret['executionResult']['output'], 16) != 0 or not ignore_nulls:
            arr.append(ret['executionResult']['output'])
        index += 1
        ret = node.callcontract(address, abi + hex(index)[2:].zfill(64))
    return arr

def p2pkh_to_hex_hash(address):
    return str(base58_to_byte(address, 25)[1])[2:-1]

def hex_hash_to_p2pkh(hex_hash):
    return keyhash_to_p2pkh(hex_str_to_bytes(hex_hash))    
