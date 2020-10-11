#pragma once

#include "CGM_Canvas2D.h"
#include "CGM_Shapes2D.h"
#include "CGM_TextBox2D.h"

namespace CGM {

	template<typename T>
	class BaseButton2D : public CGM::Entity2D<T> {
	public:
		bool is_hovered() const;
		bool is_left_clicked() const;
		bool is_right_clicked() const;

	};

	typedef BaseButton2D<int> bButton2i_util;
	typedef BaseButton2D<double> bButton2d_util;

	class Button : public bButton2i_util {
	public:

		Button();
		Button(uint8_t Color);
		Button(uint8_t SelColor, uint8_t NotSelColor);
		Button(uint8_t SelColor, uint8_t NotSelColor, CGM::Reg2i Reg);
		Button(uint8_t SelColor, uint8_t NotSelColor, CGM::Vec2i Pos, CGM::Vec2i Size);

		void SetSize(int x, int y);
		void SetSize(CGM::Vec2i S);

		void SetPosition(int x, int y);
		void SetPosition(CGM::Vec2i P);

		void SetRegion(CGM::Reg2i Reg);

		void SetColor(uint8_t Color);
		void SetSelectedColor(uint8_t Color);
		void SetNotSelectedColor(uint8_t Color);

		void SetFontColor(uint8_t Color);

		void SetFontFormat_TextBreak(bool Mode);
		void SetFontFormat_CenteredTopDown(bool Mode);

		uint8_t GetFontColor() const;
		uint8_t GetSelectedColor() const;
		uint8_t GetNotSelectedColor() const;

		template<typename T>
		friend Button& operator<<(Button& butt, T message_to_add);

		void ClearText();

		void AppendToCanvas(CGM::Canvas2D* Can);

		friend void SaveButtonToFile(std::ofstream&, const CGM::Button*);

		friend void LoadButtonFromFile(std::ifstream&, CGM::Button*);

	private:
		uint8_t MyOnColor = CGM::Color::Black;
		uint8_t MyOffColor = CGM::Color::Black;

		CGM::TextBox MyText;
		CGM::RectangleShape MyRect;

	};

	void SaveButtonToFile(std::ofstream& out_file, const CGM::Button* Butt);

	void LoadButtonFromFile(std::ifstream& in_file, CGM::Button* Butt);

	////////////////////////////////////////////////////////

	template<typename T>
	inline bool BaseButton2D<T>::is_hovered() const {
		return this->GetRegion().is_over_a_vector(CGM::Canvas2D::GetMousePos());
	}

	template<typename T>
	inline bool BaseButton2D<T>::is_left_clicked() const {
		return GetKeyState(VK_LBUTTON) < 0 && this->is_hovered();
	}

	template<typename T>
	inline bool BaseButton2D<T>::is_right_clicked() const {
		return GetKeyState(VK_RBUTTON) < 0 && this->is_hovered();
	}

	template<typename T>
	Button& operator<<(Button& butt, T message_to_add) {
		butt.MyText << message_to_add;
		return butt;
	}

}
