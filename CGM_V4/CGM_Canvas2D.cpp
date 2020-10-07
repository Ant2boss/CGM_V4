#include "CGM_Canvas2D.h"

CGM::Canvas2D::Canvas2D(size_t x, size_t y) {
    this->MySize = CGM::Vec2i(x, y);
    this->MyCharInfoArray.resize(y * x);

    this->MyInput = GetStdHandle(STD_INPUT_HANDLE);
    this->MyOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    this->MyBuffSize.X = x;
    this->MyBuffSize.Y = y;
    this->MyBuffCoord.X = 0;
    this->MyBuffCoord.Y = 0;

    this->MySR.Left = 0;
    this->MySR.Top = 0;
    this->MySR.Right = x;
    this->MySR.Bottom = y;

    this->MyCSBI.cbSize = sizeof(this->MyCSBI);
    GetConsoleScreenBufferInfoEx(this->MyOutput, &this->MyCSBI);
    this->MyBackupCSBI = this->MyCSBI;

    this->MyCSBI.dwSize.X = x;
    this->MyCSBI.dwSize.Y = y;

    this->MyCSBI.srWindow.Right = x * 8;
    this->MyCSBI.srWindow.Bottom = y * 16;

    this->MyCSBI.bFullscreenSupported = false;

    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Black]        = RGB(0, 0, 0);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Gray]         = RGB(128, 128, 128);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::White]        = RGB(255, 255, 255);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Red]          = RGB(255, 0, 0);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::DarkRed]      = RGB(128, 0, 0);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Cyan]         = RGB(0, 255, 255);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Blue]         = RGB(0, 0, 255);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::DarkBlue]     = RGB(0, 0, 128);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Green]        = RGB(0, 255, 0);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::DarkGreen]    = RGB(0, 128, 0);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Magenta]      = RGB(255, 0, 255);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Indigo]       = RGB(75, 0, 130);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Brown]        = RGB(160, 82, 45);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Bisque]       = RGB(255, 228, 196);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Yellow]       = RGB(255, 255, 0);
    this->MyCSBI.ColorTable[CGM::Canvas2D::Color::Orange]       = RGB(255, 165, 0);

    SetConsoleScreenBufferInfoEx(this->MyOutput, &this->MyCSBI);

}

CGM::Canvas2D::~Canvas2D() {
    SetConsoleScreenBufferInfoEx(this->MyOutput, &this->MyBackupCSBI);
}

void CGM::Canvas2D::SetCharAt(char C, int x, int y) {
    this->SetCharAt(C, Vec2i(x, y));
}

void CGM::Canvas2D::SetCharAt(char C, CGM::Vec2i V) {
    this->MyCharInfoArray[this->index_of(V)].Char.UnicodeChar = C;
}

void CGM::Canvas2D::SetColorAt(uint8_t Color, int x, int y) {
    this->SetColorAt(Color, CGM::Vec2i(x, y));
}

void CGM::Canvas2D::SetColorAt(uint8_t Color, CGM::Vec2i V) {
    this->MyCharInfoArray[this->index_of(V)].Attributes = Color;
}

void CGM::Canvas2D::SetFontColorAt(uint8_t Color, int x, int y) {
    this->SetFontColorAt(Color, CGM::Vec2i(x, y));
}

void CGM::Canvas2D::SetFontColorAt(uint8_t Color, CGM::Vec2i V) {
    uint8_t curr_back_color = this->GetColorAt(V) / 16;
    this->SetColorAt(curr_back_color * 16 + Color, V);
}

void CGM::Canvas2D::SetBackColorAt(uint8_t Color, int x, int y) {
    this->SetBackColorAt(Color, CGM::Vec2i(x, y));
}

void CGM::Canvas2D::SetBackColorAt(uint8_t Color, CGM::Vec2i V) {
    uint8_t curr_font_color = this->GetColorAt(V) % 16;
    this->SetColorAt(Color * 16 + curr_font_color, V);
}

char CGM::Canvas2D::GetCharAt(int x, int y) const {
    return this->GetCharAt(CGM::Vec2i(x, y));
}

char CGM::Canvas2D::GetCharAt(CGM::Vec2i V) const {
    return this->MyCharInfoArray[this->index_of(V)].Char.UnicodeChar;
}

uint8_t CGM::Canvas2D::GetColorAt(int x, int y) const {
    return this->GetColorAt(CGM::Vec2i(x, y));
}

uint8_t CGM::Canvas2D::GetColorAt(CGM::Vec2i V) const {
    return this->MyCharInfoArray[this->index_of(V)].Attributes;
}

CGM::Vec2i CGM::Canvas2D::GetSize() const {
    return this->MySize;
}

CGM::Reg2i CGM::Canvas2D::GetRegion() const {
    return CGM::Reg2i(CGM::Vec2i(0, 0), this->GetSize());
}

CGM::Vec2i CGM::Canvas2D::GetMousePos() const {
    POINT p;
    
    GetCursorPos(&p);
    ScreenToClient(GetConsoleWindow(), &p);

    return CGM::Vec2i(p.x / 8, p.y / 16);
}

void CGM::Canvas2D::AppendLine(uint8_t Color, CGM::Vec2i Start, CGM::Vec2i End) {
    CGM::Vec2i reg_start = Start.get_smallest_vector(End);
    CGM::Vec2i reg_end = Start.get_largest_vector(End);

    double x1 = Start.x;
    double y1 = Start.y;
    double x2 = End.x;
    double y2 = End.y;

    uint8_t MyCol = Color * 16 + Color;

    if (x2 - x1 == 0) {
        for (int y = reg_start.y; y <= reg_end.y; ++y) {
            CGM::Vec2i Final(x1, y);
            if (this->GetRegion().is_over_a_vector(Final))
                this->SetColorAt(MyCol, Final);
        }
        return;
    }
    double k = (y2 - y1) / (x2 - x1);

    for (int x = reg_start.x; x <= reg_end.x; ++x) {
        double t_y = k * (x - x1) + y1;

        CGM::Vec2i Final = CGM::Vec2i(x, std::round(t_y));
        if (this->GetRegion().is_over_a_vector(Final))
            this->SetColorAt(MyCol, Final);
    }

    for (int y = reg_start.y; y <= reg_end.y; ++y) {
        double t_x = (y - y1) / k + x1;

        CGM::Vec2i Final = CGM::Vec2i(std::round(t_x), y);
        if (this->GetRegion().is_over_a_vector(Final))
            this->SetColorAt(MyCol, Final);
    }
}

void CGM::Canvas2D::AppendLine(uint8_t Color, int xStart, int yStart, int xEnd, int yEnd) {
    this->AppendLine(Color, CGM::Vec2i(xStart, yStart), CGM::Vec2i(xEnd, yEnd));
}

void CGM::Canvas2D::Clear(uint8_t ClearColor, char ClearChar) {
    for (auto& el : this->MyCharInfoArray) {
        el.Attributes = ClearColor;
        el.Char.UnicodeChar = ClearChar;
    }
}

void CGM::Canvas2D::Draw() {
    SMALL_RECT tSR = this->MySR;
    WriteConsoleOutput(this->MyOutput, &this->MyCharInfoArray[0], this->MyBuffSize, this->MyBuffCoord, &tSR);
}

int CGM::Canvas2D::index_of(CGM::Vec2i V) const {
#ifdef _DEBUG
    if (V.x < 0 || V.x >= this->GetSize().x || V.y < 0 || V.y >= this->GetSize().y) DebugBreak();
#endif
    return V.y * this->GetSize().x + V.x;
}

int CGM::Canvas2D::index_of(int x, int y) const {
    return this->index_of(CGM::Vec2i(x, y));
}

void CGM::AppendMessageToCanvas(CGM::Canvas2D* Can, const char* Message, uint8_t Color, int x, int y) {
    CGM::AppendMessageToCanvas(Can, Message, Color, CGM::Vec2i(x, y));
}

void CGM::AppendMessageToCanvas(CGM::Canvas2D* Can, const char* Message, uint8_t Color, CGM::Vec2i P) {
    if (Message == nullptr)
        return;
    
    unsigned int curr_index = 0;
    while (Message[curr_index] != 0) {
        if (P.x >= Can->GetSize().x) {
            P.x = 0;
            ++P.y;
        }
        if (P.y >= Can->GetSize().y) {
            P.x = 0;
            P.y = 0;
        }

        Can->SetCharAt(Message[curr_index++], P);
        Can->SetFontColorAt(Color, P);
        ++P.x;

        if (curr_index >= 256)
            throw "Message size is too large!";
    }
}
