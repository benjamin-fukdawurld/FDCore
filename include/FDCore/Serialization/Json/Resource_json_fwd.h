#ifndef FDCORE_RESOURCE_JSON_FWD_H
#define FDCORE_RESOURCE_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FDCore/BaseResource.h>

namespace FDJson
{
    template<typename T>
    std::enable_if_t<std::is_same_v<T, FDCore::AbstractResource> || std::is_same_v<T, FDCore::BaseResource>,
    rapidjson::Value> serialize(const T &res, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same_v<T, FDCore::AbstractResource> || std::is_same_v<T, FDCore::BaseResource>,
    bool> unserialize(const rapidjson::Value &val, T &cam, Serializer &serializer, std::string *err = nullptr);
}

#endif // FDCORE_RESOURCE_JSON_FWD_H
