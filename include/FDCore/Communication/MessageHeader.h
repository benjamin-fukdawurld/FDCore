#ifndef FDCORE_COMMUNICATION_MESSAGEHEADER_H
#define FDCORE_COMMUNICATION_MESSAGEHEADER_H

#include <FDCore/Common/Span.h>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace FDCore
{
    class MessageHeader
    {
      private:
        std::unordered_map<std::string, std::vector<uint8_t>> m_fields;
        uint32_t m_payloadLength;

      public:
        MessageHeader() : MessageHeader(0) {}
        MessageHeader(uint32_t payloadLength) : m_payloadLength(payloadLength) {}

        bool hasField(std::string_view name) const;
        const std::vector<uint8_t> &getFiled(std::string_view name) const;
        void setFiled(std::string_view name, const Span<uint8_t> &value);

        uint32_t getPayloadLength() const { return m_payloadLength; }
        void setPayloadLength(uint32_t length) { m_payloadLength = length; }

        size_t size() const;

        uint32_t write(Span<uint8_t> &output, uint32_t payloadLength);
        uint32_t read(const Span<uint8_t> &input);
    };
} // namespace FDCore

#endif // FDCORE_COMMUNICATION_MESSAGEHEADER_H