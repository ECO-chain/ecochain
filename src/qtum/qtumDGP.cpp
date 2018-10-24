#include "qtumDGP.h"

void QtumDGP::initDataEIP158(){
    std::vector<uint32_t> tempData = {dev::eth::EIP158Schedule.tierStepGas[0], dev::eth::EIP158Schedule.tierStepGas[1], dev::eth::EIP158Schedule.tierStepGas[2],
                                      dev::eth::EIP158Schedule.tierStepGas[3], dev::eth::EIP158Schedule.tierStepGas[4], dev::eth::EIP158Schedule.tierStepGas[5],
                                      dev::eth::EIP158Schedule.tierStepGas[6], dev::eth::EIP158Schedule.tierStepGas[7], dev::eth::EIP158Schedule.expGas,
                                      dev::eth::EIP158Schedule.expByteGas, dev::eth::EIP158Schedule.sha3Gas, dev::eth::EIP158Schedule.sha3WordGas,
                                      dev::eth::EIP158Schedule.sloadGas, dev::eth::EIP158Schedule.sstoreSetGas, dev::eth::EIP158Schedule.sstoreResetGas,
                                      dev::eth::EIP158Schedule.sstoreRefundGas, dev::eth::EIP158Schedule.jumpdestGas, dev::eth::EIP158Schedule.logGas,
                                      dev::eth::EIP158Schedule.logDataGas, dev::eth::EIP158Schedule.logTopicGas, dev::eth::EIP158Schedule.createGas,
                                      dev::eth::EIP158Schedule.callGas, dev::eth::EIP158Schedule.callStipend, dev::eth::EIP158Schedule.callValueTransferGas,
                                      dev::eth::EIP158Schedule.callNewAccountGas, dev::eth::EIP158Schedule.suicideRefundGas, dev::eth::EIP158Schedule.memoryGas,
                                      dev::eth::EIP158Schedule.quadCoeffDiv, dev::eth::EIP158Schedule.createDataGas, dev::eth::EIP158Schedule.txGas,
                                      dev::eth::EIP158Schedule.txCreateGas, dev::eth::EIP158Schedule.txDataZeroGas, dev::eth::EIP158Schedule.txDataNonZeroGas,
                                      dev::eth::EIP158Schedule.copyGas, dev::eth::EIP158Schedule.extcodesizeGas, dev::eth::EIP158Schedule.extcodecopyGas,
                                      dev::eth::EIP158Schedule.balanceGas, dev::eth::EIP158Schedule.suicideGas, dev::eth::EIP158Schedule.maxCodeSize};
    dataEIP158Schedule = tempData;
}

uint64_t QtumDGP::getUint64FromDGP(unsigned int blockHeight, const dev::Address& contract, std::vector<unsigned char> data){
    uint64_t value = 0;
    if(initStorages(contract, blockHeight, data)){
        if(!dgpevm){
            parseStorageOneUint64(value);
        } else {
            parseDataOneUint64(value);
        }
    }
    return value;
}

bool QtumDGP::initStorages(const dev::Address& addr, unsigned int blockHeight, std::vector<unsigned char> data){
    initStorageDGP(addr);
    createParamsInstance();
    dev::Address address = getAddressForBlock(blockHeight);
    if(address != dev::Address()){
        if(!dgpevm){
            initStorageTemplate(address);
        } else {
            initDataTemplate(address, data);
        }
        return true;
    }
    return false;
}

void QtumDGP::initStorageDGP(const dev::Address& addr){
    storageDGP = state->storage(addr);
}

void QtumDGP::initStorageTemplate(const dev::Address& addr){
    storageTemplate = state->storage(addr);
}

void QtumDGP::initDataTemplate(const dev::Address& addr, std::vector<unsigned char>& data){
    dataTemplate = CallContract(addr, data)[0].execRes.output;
}

void QtumDGP::createParamsInstance(){
    dev::h256 paramsInstanceHash = sha3(dev::h256("0000000000000000000000000000000000000000000000000000000000000000"));
    if(storageDGP.count(paramsInstanceHash)){
        dev::u256 paramsInstanceSize = storageDGP.find(paramsInstanceHash)->second.second;
        for(size_t i = 0; i < size_t(paramsInstanceSize); i++){
            std::pair<unsigned int, dev::Address> params;
            params.first = uint64_t(storageDGP.find(sha3(paramsInstanceHash))->second.second);
            ++paramsInstanceHash;
            params.second = dev::right160(dev::h256(storageDGP.find(sha3(paramsInstanceHash))->second.second));
            ++paramsInstanceHash;
            paramsInstance.push_back(params);
        }
    }
}

dev::Address QtumDGP::getAddressForBlock(unsigned int blockHeight){
    for(auto i = paramsInstance.rbegin(); i != paramsInstance.rend(); i++){
        if(i->first <= blockHeight)
            return i->second;
    }
    return dev::Address();
}

static inline bool sortPairs(const std::pair<dev::u256, dev::u256>& a, const std::pair<dev::u256, dev::u256>& b){
    return a.first < b.first;
}

void QtumDGP::parseStorageScheduleContract(std::vector<uint32_t>& uint32Values){
    std::vector<std::pair<dev::u256, dev::u256>> data;
    for(size_t i = 0; i < 5; i++){
        dev::h256 gasScheduleHash = sha3(dev::h256(dev::u256(i)));
        if(storageTemplate.count(gasScheduleHash)){
            dev::u256 key = storageTemplate.find(gasScheduleHash)->second.first;
            dev::u256 value = storageTemplate.find(gasScheduleHash)->second.second;
            data.push_back(std::make_pair(key, value));
        }
    }

    std::sort(data.begin(), data.end(), sortPairs);

    for(std::pair<dev::u256, dev::u256> d : data){
        dev::u256 value = d.second;
        for(size_t i = 0; i < 4; i++){
            uint64_t uint64Value = uint64_t(value);
            value = value >> 64;

            uint32Values.push_back(uint32_t(uint64Value));
            uint64Value = uint64Value >> 32;
            uint32Values.push_back(uint32_t(uint64Value));
        }
    }
}

void QtumDGP::parseDataScheduleContract(std::vector<uint32_t>& uint32Values){
    size_t size = dataTemplate.size() / 32;
    for(size_t i = 0; i < size; i++){
        std::vector<unsigned char> value = std::vector<unsigned char>(dataTemplate.begin() + (i * 32), dataTemplate.begin() + ((i+1) * 32));
        dev::h256 valueTemp(value);
        uint32Values.push_back(uint64_t(dev::u256(valueTemp)));
    }
}

void QtumDGP::parseStorageOneUint64(uint64_t& value){
    dev::h256 blockSizeHash = sha3(dev::h256(dev::u256(0)));
    if(storageTemplate.count(blockSizeHash)){
        value = uint64_t(storageTemplate.find(blockSizeHash)->second.second);
    }
}

void QtumDGP::parseDataOneUint64(uint64_t& value){
    if(dataTemplate.size() == 32){
        value = uint64_t(dev::u256(dev::h256(dataTemplate)));
    }
}
