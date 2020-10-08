#pragma once

#include "CGM_Canvas2D.h"

#include <sstream>

#define ENDLINE '\n'

namespace CGM {

	class TextBox : public CGM::Ent2i {
	public:
		TextBox() {}
		TextBox(CGM::Vec2i Size);
		
		void SetFontColor(uint8_t Color);

		void SetFormatMode_TextBreak(bool Mode);
		void SetFormatMode_CenterTopDown(bool Mode);
		
		uint8_t GetFontColor() const;
		uint32_t GetBufferSize() const;

		void ClearBuffer();

		template<typename T>
		friend TextBox& operator<<(CGM::TextBox& tb, const T ElementToAdd);

		void AppendToCanvas(CGM::Canvas2D* Can);

		void SetBufferCharAt(char C, uint32_t index);
		void SetBufferColorAt(uint8_t Col, uint32_t index);

		char GetBufferCharAt(uint32_t index) const;
		uint8_t GetBufferColorAt(uint32_t index) const;

		friend void SaveTextBoxToFile(std::ofstream&, const TextBox*);
		friend void LoadTextBoxFromFile(std::ifstream&, TextBox*);

	private:
		struct text_element {
			char Letter = ' ';
			uint8_t Color = CGM::Canvas2D::Color::Black;
		};

		std::vector<text_element> MyTextBuffer;
		uint8_t MyCurrentColor = CGM::Canvas2D::Color::White;

		std::string convert_TextBuffer_to_string() const;

		bool TextBreakMode = false;
		bool CenterTDMode = false;

	};

	void SaveTextBoxToFile(std::ofstream& out_file, const TextBox* text_to_save);

	void LoadTextBoxFromFile(std::ifstream& in_file, TextBox* text_to_load);

	template<typename T>
	TextBox& operator<<(CGM::TextBox& tb, const T ElementToAdd) {
		std::stringstream ss;

		ss << ElementToAdd;
		std::string text_to_add = ss.str();

		for (int i = 0; i < text_to_add.size(); ++i) {
			CGM::TextBox::text_element tel;

			tel.Letter = text_to_add[i];
			tel.Color = tb.MyCurrentColor;

			tb.MyTextBuffer.push_back(tel);
		}

		return tb;
	}

}