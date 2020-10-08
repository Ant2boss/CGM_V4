#include "CGM_TextBox2D.h"

size_t get_next_word_len(std::string Text, uint32_t start_index) {
	size_t len = 0;
	for (int i = start_index; i < Text.length(); ++i) {
		if (Text[i] == ' ' || Text[i] == '\n') break;

		++len;
	}

	return len;
}

CGM::TextBox::TextBox(CGM::Vec2i Size) {
	this->SetSize(Size);
}

void CGM::TextBox::SetFontColor(uint8_t Color) {
	this->MyCurrentColor = Color;
}

void CGM::TextBox::SetFormatMode_TextBreak(bool Mode) {
	this->TextBreakMode = Mode;
}

void CGM::TextBox::SetFormatMode_CenterTopDown(bool Mode) {
	this->CenterTDMode = Mode;
}

uint8_t CGM::TextBox::GetFontColor() const {
	return this->MyCurrentColor;
}

uint32_t CGM::TextBox::GetBufferSize() const {
	return this->MyTextBuffer.size();
}

void CGM::TextBox::ClearBuffer() {
	this->MyTextBuffer.clear();
}

void CGM::TextBox::AppendToCanvas(CGM::Canvas2D* Can) {
	CGM::Vec2i Offset = this->GetPosition();
	std::string OutputText = this->convert_TextBuffer_to_string();

	if (this->CenterTDMode) {
		int char_count = 0;	//Number of characters
		int len_count = 0;	//Lenght of a single line up to a point

		for (int i = 0; i < OutputText.length(); ++i) {
			//If anything other thane \n is encounterd increase char_count by 1
			if (OutputText[i] != '\n') {
				++char_count;

				++len_count;

				if (len_count >= this->GetSize().x)
					len_count = 0;
			}
			//Othewise increase it by the amount of remaining lenght
			else {
				char_count += this->GetSize().x - len_count;
				len_count = 0;
			}
		}

		int aprox_line_count = std::round(char_count / this->GetSize().x);

		int empty_line_count = this->GetSize().y - aprox_line_count;

		Offset.y += empty_line_count / 2;

		if (Offset.y < this->GetPosition().y) {
			Offset.y = this->GetPosition().y;
		}
	}

	if (this->TextBreakMode) {		
		uint32_t curr_index = 0;

		CGM::Vec2i tOff;

		while (curr_index < this->GetBufferSize()) {
			//Get world lenght
			uint32_t next_word = get_next_word_len(OutputText, curr_index);

			//Calculate where the cursor would be if the word were written out
			tOff = Offset;
			tOff.x += next_word;

			//If the word would be to far to the right, adjust the Offset
			if (tOff.x >= (this->GetPosition() + this->GetSize()).x) {
				Offset.x = this->GetPosition().x;
				++Offset.y;
				++tOff.y;
			}
			if (tOff.y >= (this->GetPosition() + this->GetSize()).y) {
				Offset = this->GetPosition();
			}

			//Write as much of the word as possible
			for (int i = curr_index; i < this->GetBufferSize(); ++i) {
				if (this->GetBufferCharAt(i) == '\n') {
					Offset.x = this->GetPosition().x;
					++Offset.y;
					break;
				}

				Can->SetCharAt(this->GetBufferCharAt(i), Offset);
				Can->SetFontColorAt(this->GetBufferColorAt(i), Offset);

				++Offset.x;

				if (this->GetBufferCharAt(i) == ' ') break;
			}

			//Update curr_index
			curr_index += next_word + 1;
		}

	}
	else {
		for (int i = 0; i < this->GetBufferSize(); ++i) {
			if (this->GetBufferCharAt(i) == ENDLINE) {
				Offset.x = this->GetPosition().x;
				Offset.y++;
				continue;
			}
			if (Offset.x >= (this->GetSize() + this->GetPosition()).x) {
				Offset.x = this->GetPosition().x;
				Offset.y++;
			}
			if (Offset.y >= (this->GetPosition() + this->GetSize()).y) {
				Offset = this->GetPosition();
			}

			Can->SetCharAt(this->GetBufferCharAt(i), Offset);
			Can->SetFontColorAt(this->GetBufferColorAt(i), Offset);

			++Offset.x;
		}
	}
}

void CGM::TextBox::SetBufferCharAt(char C, uint32_t index) {
#ifdef _DEBUG
	if (index >= this->GetBufferSize()) DebugBreak();
#endif
	this->MyTextBuffer[index].Letter = C;
}

void CGM::TextBox::SetBufferColorAt(uint8_t Col, uint32_t index) {
#ifdef _DEBUG
	if (index >= this->GetBufferSize()) DebugBreak();
#endif
	this->MyTextBuffer[index].Color = Col;
}

char CGM::TextBox::GetBufferCharAt(uint32_t index) const {
#ifdef _DEBUG
	if (index >= this->GetBufferSize()) DebugBreak();
#endif
	return this->MyTextBuffer[index].Letter;
}

uint8_t CGM::TextBox::GetBufferColorAt(uint32_t index) const {
#ifdef _DEBUG
	if (index >= this->GetBufferSize()) DebugBreak();
#endif
	return this->MyTextBuffer[index].Color;
}

std::string CGM::TextBox::convert_TextBuffer_to_string() const {
	std::stringstream ss;

	for (int i = 0; i < this->GetBufferSize(); ++i) {
		ss << this->GetBufferCharAt(i);
	}

	return ss.str();
}

void CGM::SaveTextBoxToFile(std::ofstream& out_file, const TextBox* text_to_save) {
	CGM::SaveEntity2DToFile(out_file, text_to_save);

	out_file.write((char*)&text_to_save->TextBreakMode, sizeof(bool));
	out_file.write((char*)&text_to_save->CenterTDMode, sizeof(bool));

	uint32_t el_count = text_to_save->GetBufferSize();
	out_file.write((char*)&el_count, sizeof(uint32_t));
	out_file.write((char*)&text_to_save->MyTextBuffer[0], el_count * sizeof(CGM::TextBox::text_element));
}

void CGM::LoadTextBoxFromFile(std::ifstream& in_file, TextBox* text_to_load) {
	CGM::LoadEntity2DFromFile(in_file, text_to_load);

	in_file.read((char*)&text_to_load->TextBreakMode, sizeof(bool));
	in_file.read((char*)&text_to_load->CenterTDMode, sizeof(bool));

	uint32_t el_count;
	in_file.read((char*)&el_count, sizeof(uint32_t));
	CGM::TextBox::text_element* tel_array = new CGM::TextBox::text_element[el_count];

	in_file.read((char*)tel_array, sizeof(CGM::TextBox::text_element) * el_count);

	text_to_load->MyTextBuffer.resize(el_count);
	memcpy(&text_to_load->MyTextBuffer[0], tel_array, sizeof(CGM::TextBox::text_element) * el_count);

	delete[] tel_array;

}
