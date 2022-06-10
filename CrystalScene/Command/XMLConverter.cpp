#include "XMLConverter.h"
#include "Crystal/Math/Vector3d.h"
#include "Crystal/Math/Box3d.h"
#include <cassert>

using namespace Crystal::Math;
using namespace Crystal::Command;

template<>
tinyxml2::XMLElement* XMLConverter::toXML<bool>(tinyxml2::XMLDocument* doc, const std::string& name, const bool value)
{
    auto elem = doc->NewElement(name.c_str());
    auto text = doc->NewText(std::to_string(value).c_str());
    elem->InsertEndChild(text);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<int>(tinyxml2::XMLDocument* doc, const std::string& name, const int value)
{
    auto elem = doc->NewElement(name.c_str());
    auto text = doc->NewText(std::to_string(value).c_str());
    elem->InsertEndChild(text);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<float>(tinyxml2::XMLDocument* doc, const std::string& name, const float value)
{
    auto elem = doc->NewElement(name.c_str());
    auto text = doc->NewText(std::to_string(value).c_str());
    elem->InsertEndChild(text);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<double>(tinyxml2::XMLDocument* doc, const std::string& name, const double value)
{
    auto elem = doc->NewElement(name.c_str());
    auto text = doc->NewText(std::to_string(value).c_str());
    elem->InsertEndChild(text);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<std::string>(tinyxml2::XMLDocument* doc, const std::string& name, const std::string value)
{
    auto elem = doc->NewElement(name.c_str());
    auto text = doc->NewText(value.c_str());
    elem->InsertEndChild(text);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<Vector3df>(tinyxml2::XMLDocument* doc, const std::string& name, const Vector3df value)
{
    auto elem = doc->NewElement(name.c_str());
    auto x = toXML(doc, "x", value.x);
    auto y = toXML(doc, "y", value.y);
    auto z = toXML(doc, "z", value.z);
    elem->InsertEndChild(x);
    elem->InsertEndChild(y);
    elem->InsertEndChild(z);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<Vector3dd>(tinyxml2::XMLDocument* doc, const std::string& name, const Vector3dd value)
{
    auto elem = doc->NewElement(name.c_str());
    auto x = toXML(doc, "x", value.x);
    auto y = toXML(doc, "y", value.y);
    auto z = toXML(doc, "z", value.z);
    elem->InsertEndChild(x);
    elem->InsertEndChild(y);
    elem->InsertEndChild(z);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<Box3dd>(tinyxml2::XMLDocument* doc, const std::string& name, const Box3dd value)
{
    auto elem = doc->NewElement(name.c_str());
    auto min = toXML(doc, "min", value.getMin());
    auto max = toXML(doc, "max", value.getMax());
    elem->InsertEndChild(min);
    elem->InsertEndChild(max);
    return elem;
}

template<>
tinyxml2::XMLElement* XMLConverter::toXML<Box3df>(tinyxml2::XMLDocument* doc, const std::string& name, const Box3df value)
{
    auto elem = doc->NewElement(name.c_str());
    auto min = toXML(doc, "min", value.getMin());
    auto max = toXML(doc, "max", value.getMax());
    elem->InsertEndChild(min);
    elem->InsertEndChild(max);
    return elem;
}

tinyxml2::XMLElement* XMLConverter::toXML(tinyxml2::XMLDocument* doc, const std::string& name, const std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(bool)) {
        const auto v = std::any_cast<bool>(value);
        return toXML<bool>(doc, name, v);
    }
    if (type == typeid(int)) {
        const auto v = std::any_cast<int>(value);
        return toXML<int>(doc, name, v);
    }
    if (type == typeid(float)) {
        const auto v = std::any_cast<float>(value);
        return toXML<float>(doc, name , v);
    }
    if (type == typeid(double)) {
        const auto v = std::any_cast<double>(value);
        return toXML<double>(doc, name, v );
    }
    if (type == typeid(std::string)) {
        const auto v = std::any_cast<std::string>(value);
        return toXML<std::string>(doc, name, v);
    }
    if (type == typeid(Vector3df)) {
        const auto v = std::any_cast<Vector3df>(value);
        return toXML<Vector3df>(doc, name, v);
    }
    if (type == typeid(Vector3dd)) {
        const auto v = std::any_cast<Vector3dd>(value);
        return toXML<Vector3dd>(doc, name, v);
    }
    if (type == typeid(Box3df)) {
        const auto v = std::any_cast<Box3df>(value);
        return toXML<Box3df>(doc, name, v);
    }
    if (type == typeid(Math::Box3dd)) {
        const auto v = std::any_cast<Math::Box3dd>(value);
        return toXML<Box3dd>(doc, name, v);
    }

    /*
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
    if (type == typeid(std::vector<Math::Vector3dd>)) {
        return std::any_cast<std::vector<Math::Vector3dd>>(value);
    }
    if (type == typeid(Graphics::ColorRGBAf)) {
        return std::any_cast<Graphics::ColorRGBAf>(value);
    }
    */
    assert(false);
    return {};
}

tinyxml2::XMLElement* XMLConverter::toXML(tinyxml2::XMLDocument* doc,  const PropertyTree& args)
{
    auto elem = doc->NewElement(args.getName().c_str());

    const auto attrs = args.getAttributes();
    for (auto a : attrs) {
        elem->SetAttribute(a->name.c_str(), std::any_cast<std::string>(a->value).c_str());
    }

    const auto values = args.getValues();
    for (auto v : values) {
        auto e = toXML(doc, v->name, v->value);
        elem->InsertEndChild(e);
    }

    const auto children = args.getChildren();
    for (auto c : children) {
        auto e = toXML(doc, *c);
        elem->InsertEndChild(e);
    }
    return elem;
}

template<>
void XMLConverter::fromXML<int>(const tinyxml2::XMLElement& parent, const std::string& name, int& value)
{
    value = parent.FirstChildElement(name.c_str())->IntText();
}

template<>
void XMLConverter::fromXML<float>(const tinyxml2::XMLElement& parent, const std::string& name, float& value)
{
    value = parent.FirstChildElement(name.c_str())->FloatText();
}

template<>
void XMLConverter::fromXML<double>(const tinyxml2::XMLElement& parent, const std::string& name, double& value)
{
    value = parent.FirstChildElement(name.c_str())->DoubleText();
}

template<>
int XMLConverter::fromXML<int>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    return parent.FirstChildElement(name.c_str())->IntText();
}

template<>
float XMLConverter::fromXML<float>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    return parent.FirstChildElement(name.c_str())->FloatText();
}

template<>
double XMLConverter::fromXML<double>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    return parent.FirstChildElement(name.c_str())->DoubleText();
}

template<>
std::string XMLConverter::fromXML<std::string>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    return parent.FirstChildElement(name.c_str())->GetText();
}

template<>
Vector3df XMLConverter::fromXML<Vector3df>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    const auto e = parent.FirstChildElement(name.c_str());
    const auto x = fromXML<float>(*e, "x");
    const auto y = fromXML<float>(*e, "y");
    const auto z = fromXML<float>(*e, "z");
    return Vector3dd(x, y, z);
}

template<>
Vector3dd XMLConverter::fromXML<Vector3dd>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    const auto e = parent.FirstChildElement(name.c_str());
    const auto x = fromXML<double>(*e, "x");
    const auto y = fromXML<double>(*e, "y");
    const auto z = fromXML<double>(*e, "z");
    return Vector3dd(x, y, z);
}

template<>
Box3df XMLConverter::fromXML<Box3df>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    auto e = parent.FirstChildElement(name.c_str());
    auto min = fromXML<Vector3df>(*e, "min");
    auto max = fromXML<Vector3df>(*e, "max");
    return Box3df(min, max);
}

template<>
Box3dd XMLConverter::fromXML<Box3dd>(const tinyxml2::XMLElement& parent, const std::string& name)
{
    auto e = parent.FirstChildElement(name.c_str());
    auto min = fromXML<Vector3dd>(*e, "min");
    auto max = fromXML<Vector3dd>(*e, "max");
    return Box3dd(min, max);
}

void XMLConverter::fromXML(const tinyxml2::XMLElement& text, std::any& value)
{
    const auto& type = value.type();
    if (type == typeid(int)) {
        const int v = text.IntText();
        value = v;
    }
    else if (type == typeid(bool)) {
        const bool v = text.BoolText();
        value = v;
    }
    else if (type == typeid(float)) {
        const float v = text.FloatText();
        value = v;
    }
    else if (type == typeid(double)) {
        const double v = text.DoubleText();
        value = v;
    }
    else if (type == typeid(std::string)) {
        const std::string v = text.GetText();
        value = v;
    }
    else {
        assert(false);
    }
}

#include <iostream>

bool XMLConverter::fromXML(const tinyxml2::XMLElement& parent, PropertyTree& tree)
{
    const auto values = tree.getValues();
    for (auto v : values) {
        auto e = parent.FirstChildElement(v->name.c_str());
        fromXML(*e, v->value);
    }
    return true;
}
