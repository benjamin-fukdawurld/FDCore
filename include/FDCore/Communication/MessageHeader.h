#ifndef FDCORE_COMMUNICATION_MESSAGEHEADER_H
#define FDCORE_COMMUNICATION_MESSAGEHEADER_H

#include <Common/Span.h>
#include <cstdint>
#include <numeric>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace FDCore
{
    class MessageHeader
    {
      private:
        std::unordered_map<std::string, std::vector<uint8_t>> m_fields;

      public:
        MessageHeader() = default;

        const std::vector<uint8_t> getFiled(std::string_view name) const

          size_t size() const
        {
            typedef std::unordered_map<std::string, std::vector<uint8_t>>::const_iterator iterator;
            return std::accumulate<iterator, size_t>(
              m_fields.begin(), m_fields.end(), 4,
              [](size_t total, const std::pair<std::string, std::vector<uint8_t>> *field)
                -> size_t { return total + field->first.size() + 1 + field->second.size() });
        }

        uint32_t write(Span<uint8_t> &output, uint32_t payloadLength)
        {
            uint8_t *current = output.data + 5;
            memcpy(current, &payloadLength, 4);
            for(auto &field: m_fields)
            {
                size_t s = field.first.size() + 1;
                memcpy(current, field.first.data, s);
                current += s;
                memcpy(current, &field.second.size, 4);
                current += 4;
                memcpy(current, field.second.data, field.second.size);
                current += field.second.size;
            }

            uint32_t length = current - output.data;
            memcpy(output.data, &length, 4);
            return length;
        }

        uint32_t read(const Span<uint8_t> &input)
        {
            uint32_t result = 0;
            uint8_t *current = input.data + 9;
        }
    };
} // namespace FDCore

#endif // FDCORE_COMMUNICATION_MESSAGEHEADER_H