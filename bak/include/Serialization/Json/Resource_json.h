#ifndef FDCORE_RESOURCE_JSON_H
#define FDCORE_RESOURCE_JSON_H

#include <FDCore/BaseResource.h>
#include <FDCore/Serialization/Json/Object_json_fwd.h>
#include <FDCore/Serialization/Json/Resource_json_fwd.h>
#include <FDJson/JsonSerializer.h>

template<typename T>
std::enable_if_t<std::is_same_v<T, FDCore::AbstractResource> ||
                   std::is_same_v<T, FDCore::BaseResource>,
                 rapidjson::Value>
  FDJson::serialize(const T &res, Serializer &serializer)
{
    rapidjson::Value result(serializer.serialize(static_cast<const FDCore::Object &>(res)));
    std::string_view str = res.getResourceName();
    result.AddMember(serializer.serialize("resourceName"),
                     serializer.serialize(str.data(), str.size()), serializer.getAllocator());
    std::string_view path = res.getResourcePath();
    if(!path.empty())
        result.AddMember(serializer.serialize("resourcePath"),
                         serializer.serialize(path.data(), path.size()), serializer.getAllocator());

    return result;
}

template<typename T>
std::enable_if_t<
  std::is_same_v<T, FDCore::AbstractResource> || std::is_same_v<T, FDCore::BaseResource>, bool>
  FDJson::unserialize(const rapidjson::Value &val, T &res, Serializer &serializer, std::string *err)
{
    if(!serializer.unserialize(val, static_cast<FDCore::Object &>(res), err))
        return false;

    if(!val.HasMember("resourceName"))
    {
        if(err)
            *err = "value has no member 'resourceName'";

        return false;
    }

    std::string str;
    if(!serializer.unserialize(val["resourceName"], str, err))
    {
        if(err)
            *err = "error parsing 'resourceName': " + *err;

        return false;
    }

    if(str.empty())
    {
        if(err)
            *err = "attribute 'resourceName' is an empty string";

        return false;
    }

    res.setResourceName(str);

    std::string path;
    if(!val.HasMember("resourcePath") || !serializer.unserialize(val["resourcePath"], path, err) ||
       path.empty())
        return true;

    res.setResourcePath(path);

    return true;
}

#endif // FDCORE_RESOURCE_JSON_H
