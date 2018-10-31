#include "pxt.h"
#include "KeyValueService.h"

namespace blockytalky {
    KeyValueService* _pService = NULL;

    //%
    void startBluetoothService() {
        if (NULL != _pService) return;

        _pService = new KeyValueService(*uBit.ble);
    }

    //%
    void sendMessage(String key, int type, Buffer value) {
        startBluetoothService();
        _pService->send(key, type, value);
    }

    //%
    String receivedKey() {
        startBluetoothService();
        auto msg = _pService->receivedMessage();
        return mkString(msg.key);
    }

    //%
    int receivedType() {
        startBluetoothService();
        auto msg = _pService->receivedMessage();
        return msg.type;
    }

    //%
    String receivedString() {
        startBluetoothService();
        auto msg = _pService->receivedMessage();
        return msg.type == BlockyTalkyMessageType::StringType 
            ? mkString((char*)msg.value) 
            : mkString(NULL);
    }

    //%
    Buffer receivedBuffer() {
        startBluetoothService();
        auto msg = _pService->receivedMessage();
        return msg.type == BlockyTalkyMessageType::Int32LE 
            ? mkBuffer(msg.value, 4) 
            : msg.type == BlockyTalkyMessageType::Float64LE 
            ? mkBuffer(msg.value, 8)
            : mkBuffer(NULL, 0);
    }

}