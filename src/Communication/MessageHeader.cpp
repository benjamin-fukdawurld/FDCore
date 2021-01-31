#include <FDCore/Communication/MessageHeader.h>
#include <cstring>
#include <numeric>

bool FDCore::MessageHeader::hasField(std::string_view name) const
{
    return m_fields.find(name.data()) != m_fields.end();
}

const std::vector<uint8_t> &FDCore::MessageHeader::getFiled(std::string_view name) const
{
    return m_fields.find(name.data())->second;
}

void FDCore::MessageHeader::setFiled(std::string_view name, const FDCore::Span<uint8_t> &value)
{
    m_fields[name.data()] = std::vector<uint8_t>(value.data, value.data + value.size);
}

size_t FDCore::MessageHeader::size() const
{
    return std::accumulate(
      m_fields.begin(), m_fields.end(), size_t(4),
      [](size_t total, const std::pair<std::string, std::vector<uint8_t>> &field) -> size_t {
          return total + field.first.size() + 1 + field.second.size();
      });
}

uint32_t FDCore::MessageHeader::write(FDCore::Span<uint8_t> &output, uint32_t payloadLength)
{
    uint8_t *current = output.data + 5;
    memcpy(current, &payloadLength, 4);
    for(auto &field: m_fields)
    {
        uint32_t s = static_cast<uint32_t>(field.first.size()) + 1;
        memcpy(current, field.first.data(), s);
        current += s;
        s = field.second.size();
        memcpy(current, &s, 4);
        current += 4;
        memcpy(current, field.second.data(), s);
        current += s;
    }

    uint32_t length = current - output.data;
    memcpy(output.data + 1, &length, 4);
    return length;
}

uint32_t FDCore::MessageHeader::read(const FDCore::Span<uint8_t> &input)
{
    uint32_t headerLength = 0;
    const uint8_t *headerData = input.data + 9;
    memcpy(&headerLength, input.data + 1, 4);
    uint32_t offset = 0;
    while(offset < headerLength)
    {
        std::string name(reinterpret_cast<const char *>(headerData) + offset);
        offset += name.size() + 1;
        uint32_t fieldLength = 0;
        memcpy(&fieldLength, headerData + offset, 4);
        offset += 4;
        m_fields[name] =
          std::vector<uint8_t>(headerData + offset, headerData + offset + fieldLength);
        offset += fieldLength;
    }

    return offset;
}