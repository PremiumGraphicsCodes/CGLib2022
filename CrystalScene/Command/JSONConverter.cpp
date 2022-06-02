#include "JSONConverter.h"

#include "../ThirdParty/nlohmnn/json.hpp"

#include "Crystal/Math/Vector3d.h"
#include "Crystal/Graphics/ColorRGBA.h"

using namespace Crystal;
using namespace Crystal::Command;
using namespace nlohmann;

namespace glm {
    void to_json(json& j, const Math::Vector2df& p) {
        j = json{ {"x", p.x}, {"y", p.y} };
    }

    void from_json(const json& j, Math::Vector2df& p) {
        p.x = j.at("x").get<float>();
        p.y = j.at("y").get<float>();
    }

    void to_json(json& j, const Math::Vector2dd& p) {
        j = json{ {"x", p.x}, {"y", p.y} };
    }

    void from_json(const json& j, Math::Vector2dd& p) {
        p.x = j.at("x").get<double>();
        p.y = j.at("y").get<double>();
    }

    void to_json(json& j, const Math::Vector3df& p) {
        j = json{ {"x", p.x}, {"y", p.y}, {"z", p.z} };
    }

    void from_json(const json& j, Math::Vector3df& p) {
        p.x = j.at("x").get<float>();       // get_to(T& arg) ‚Í arg = get<T>() ‚Æ“¯‚¶
        p.y = j.at("y").get<float>();
        p.z = j.at("z").get<float>();
    }

    void to_json(json& j, const Math::Vector3dd& p) {
        j = json{ {"x", p.x}, {"y", p.y}, {"z", p.z} };
    }

    void from_json(const json& j, Math::Vector3dd& p) {
        p.x = j.at("x").get<double>();       // get_to(T& arg) ‚Í arg = get<T>() ‚Æ“¯‚¶
        p.y = j.at("y").get<double>();
        p.z = j.at("z").get<double>();
    }

    void to_json(json& j, const Graphics::ColorRGBAf& p) {
        j = json{ {"r", p.r}, {"g", p.g}, {"b", p.b}, {"a", p.a} };
    }

    void from_json(const json& j, Graphics::ColorRGBAf& c) {
        c.r = j.at("r").get<float>();
        c.g = j.at("g").get<float>();
        c.b = j.at("b").get<float>();
        c.a = j.at("a").get<float>();
    }

} // namespace ns

json JSONConverter::toJSON(const std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(bool)) {
        return std::any_cast<bool>(value);
    }
    if (type == typeid(int)) {
        return std::any_cast<int>(value);
    }
    if (type == typeid(float)) {
        return std::any_cast<float>(value);
    }
    if (type == typeid(double)) {
        return std::any_cast<double>(value);
    }
    if (type == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }
    if (type == typeid(std::vector<int>)) {
        return std::any_cast<std::vector<int>>(value);
    }
    if (type == typeid(Math::Vector2df)) {
        return std::any_cast<Math::Vector2df>(value);
    }
    if (type == typeid(std::vector<Math::Vector2df>)) {
        return std::any_cast<std::vector<Math::Vector2df>>(value);
    }
    if (type == typeid(Math::Vector2dd)) {
        return std::any_cast<Math::Vector2dd>(value);
    }
    if (type == typeid(std::vector<Math::Vector2dd>)) {
        return std::any_cast<std::vector<Math::Vector2dd>>(value);
    }
    if (type == typeid(Math::Vector3df)) {
        return std::any_cast<Math::Vector3df>(value);
    }
    if (type == typeid(Math::Vector3dd)) {
        return std::any_cast<Math::Vector3dd>(value);
    }
    if (type == typeid(std::vector<Math::Vector3dd>)) {
        return std::any_cast<std::vector<Math::Vector3dd>>(value);
    }
    if (type == typeid(Graphics::ColorRGBAf)) {
        return std::any_cast<Graphics::ColorRGBAf>(value);
    }
    assert(false);
    return {};
}

json JSONConverter::toJSON(const IArgs& args)
{
    json j;
    for (auto a : args.args) {
        j[a->name] = toJSON(a->value);
    }
    return j;
}

json JSONConverter::toJSON(const ICommand& command)
{
    json j;
    j["name"] = command.getCommandName();
    j["args"] = toJSON(*command.getArgs());
    return j;
}

void JSONConverter::fromJSON(const nlohmann::json& json, std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(int)) {
        const int v = json;
        value = v;
    }
    else if (type == typeid(bool)) {
        const bool v = json;
        value = v;
    }
    else if (type == typeid(float)) {
        const float v = json;
        value = v;
    }
    else if (type == typeid(double)) {
        const double v = json;
        value = v;
    }
    else if (type == typeid(std::string)) {
        const std::string v = json;
        value = v;
    }
    else if (type == typeid(std::vector<int>)) {
        const std::vector<int> v = json;
        value = v;
    }
    else if (type == typeid(Math::Vector2df)) {
        const Math::Vector2df v = json;
        value = v;
    }
    else if (type == typeid(Math::Vector2dd)) {
        const Math::Vector2dd v = json;
        value = v;
    }
    else if (type == typeid(std::vector<Math::Vector2dd>)) {
        const std::vector<Math::Vector2dd> v = json;
        value = v;
    }
    else if (type == typeid(Math::Vector3df)) {
        const Math::Vector3df v = json;
        value = v;
    }
    else if (type == typeid(Math::Vector3dd)) {
        const Math::Vector3dd v = json;
        value = v;
    }
    else if (type == typeid(std::vector<Math::Vector3dd>)) {
        const std::vector<Math::Vector3dd> v = json;
        value = v;
    }
    else if (type == typeid(Graphics::ColorRGBAf)) {
        const Graphics::ColorRGBAf v = json;
        value = v;
    }
    else {
        assert(false);
    }
}

void JSONConverter::fromJSON(const nlohmann::json& json, Arg<int>& dest)
{
    fromJSON(json, dest.value);
}

void JSONConverter::fromJSON(const nlohmann::json& json, ICommand& command)
{
    auto args = command.getArgs();
    // const auto jj = json["args"];
    for (auto a : args->args) {
        auto j = json[a->name];
        /*
        auto& type = a->value.type();
        if (type == typeid(int)) {
            return;
        }
        */
//        command.getArgType(a->name);
        fromJSON(j, a->value);
    }
}


//JSONConverter::
