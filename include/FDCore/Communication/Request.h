#ifndef FDCORE_COMMUNICATION_REQUEST_H
#define FDCORE_COMMUNICATION_REQUEST_H

#include <FDCore/Communication/MessageHeader.h>
#include <FDCore/Communication/RequestType.h>
#include <cstdint>
#include <cstring>
#include <vector>

namespace FDCore
{
    class Request
    {
      private:
        RequestType m_type;
        MessageHeader m_header;
        std::vector<uint8_t> m_payload;
    };
} // namespace FDCore

#endif // FDCORE_COMMUNICATION_REQUEST_H