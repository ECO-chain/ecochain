#ifndef QTUMDGP_H
#define QTUMDGP_H

#include "qtumstate.h"
#include "primitives/block.h"
#include "validation.h"
#include "utilstrencodings.h"

static const dev::Address DGPCONTRACT4 = dev::Address("0000000000000000000000000000000000000083");

class QtumDGP {
    
public:

    QtumDGP(QtumState* _state, bool _dgpevm = true) : dgpevm(_dgpevm), state(_state) { initDataEIP158(); }

private:

    bool initStorages(const dev::Address& addr, unsigned int blockHeight, std::vector<unsigned char> data = std::vector<unsigned char>());

    void initStorageDGP(const dev::Address& addr);

    void initStorageTemplate(const dev::Address& addr);

    void initDataTemplate(const dev::Address& addr, std::vector<unsigned char>& data);

    void initDataEIP158();

    void createParamsInstance();

    dev::Address getAddressForBlock(unsigned int blockHeight);

    uint64_t getUint64FromDGP(unsigned int blockHeight, const dev::Address& contract, std::vector<unsigned char> data);

    void parseStorageScheduleContract(std::vector<uint32_t>& uint32Values);
    
    void parseDataScheduleContract(std::vector<uint32_t>& uint32Values);

    void parseStorageOneUint64(uint64_t& blockSize);

    void parseDataOneUint64(uint64_t& value);

    
    bool dgpevm;

    const QtumState* state;

    dev::Address templateContract;

    std::map<dev::h256, std::pair<dev::u256, dev::u256>> storageDGP;

    std::map<dev::h256, std::pair<dev::u256, dev::u256>> storageTemplate;

    std::vector<unsigned char> dataTemplate;

    std::vector<std::pair<unsigned int, dev::Address>> paramsInstance;

    std::vector<uint32_t> dataEIP158Schedule;

};
#endif
