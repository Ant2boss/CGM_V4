#pragma once

#include "CGM_Vector2D.h"

#include <cmath>

namespace CGM {
	
	template<typename T>
	struct Region2D {

		CGM::Vector2D<T> Position;
		CGM::Vector2D<T> Size;

		Region2D() {}
		Region2D(CGM::Vector2D<T> Pos, CGM::Vector2D<T> Siz);

		bool is_over_a_vector(CGM::Vector2D<T> Vec) const;
		bool is_over_a_region(CGM::Region2D<T> Reg) const;

	};

	typedef Region2D<int> Reg2i;
	typedef Region2D<double> Reg2d;

	template<typename T>
	CGM::Region2D<T> generate_region_from_start_to_end(CGM::Vector2D<T> Start, CGM::Vector2D<T> End);

	//---------------------------------------------------------------//

	template<typename T>
	inline Region2D<T>::Region2D(CGM::Vector2D<T> Pos, CGM::Vector2D<T> Siz) {
		this->Position = Pos;
		this->Size = Siz;
	}

	template<typename T>
	inline bool Region2D<T>::is_over_a_vector(CGM::Vector2D<T> Vec) const {
		return (Vec.x >= this->Position.x && Vec.x < (this->Position + this->Size).x && Vec.y >= this->Position.y && Vec.y < (Position + this->Size).y);
	}

	template<typename T>
	inline bool Region2D<T>::is_over_a_region(CGM::Region2D<T> Reg) const {
		if ((Reg.Position.x > (this->Position + this->Size).x - 1) || ((Reg.Position + Reg.Size).x <= this->Position.x))
			return false;
		if ((Reg.Position.y > (this->Position + this->Size).y - 1) || ((Reg.Position + Reg.Size).y <= this->Position.y))
			return false;
		return true;
	}

	template<typename T>
	CGM::Region2D<T> generate_region_from_start_to_end(CGM::Vector2D<T> Start, CGM::Vector2D<T> End) {
		CGM::Region2D<T> Reg;
		Reg.Position = CGM::Vector2D<T>(std::fmin(Start.x, End.x), std::fmin(Start.y, End.y));
		Reg.Size = CGM::Vector2D<T>(std::abs(End.x - Start.x), std::abs(End.y - Start.y));

		return Reg;
	}

}