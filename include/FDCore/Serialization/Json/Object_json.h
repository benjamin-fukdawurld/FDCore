#ifndef FDCORE_OBJECT_JSON_H
#define FDCORE_OBJECT_JSON_H

#include <FDJson/JsonSerializer.h>

#include <FDCore/Object.h>

namespace FDJson
{
    FD_INLINE rapidjson::Value serialize(const FDCore::Object &obj, FDJson::Serializer &serializer)
    {
        rapidjson::Value result(rapidjson::kObjectType);

        result.AddMember(serializer.serialize("type"),
                         serializer.serialize(obj.getTypeCode()),
                         serializer.getAllocator());

        return result;
    }

    FD_INLINE bool unserialize(const rapidjson::Value &val, FDCore::Object &, FDJson::Serializer &, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "value is not an object";

            return false;
        }

        if(!val.HasMember("type"))
        {
            if(err)
                *err = "value has no member 'type'";

            return false;
        }

        if(!val["type"].IsString())
        {
            if(err)
                *err = "attribute 'type' is not a string";

            return false;
        }

        if(val["type"].GetStringLength() == 0)
        {
            if(err)
                *err = "attribute 'type' is an empty string";

            return false;
        }


        return true;
    }
}

#endif // FDCORE_OBJECT_JSON_H
