#ifndef FDCORE_OBJECT_JSON_FWD_H
#define FDCORE_OBJECT_JSON_FWD_H

#include <FDCore/Object.h>
#include <FDJson/FDJson.h>
#include <rapidjson/fwd.h>

namespace FDJson
{
    rapidjson::Value serialize(const FDCore::Object &obj, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FDCore::Object &obj, Serializer &serializer,
                     std::string *err = nullptr);
} // namespace FDJson

#endif // FDCORE_OBJECT_JSON_FWD_H
