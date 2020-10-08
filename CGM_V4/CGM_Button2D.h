#pragma once

#include "CGM_Canvas2D.h"
#include "CGM_Shapes2D.h"
#include "CGM_TextBox2D.h"

namespace CGM {

	template<class MyShapeClass>
	class Button2D : public CGM::Ent2i{
	public:	
		
		Button2D();
		Button2D(uint8_t HovCol, uint8_t OffCol);
		Button2D(uint8_t HovCol, uint8_t OffCol, CGM::Vec2i Pos, CGM::Vec2i Siz);

		void SetTextFormatMode_TextBreak(bool Mode);
		void SetTextFormatMode_CenterTopDown(bool Mode);

		void SetFontColor(uint8_t Color);
		void SetColorFull(uint8_t Color);
		void SetColorHovered(uint8_t Color);
		void SetColorNotHovered(uint8_t Color);

		void SetSize(int x, int y);
		void SetSize(CGM::Vec2i S);
		void SetPosition(int x, int y);
		void SetPosition(CGM::Vec2i P);

		uint8_t GetFontColor() const;
		uint8_t GetColorHovered() const;
		uint8_t GetColorNotHovered() const;

		bool is_hovered() const;
		bool is_left_clicked() const;
		bool is_right_clicked() const;

		void AddTextToButton(const char* msg);

		void AppendToCanvas(CGM::Canvas2D* Can);

	private:

		MyShapeClass MyShape;
		CGM::TextBox MyText;

		uint8_t MyHovCol = CGM::Canvas2D::Color::Black;
		uint8_t MyNotHovCol = CGM::Canvas2D::Color::Black;

	};

	typedef Button2D<CGM::ElipseShape> Butt2_Elipse;
	typedef Button2D<CGM::RectangleShape> Butt2_Rect;

	/////////////////////////////////////////////////////////////////////////////////////////////////

	template<class MyShapeClass>
	inline Button2D<MyShapeClass>::Button2D() {
		this->SetTextFormatMode_CenterTopDown(true);
		this->SetTextFormatMode_TextBreak(true);
	}

	template<class MyShapeClass>
	inline Button2D<MyShapeClass>::Button2D(uint8_t HovCol, uint8_t OffCol) 
		: Button2D() {
		this->SetColorHovered(HovCol);
		this->SetColorNotHovered(OffCol);
	}

	template<class MyShapeClass>
	inline Button2D<MyShapeClass>::Button2D(uint8_t HovCol, uint8_t OffCol, CGM::Vec2i Pos, CGM::Vec2i Siz) 
		: Button2D(HovCol, OffCol) {
		this->SetSize(Siz);
		this->SetPosition(Pos);
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetTextFormatMode_TextBreak(bool Mode) {
		this->MyText.SetFormatMode_TextBreak(Mode);
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetTextFormatMode_CenterTopDown(bool Mode) {
		this->MyText.SetFormatMode_CenterTopDown(Mode);
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetFontColor(uint8_t Color) {
		this->MyText.SetFontColor(Color);
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetColorFull(uint8_t Color) {
		this->SetColorHovered(Color);
		this->SetColorNotHovered(Color);
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetColorHovered(uint8_t Color) {
		this->MyHovCol = Color;
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetColorNotHovered(uint8_t Color) {
		this->MyNotHovCol = Color;
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetSize(int x, int y) {
		this->SetSize(CGM::Vec2i(x, y));
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetSize(CGM::Vec2i S) {
		this->MyRegion.Size = S;
		this->MyShape.SetSize(S);
		this->MyText.SetSize(S);
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetPosition(int x, int y) {
		this->SetPosition(CGM::Vec2i(x, y));
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::SetPosition(CGM::Vec2i P) {
		this->MyRegion.Position = P;
		this->MyShape.SetPosition(P);
		this->MyText.SetPosition(P);
	}

	template<class MyShapeClass>
	inline uint8_t Button2D<MyShapeClass>::GetFontColor() const {
		return this->MyText.GetFontColor();
	}

	template<class MyShapeClass>
	inline uint8_t Button2D<MyShapeClass>::GetColorHovered() const {
		return this->MyHovCol;
	}

	template<class MyShapeClass>
	inline uint8_t Button2D<MyShapeClass>::GetColorNotHovered() const {
		return this->MyNotHovCol;
	}

	template<class MyShapeClass>
	inline bool Button2D<MyShapeClass>::is_hovered() const {
		return this->GetRegion().is_over_a_vector(CGM::Canvas2D::GetMousePos());
	}

	template<class MyShapeClass>
	inline bool Button2D<MyShapeClass>::is_left_clicked() const {
		return GetKeyState(VK_LBUTTON) < 0 && this->is_hovered();
	}

	template<class MyShapeClass>
	inline bool Button2D<MyShapeClass>::is_right_clicked() const {
		return GetKeyState(VK_RBUTTON) < 0 && this->is_hovered();
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::AddTextToButton(const char* msg) {
		this->MyText << msg;
	}

	template<class MyShapeClass>
	inline void Button2D<MyShapeClass>::AppendToCanvas(CGM::Canvas2D* Can) {
		if (this->MyShape.GetRegion().is_over_a_vector(Can->GetMousePos()))
			this->MyShape.SetColor(this->GetColorHovered());
		else
			this->MyShape.SetColor(this->GetColorNotHovered());

		Can->Append(&this->MyShape);
		Can->Append(&this->MyText);
	}

}
