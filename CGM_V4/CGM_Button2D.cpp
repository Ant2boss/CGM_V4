#include "CGM_Button2D.h"

CGM::Button::Button() {
    this->MyText.SetFormatMode_TextBreak(true);
    this->MyText.SetFormatMode_CenterTopDown(true);
}

CGM::Button::Button(uint8_t Color) : Button() {
    this->SetColor(Color);
}

CGM::Button::Button(uint8_t SelColor, uint8_t NotSelColor) : Button() {
    this->SetSelectedColor(SelColor);
    this->SetNotSelectedColor(NotSelColor);
}

CGM::Button::Button(uint8_t SelColor, uint8_t NotSelColor, CGM::Reg2i Reg) : Button(SelColor, NotSelColor) {
    this->SetRegion(Reg);
}

CGM::Button::Button(uint8_t SelColor, uint8_t NotSelColor, CGM::Vec2i Pos, CGM::Vec2i Size) : Button(SelColor, NotSelColor) {
    this->SetRegion(CGM::Reg2i(Pos, Size));
}

void CGM::Button::SetSize(int x, int y) {
    this->SetSize(CGM::Vec2i(x, y));
}

void CGM::Button::SetSize(CGM::Vec2i S) {
    this->MyLastRegion = this->MyRegion;
    this->MyRegion.Size = S;
    this->MyText.SetSize(S);
    this->MyRect.SetSize(S);
}

void CGM::Button::SetPosition(int x, int y) {
    this->SetPosition(CGM::Vec2i(x, y));
}

void CGM::Button::SetPosition(CGM::Vec2i P) {
    this->MyLastRegion = this->MyRegion;
    this->MyRegion.Position = P;
    this->MyText.SetPosition(P);
    this->MyRect.SetPosition(P);
}

void CGM::Button::SetRegion(CGM::Reg2i Reg) {
    this->SetSize(Reg.Size);
    this->SetPosition(Reg.Position);
}

void CGM::Button::SetColor(uint8_t Color) {
    this->SetSelectedColor(Color);
    this->SetNotSelectedColor(Color);
}

void CGM::Button::SetSelectedColor(uint8_t Color) {
    this->MyOnColor = Color;
}

void CGM::Button::SetNotSelectedColor(uint8_t Color) {
    this->MyOffColor = Color;
}

void CGM::Button::SetFontColor(uint8_t Color) {
    this->MyText.SetFontColor(Color);
}

void CGM::Button::SetFontFormat_TextBreak(bool Mode) {
    this->MyText.SetFormatMode_TextBreak(Mode);
}

void CGM::Button::SetFontFormat_CenteredTopDown(bool Mode) {
    this->MyText.SetFormatMode_CenterTopDown(Mode);
}

uint8_t CGM::Button::GetFontColor() const {
    return this->MyText.GetFontColor();
}

uint8_t CGM::Button::GetSelectedColor() const {
    return this->MyOnColor;
}

uint8_t CGM::Button::GetNotSelectedColor() const {
    return this->MyOffColor;
}

void CGM::Button::AppendToCanvas(CGM::Canvas2D* Can) {
    if (this->is_hovered())
        this->MyRect.SetColor(this->GetSelectedColor());
    else
        this->MyRect.SetColor(this->GetNotSelectedColor());

    Can->Append(&this->MyRect);
    Can->Append(&this->MyText);
}

void CGM::SaveButtonToFile(std::ofstream& out_file, const CGM::Button* Butt) {
    uint8_t tCol = Butt->GetSelectedColor();
    out_file.write((char*)&tCol, sizeof(uint8_t));
    tCol = Butt->GetNotSelectedColor();
    out_file.write((char*)&tCol, sizeof(uint8_t));

    CGM::SaveEntity2DToFile(out_file, Butt);
    CGM::SaveShapeToFile(out_file, &Butt->MyRect);
    CGM::SaveTextBoxToFile(out_file, &Butt->MyText);
}

void CGM::LoadButtonFromFile(std::ifstream& in_file, CGM::Button* Butt) {
    uint8_t tCol;
    in_file.read((char*)&tCol, sizeof(uint8_t));
    Butt->SetSelectedColor(tCol);
    in_file.read((char*)&tCol, sizeof(uint8_t));
    Butt->SetNotSelectedColor(tCol);

    CGM::LoadEntity2DFromFile(in_file, Butt);
    CGM::LoadShapeFromFile(in_file, &Butt->MyRect);
    CGM::LoadTextBoxFromFile(in_file, &Butt->MyText);
}
