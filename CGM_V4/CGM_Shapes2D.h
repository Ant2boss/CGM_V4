#pragma once

#include "CGM_Canvas2D.h"

namespace CGM {
	
	class BaseShape : public CGM::Ent2i {
	public:

		void SetFillMode(bool Mode);

		void SetColor(uint8_t Color);

		bool GetFillMode() const;

		uint8_t GetColor() const;

	protected:

		uint8_t MyColor = CGM::Canvas2D::Color::Black;
		bool MyFillMode = true;

	};

	class RectangleShape : public BaseShape {
	public:

		RectangleShape() {}
		RectangleShape(uint8_t Color);
		RectangleShape(uint8_t Color, CGM::Vec2i Pos, CGM::Vec2i Size);

		void AppendToCanvas(CGM::Canvas2D* Can);

	};

	class ElipseShape : public BaseShape {
	public:

		ElipseShape() {}
		ElipseShape(uint8_t Color);
		ElipseShape(uint8_t Color, CGM::Vec2i Pos, CGM::Vec2i Size);

		void AppendToCanvas(CGM::Canvas2D* Can);

	};

	void SaveShapeToFile(std::ofstream& out_file, const CGM::BaseShape* Shape);

	void LoadShapeFromFile(std::ifstream& in_file, CGM::BaseShape* Shape);

}