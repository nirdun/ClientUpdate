#pragma once

#include "BasePacket.h"
#include <string>
#include <vector>


class BCASTPacket : public BasePacket {
private:
    std::string Filename;
    bool fileAdded = false;

public:
    BCASTPacket(std::vector<char> &bytes);

    BCASTPacket(char addOrDelete, const std::string &filename);

    BCASTPacket(const std::string &filename);

    //todo initiailize while getting bytes.
    virtual std::string getFileName();

    virtual void setFilename(const std::string &filename);

    virtual bool isFileAdded();

    virtual void setFileAdded(bool fileAdded);

    virtual bool haveEndByte() override;

    void printMessage();
};