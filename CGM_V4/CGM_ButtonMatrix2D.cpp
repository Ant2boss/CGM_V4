#include "CGM_ButtonMatrix2D.h"

CGM::ButtonMatrix::ButtonMatrix(CGM::Vec2i init_mat_size) 
    : ButtonMatrix(init_mat_size.x, init_mat_size.y) {}

CGM::ButtonMatrix::ButtonMatrix(int x_mat_size, int y_mat_size) {
    this->AddRow(y_mat_size);
    this->AddColumn(x_mat_size);
}

void CGM::ButtonMatrix::SetMatrixElementSize(int x, int y) {
    this->SetMatrixElementSize(CGM::Vec2i(x, y));
}

void CGM::ButtonMatrix::SetMatrixElementSize(CGM::Vec2i S) {
    this->MyElementSize = S;
    this->update_matrix_elements();
}

void CGM::ButtonMatrix::SetMatrixColor(uint8_t Color) {
    this->SetMatrixSelectedColor(Color);
    this->SetMatrixNotSelectedColor(Color);
}

void CGM::ButtonMatrix::SetMatrixSelectedColor(uint8_t Color) {
    this->MySelectedColor = Color;
    this->apply_matrix_coloring();
}

void CGM::ButtonMatrix::SetMatrixNotSelectedColor(uint8_t Color) {
    this->MyNotSelectedColor = Color;
    this->apply_matrix_coloring();
}

void CGM::ButtonMatrix::SetElementColor(uint8_t Color, uint32_t el_index) {
    this->GetElement(el_index).SetColor(Color);
}

void CGM::ButtonMatrix::SetElementColor(uint8_t Color, CGM::Vec2i index) {
    this->GetElement(index).SetColor(Color);
}

void CGM::ButtonMatrix::SetElementColor(uint8_t Color, uint32_t x_index, uint32_t y_index) {
    this->GetElement(x_index, y_index).SetColor(Color);
}

void CGM::ButtonMatrix::SetElementSelectedColor(uint8_t Color, uint32_t el_index) {
    this->GetElement(el_index).SetSelectedColor(Color);
}

void CGM::ButtonMatrix::SetElementSelectedColor(uint8_t Color, CGM::Vec2i index) {
    this->GetElement(index).SetSelectedColor(Color);
}

void CGM::ButtonMatrix::SetElementSelectedColor(uint8_t Color, uint32_t x_index, uint32_t y_index) {
    this->GetElement(x_index, y_index).SetSelectedColor(Color);
}

void CGM::ButtonMatrix::SetElementNotSelectedColor(uint8_t Color, uint32_t el_index) {
    this->GetElement(el_index).SetNotSelectedColor(Color);
}

void CGM::ButtonMatrix::SetElementNotSelectedColor(uint8_t Color, CGM::Vec2i index) {
    this->GetElement(index).SetNotSelectedColor(Color);
}

void CGM::ButtonMatrix::SetElementNotSelectedColor(uint8_t Color, uint32_t x_index, uint32_t y_index) {
    this->GetElement(x_index, y_index).SetNotSelectedColor(Color);
}

void CGM::ButtonMatrix::SetSpaceBetweenElements(uint32_t dist) {
    this->MySpaceBetweenElemenets = dist;
    this->update_matrix_elements();
}

CGM::Button& CGM::ButtonMatrix::operator[] (uint32_t index) {
    return this->GetElement(index);
}

CGM::Button& CGM::ButtonMatrix::operator[](CGM::Vec2i index) {
    return this->GetElement(index);
}

CGM::Button& CGM::ButtonMatrix::GetElement(uint32_t index) {
#ifdef _DEBUG
    if (index >= this->GetMatrixIndexCount()) DebugBreak();
#endif
    return this->MyButtonArray[index];
}

CGM::Button& CGM::ButtonMatrix::GetElement(CGM::Vec2i index) {
    return this->GetElement(index.y * this->GetMatrixSize().x + index.x);
}

CGM::Button& CGM::ButtonMatrix::GetElement(uint32_t x, uint32_t y) {
    return this->GetElement(y * this->GetMatrixSize().x + x);
}

uint32_t CGM::ButtonMatrix::GetMatrixIndexCount() const {
    return this->MyMatSize.x * this->MyMatSize.y;
}

uint32_t CGM::ButtonMatrix::GetSpaceBetweenElements() const {
    return this->MySpaceBetweenElemenets;
}

CGM::Vec2i CGM::ButtonMatrix::GetMatrixSize() const {
    return this->MyMatSize;
}

CGM::Vec2i CGM::ButtonMatrix::GetMatrixElementSize() const {
    return this->MyElementSize;
}

uint8_t CGM::ButtonMatrix::GetMatrixSelectedColor() const {
    return this->MySelectedColor;
}

uint8_t CGM::ButtonMatrix::GetMatrixNotSelectedColor() const {
    return this->MyNotSelectedColor;
}

uint8_t CGM::ButtonMatrix::GetElementSelectedColor(uint32_t el_index) const {
    return this->MyButtonArray[this->index_of(el_index)].GetSelectedColor();
}

uint8_t CGM::ButtonMatrix::GetElementSelectedColor(CGM::Vec2i index) const {
    return this->GetElementSelectedColor(this->index_of(index));
}

uint8_t CGM::ButtonMatrix::GetElementSelectedColor(uint32_t x_index, uint32_t y_index) const {
    return this->GetElementSelectedColor(this->index_of(x_index, y_index));
}

uint8_t CGM::ButtonMatrix::GetElementNotSelectedColor(uint32_t el_index) const {
    return this->MyButtonArray[this->index_of(el_index)].GetNotSelectedColor();
}

uint8_t CGM::ButtonMatrix::GetElementNotSelectedColor(CGM::Vec2i index) const {
    return this->GetElementNotSelectedColor(this->index_of(index));
}

uint8_t CGM::ButtonMatrix::GetElementNotSelectedColor(uint32_t x_index, uint32_t y_index) const {
    return this->GetElementNotSelectedColor(this->index_of(x_index, y_index));
}

void CGM::ButtonMatrix::AddRow(uint32_t RowCount) {
    this->MyMatSize.y += RowCount;
    this->resize_array();
    this->update_matrix_elements();
}

void CGM::ButtonMatrix::AddColumn(uint32_t ColumnCount) {
    this->MyMatSize.x += ColumnCount;
    this->resize_array();
    this->update_matrix_elements();
}

void CGM::ButtonMatrix::AddTextToButton(uint32_t index, const char* TextToAdd) {
    this->GetElement(index) << TextToAdd;
}

void CGM::ButtonMatrix::AddTextToButton(CGM::Vec2i index, const char* TextToAdd) {
    this->GetElement(index) << TextToAdd;
}

void CGM::ButtonMatrix::AddTextToButton(uint32_t x, uint32_t y, const char* TextToAdd) {
    this->GetElement(x, y) << TextToAdd;
}

bool CGM::ButtonMatrix::is_hovered() const {
    for (auto& el : this->MyButtonArray) {
        if (el.is_hovered()) return true;
    }
    return false;
}

bool CGM::ButtonMatrix::is_hovered(uint32_t& hovered_index) const {
    for (int i = 0; i < this->GetMatrixIndexCount(); ++i) {
        if (this->MyButtonArray[i].is_hovered()) {
            hovered_index = i;
            return true;
        }
    }
    hovered_index = 0;
    return false;
}

bool CGM::ButtonMatrix::is_hovered(CGM::Vec2i& hovered_index) const {
    for (int y = 0; y < this->GetMatrixSize().y; ++y) {
        for (int x = 0; x < this->GetMatrixSize().x; ++x) {
            if (this->MyButtonArray[this->index_of(hovered_index)].is_hovered()) {
                hovered_index = CGM::Vec2i(x, y);
                return true;
            }
        }
    }
    hovered_index = CGM::Vec2i(0, 0);
    return false;
}

bool CGM::ButtonMatrix::is_hovered(uint32_t& x_hovered, uint32_t& y_hovered) const {
    CGM::Vec2i temp(x_hovered, y_hovered);
    bool hov_status = this->is_hovered(temp);

    x_hovered = temp.x;
    y_hovered = temp.y;

    return hov_status;
}

bool CGM::ButtonMatrix::is_left_clicked() const {
    for (auto& el : this->MyButtonArray) {
        if (el.is_left_clicked()) return true;
    }
    return false;
}

bool CGM::ButtonMatrix::is_left_clicked(uint32_t& hovered_index) const {
    for (int i = 0; i < this->GetMatrixIndexCount(); ++i) {
        if (this->MyButtonArray[i].is_left_clicked()) {
            hovered_index = i;
            return true;
        }
    }
    hovered_index = 0;
    return false;
}

bool CGM::ButtonMatrix::is_left_clicked(CGM::Vec2i& hovered_index) const {
    for (int y = 0; y < this->GetMatrixSize().y; ++y) {
        for (int x = 0; x < this->GetMatrixSize().x; ++x) {
            if (this->MyButtonArray[this->index_of(hovered_index)].is_left_clicked()) {
                hovered_index = CGM::Vec2i(0, 0);
                return true;
            }
        }
    }
    hovered_index = CGM::Vec2i(0, 0);
    return false;
}

bool CGM::ButtonMatrix::is_left_clicked(uint32_t& x_hovered, uint32_t& y_hovered) const {
    CGM::Vec2i temp(x_hovered, y_hovered);
    bool status = this->is_left_clicked(temp);

    x_hovered = temp.x;
    y_hovered = temp.y;

    return status;
}

bool CGM::ButtonMatrix::is_right_clicked() const {
    for (auto& el : this->MyButtonArray) {
        if (el.is_right_clicked()) return true;
    }
    return false;
}

bool CGM::ButtonMatrix::is_right_clicked(uint32_t& hovered_index) const {
    for (int i = 0; i < this->GetMatrixIndexCount(); ++i) {
        if (this->MyButtonArray[i].is_right_clicked()) {
            hovered_index = i;
            return true;
        }
    }
    hovered_index = 0;
    return false;
}

bool CGM::ButtonMatrix::is_right_clicked(CGM::Vec2i& hovered_index) const {
    for (int y = 0; y < this->GetMatrixSize().y; ++y) {
        for (int x = 0; x < this->GetMatrixSize().x; ++x) {
            if (this->MyButtonArray[this->index_of(hovered_index)].is_right_clicked()) {
                hovered_index = CGM::Vec2i(0, 0);
                return true;
            }
        }
    }
    hovered_index = CGM::Vec2i(0, 0);
    return false;
}

bool CGM::ButtonMatrix::is_right_clicked(uint32_t& x_hovered, uint32_t& y_hovered) const {
    CGM::Vec2i temp(x_hovered, y_hovered);
    bool status = this->is_right_clicked(temp);

    x_hovered = temp.x;
    y_hovered = temp.y;

    return status;
}

void CGM::ButtonMatrix::ResetMatrix() {
    this->MyMatSize = CGM::Vec2i(1, 1);
    this->MyElementSize = CGM::Vec2i(0, 0);
    this->resize_array();
    this->update_matrix_elements();
}

void CGM::ButtonMatrix::ResetElement(uint32_t index) {
    this->GetElement(index).SetSelectedColor(this->GetMatrixSelectedColor());
    this->GetElement(index).SetNotSelectedColor(this->GetMatrixNotSelectedColor());
    this->GetElement(index).ClearText();

    this->update_matrix_elements();
}

void CGM::ButtonMatrix::ResetElement(CGM::Vec2i index) {
    this->ResetElement(this->index_of(index));
}

void CGM::ButtonMatrix::ResetElement(uint32_t x, uint32_t y) {
    this->ResetElement(this->index_of(x, y));
}

void CGM::ButtonMatrix::AppendToCanvas(CGM::Canvas2D* Can) {
    for (auto& el : this->MyButtonArray) {
        el.AppendToCanvas(Can);
    }
}

void CGM::ButtonMatrix::resize_array() {
    this->MyButtonArray.clear();
    this->MyButtonArray.resize(this->GetMatrixIndexCount());
}

void CGM::ButtonMatrix::update_matrix_elements() {
    CGM::Vec2i pos_to_place = this->GetPosition();
    CGM::Vec2i size_of_element = this->GetMatrixElementSize() + CGM::Vec2i(this->GetSpaceBetweenElements() * 2, this->GetSpaceBetweenElements());

    for (int y = 0; y < this->GetMatrixSize().y; ++y) {
        for (int x = 0; x < this->GetMatrixSize().x; ++x) {
            this->GetElement(x, y).SetPosition(pos_to_place);
            this->GetElement(x, y).SetSize(this->GetMatrixElementSize());
            pos_to_place.x += size_of_element.x;
        }
        pos_to_place = this->GetPosition();
        pos_to_place.y += size_of_element.y * (y + 1);
    }
}

void CGM::ButtonMatrix::apply_matrix_coloring() {
    for (auto& el : this->MyButtonArray) {
        el.SetSelectedColor(this->MySelectedColor);
        el.SetNotSelectedColor(this->MyNotSelectedColor);
    }
}

int CGM::ButtonMatrix::index_of(int index) const {
#ifdef _DEBUG
    if (index < 0 || index >= this->GetMatrixIndexCount()) DebugBreak();
#endif
    return index;
}

int CGM::ButtonMatrix::index_of(int x, int y) const {
#ifdef _DEBUG
    if (x < 0 || x >= this->GetMatrixSize().x || y < 0 || y >= this->GetMatrixSize().y) DebugBreak();
#endif
    return y * this->GetMatrixSize().x + x;
}

int CGM::ButtonMatrix::index_of(CGM::Vec2i i) const {
    return this->index_of(i.x, i.y);
}

void CGM::SaveButtonMatrixToFile(std::ofstream& out_file, const CGM::ButtonMatrix* butt_mat) {

    out_file.write((char*)&butt_mat->MyMatSize, sizeof(CGM::Vec2i));
    out_file.write((char*)&butt_mat->MyElementSize, sizeof(CGM::Vec2i));
    out_file.write((char*)&butt_mat->MySelectedColor, sizeof(uint8_t));
    out_file.write((char*)&butt_mat->MyNotSelectedColor, sizeof(uint8_t));
    out_file.write((char*)&butt_mat->MySpaceBetweenElemenets, sizeof(uint32_t));

    for (auto& el : butt_mat->MyButtonArray) {
        CGM::SaveButtonToFile(out_file, &el);
    }

}

void CGM::LoadButtonMatrixFromFile(std::ifstream& in_file, CGM::ButtonMatrix* butt_mat) {

    in_file.read((char*)&butt_mat->MyMatSize, sizeof(CGM::Vec2i));
    in_file.read((char*)&butt_mat->MyElementSize, sizeof(CGM::Vec2i));
    in_file.read((char*)&butt_mat->MySelectedColor, sizeof(uint8_t));
    in_file.read((char*)&butt_mat->MyNotSelectedColor, sizeof(uint8_t));
    in_file.read((char*)&butt_mat->MySpaceBetweenElemenets, sizeof(uint32_t));

    butt_mat->resize_array();
    for (auto& el : butt_mat->MyButtonArray) {
        CGM::LoadButtonFromFile(in_file, &el);
    }
}
