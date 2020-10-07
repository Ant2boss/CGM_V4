#pragma once

#include "CGM_Vector2D.h"
#include "CGM_Region2D.h"
#include "CGM_Canvas2D.h"

#include <iostream>
#include <string>
#include <sstream>

//Overload cout to enable Vector logging
template<typename T>
std::string vec_to_string(CGM::Vector2D<T> Vec);

template<typename T>
std::ostream& operator<<(std::ostream& os, const CGM::Vector2D<T> Vec);

//Overload cout to enable Region logging
template<typename T>
std::string reg_to_string(CGM::Region2D<T> Reg);

template<typename T>
std::ostream& operator<<(std::ostream& os, const CGM::Region2D<T> Reg);

//Overload cout to enable Entity logging
template<typename T>
std::string ent_to_string(const CGM::Entity2D<T>* Ent);

template<typename T>
std::ostream& operator<<(std::ostream& os, const CGM::Entity2D<T>* Ent);

////////////////////////////////////////////////////////////////////////////

template<typename T>
inline std::string vec_to_string(CGM::Vector2D<T> Vec) {
    std::stringstream ss;
    ss << "[ <Vec2> (" << Vec.x << ", " << Vec.y << ") ]";
    return ss.str();
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CGM::Vector2D<T> Vec) {
    return os << vec_to_string(Vec);
}

template<typename T>
inline std::string reg_to_string(CGM::Region2D<T> Reg) {
    std::stringstream ss;
    ss << "[ <Reg2> P(" << Reg.Position.x << ", " << Reg.Position.y << "), S(" << Reg.Size.x << ", " << Reg.Size.y << ") ]";
    return ss.str();
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CGM::Region2D<T> Reg) {
    return os << reg_to_string(Reg);
}

template<typename T>
inline std::string ent_to_string(const CGM::Entity2D<T>* Ent) {
    std::stringstream ss;
    ss << "[ <Ent2> ID: " << Ent->GetID() << " | " << reg_to_string(Ent->GetRegion()) << " ]";
    return ss.str();
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const CGM::Entity2D<T>* Ent) {
    return os << ent_to_string(Ent);
}
