#ifndef FDCORE_OBJECT_JSON_FWD_H
#define FDCORE_OBJECT_JSON_FWD_H

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

#include <FDCore/Object.h>

namespace FDJson
{
    rapidjson::Value serialize(const FDCore::Object &obj, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, FDCore::Object &obj, Serializer &serializer, std::string *err = nullptr);
}

#endif // FDCORE_OBJECT_JSON_FWD_H
