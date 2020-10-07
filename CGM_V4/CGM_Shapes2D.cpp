#include "CGM_Shapes2D.h"

#include <cmath>

void CGM::BaseShape::SetColor(uint8_t Color) {
    this->MyColor = Color;
}

void CGM::BaseShape::SetFillMode(bool Mode) {
    this->MyFillMode = Mode;
}

uint8_t CGM::BaseShape::GetColor() const {
    return this->MyColor;
}

bool CGM::BaseShape::GetFillMode() const {
    return this->MyFillMode;
}

CGM::RectangleShape::RectangleShape(uint8_t Color) {
    this->SetColor(Color);
}

CGM::RectangleShape::RectangleShape(uint8_t Color, CGM::Vec2i Pos, CGM::Vec2i Size)
    : RectangleShape(Color) {
    this->SetPosition(Pos);
    this->SetSize(Size);
}

void CGM::RectangleShape::AppendToCanvas(CGM::Canvas2D* Can) {

    uint8_t MyColor = this->GetColor() * 16 + this->GetColor();

    for (int y = 0; y < this->GetSize().y; ++y) {
        for (int x = 0; x < this->GetSize().x; ++x) {
            if (this->GetFillMode()) {
                if (!Can->GetRegion().is_over_a_vector(CGM::Vec2i(x, y) + this->GetPosition())) continue;

                Can->SetColorAt(MyColor, CGM::Vec2i(x, y) + this->GetPosition());
            }
            else {
                if (x == 0 || y == 0 || x == this->GetSize().x - 1 || y == this->GetSize().y - 1) {
                    if (!Can->GetRegion().is_over_a_vector(CGM::Vec2i(x, y) + this->GetPosition())) continue;
                    Can->SetColorAt(MyColor, CGM::Vec2i(x, y) + this->GetPosition());
                }
            }
        }
    }

}

CGM::ElipseShape::ElipseShape(uint8_t Color) {
    this->SetColor(Color);
}

CGM::ElipseShape::ElipseShape(uint8_t Color, CGM::Vec2i Pos, CGM::Vec2i Size) 
    : ElipseShape(Color) {
    this->SetPosition(Pos);
    this->SetSize(Size);
}

void CGM::ElipseShape::AppendToCanvas(CGM::Canvas2D* Can) {

    double el_a = (this->GetSize().x / 2.0) - 1;
    double el_b = (this->GetSize().y / 2.0) - 1;

    uint8_t MyCol = this->GetColor() * 16 + this->GetColor();
    CGM::Vec2i Offset = (this->GetPosition() + (this->GetSize() / 2));

    for (int x = -el_a; x <= +el_a; ++x) {
        
        double y0 = std::sqrt(std::pow(el_b, 2) - ((std::pow(el_b, 2) * std::pow(x, 2)) / std::pow(el_a, 2)));
        double y1 = -std::sqrt(std::pow(el_b, 2) - ((std::pow(el_b, 2) * std::pow(x, 2)) / std::pow(el_a, 2)));

        if(Can->GetRegion().is_over_a_vector(Offset + CGM::Vec2i(x, std::round(y0))))
            Can->SetColorAt(MyCol, Offset.x + x, Offset.y + std::round(y0));

        if(Can->GetRegion().is_over_a_vector(Offset + CGM::Vec2i(x, std::round(y1))))
            Can->SetColorAt(MyCol, Offset.x + x, Offset.y + std::round(y1));

        if (this->GetFillMode()) {
            for (int y = std::round(y1); y <= std::round(y0); ++y)
                if (Can->GetRegion().is_over_a_vector(Offset + CGM::Vec2i(x, y)))
                    Can->SetColorAt(MyCol, Offset.x + x, Offset.y + y);
        }

    }

    for (int y = -el_b; y <= +el_b; ++y) {

        double x0 = std::sqrt(std::pow(el_a, 2) - ((std::pow(el_a, 2) * std::pow(y, 2)) / std::pow(el_b, 2)));
        double x1 = -std::sqrt(std::pow(el_a, 2) - ((std::pow(el_a, 2) * std::pow(y, 2)) / std::pow(el_b, 2)));

        if (Can->GetRegion().is_over_a_vector(Offset + CGM::Vec2i(std::round(x0), y)))
            Can->SetColorAt(MyCol, Offset.x + std::round(x0), Offset.y + y);
        if (Can->GetRegion().is_over_a_vector(Offset + CGM::Vec2i(std::round(x1), y)))
            Can->SetColorAt(MyCol, Offset.x + std::round(x1), Offset.y + y);

    }
}

void CGM::SaveShapeToFile(std::ofstream& out_file, const CGM::BaseShape* Shape) {
    bool tFill = Shape->GetFillMode();
    uint8_t tCol = Shape->GetColor();
    CGM::Reg2i tReg = Shape->GetRegion();

    out_file.write((char*)&tFill, sizeof(bool));
    out_file.write((char*)&tCol, sizeof(uint8_t));
    out_file.write((char*)&tReg, sizeof(CGM::Reg2i));
}

void CGM::LoadShapeFromFile(std::ifstream& in_file, CGM::BaseShape* Shape) {
    bool tFill;
    uint8_t tCol;
    CGM::Reg2i tReg;

    in_file.read((char*)&tFill, sizeof(bool));
    in_file.read((char*)&tCol, sizeof(uint8_t));
    in_file.read((char*)&tReg, sizeof(CGM::Reg2i));

    Shape->SetFillMode(tFill);
    Shape->SetColor(tCol);
    Shape->SetPosition(tReg.Position);
    Shape->SetSize(tReg.Size);
}
