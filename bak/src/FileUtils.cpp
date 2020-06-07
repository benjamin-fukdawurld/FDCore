#include <FDCore/FileUtils.h>
#include <cstdio>
#include <iostream>

std::unique_ptr<char[]> FDCore::readFile(const std::string &fileName)
{
    std::unique_ptr<char[]> output;
    std::unique_ptr<FILE, int (*)(FILE *)> file(fopen(fileName.c_str(), "r"), fclose);
    if(!file)
    {
        std::cerr << "The file descriptor is not set" << std::endl;
        return output;
    }

    size_t count = 0;

    fseek(file.get(), 0, SEEK_END);
    count = static_cast<size_t>(ftell(file.get()));
    rewind(file.get());

    if(!count)
        return output;

    output.reset(new char[count + 1]());
    fread(output.get(), sizeof(char), count, file.get());

    return output;
}

std::unique_ptr<uint8_t[]> FDCore::readBinaryFile(const std::string &fileName, size_t &size)
{
    std::unique_ptr<uint8_t[]> output;
    std::unique_ptr<FILE, int (*)(FILE *)> file(fopen(fileName.c_str(), "r"), fclose);
    if(!file)
    {
        std::cerr << "The file descriptor is not set" << std::endl;
        return output;
    }

    size = 0;

    fseek(file.get(), 0, SEEK_END);
    size = static_cast<size_t>(ftell(file.get()));
    rewind(file.get());

    if(!size)
        return output;

    output.reset(new uint8_t[size]());
    fread(output.get(), sizeof(uint8_t), size, file.get());

    return output;
}
