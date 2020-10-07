#pragma once

#include <cmath>

#define _PI 3.14159265359

namespace CGM {

	template<typename T>
	struct Vector2D {
	
		T x;
		T y;

		Vector2D() : x(0), y(0) {}
		Vector2D(T x, T y);

		double get_lenght() const;
		double get_lenght_squared() const;
		double get_distance(CGM::Vector2D<T> Vec) const;
		double get_distance_squared(CGM::Vector2D<T> Vec) const;

		double get_dot_between(CGM::Vector2D<T> Vec) const;

		double get_angle_deg(CGM::Vector2D<T> Vec) const;
		double get_angle_rad(CGM::Vector2D<T> Vec) const;

		CGM::Vector2D<T> get_normalized() const;
		CGM::Vector2D<T> get_direction_to(CGM::Vector2D<T> Vec) const;

		CGM::Vector2D<T> get_largest_vector(CGM::Vector2D<T> Vec) const;
		CGM::Vector2D<T> get_smallest_vector(CGM::Vector2D<T> Vec) const;

		CGM::Vector2D<T> operator+ (CGM::Vector2D<T> Vec) const;
		CGM::Vector2D<T> operator- (CGM::Vector2D<T> Vec) const;
		CGM::Vector2D<T> operator* (T Val) const;
		CGM::Vector2D<T> operator/ (T Val) const;

		CGM::Vector2D<T>& operator+= (CGM::Vector2D<T> Vec);
		CGM::Vector2D<T>& operator-= (CGM::Vector2D<T> Vec);
		CGM::Vector2D<T>& operator*= (T Val);
		CGM::Vector2D<T>& operator/= (T Val);

		bool operator== (CGM::Vector2D<T> Vec) const;
		bool operator!= (CGM::Vector2D<T> Vec) const;

	};

	typedef CGM::Vector2D<int> Vec2i;
	typedef CGM::Vector2D<double> Vec2d;

	//-------------------------------------------------------------//

	template<typename T>
	inline Vector2D<T>::Vector2D(T x, T y) {
		this->x = x;
		this->y = y;
	}

	template<typename T>
	inline double Vector2D<T>::get_lenght() const {
		return this->get_distance(CGM::Vector2D<T>(0, 0));
	}

	template<typename T>
	inline double Vector2D<T>::get_lenght_squared() const {
		return this->get_distance_squared(CGM::Vector2D<T>(0, 0));
	}

	template<typename T>
	inline double Vector2D<T>::get_distance(CGM::Vector2D<T> Vec) const {
		return std::sqrt(this->get_distance_squared(Vec));
	}

	template<typename T>
	inline double Vector2D<T>::get_distance_squared(CGM::Vector2D<T> Vec) const {
		return (std::pow(this->x - Vec.x, 2) + std::pow(this->y - Vec.y, 2));
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::get_normalized() const {
		double len = this->get_lenght();
		return CGM::Vector2D<T>(this->x / len, this->y / len);
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::get_direction_to(CGM::Vector2D<T> Vec) const {
		CGM::Vector2D<T> my_big_dir_vec = Vec - *this;
		return my_big_dir_vec.get_normalized();
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::get_largest_vector(CGM::Vector2D<T> Vec) const {
		return CGM::Vector2D<T>(std::fmax(this->x, Vec.x), std::fmax(this->y, Vec.y));
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::get_smallest_vector(CGM::Vector2D<T> Vec) const {
		return CGM::Vector2D<T>(std::fmin(this->x, Vec.x), std::fmin(this->y, Vec.y));
	}

	template<typename T>
	inline double Vector2D<T>::get_dot_between(CGM::Vector2D<T> Vec) const {
		CGM::Vector2D<T> Vec1 = this->get_normalized();
		CGM::Vector2D<T> Vec2 = Vec.get_normalized();
		return ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
	}

	template<typename T>
	inline double Vector2D<T>::get_angle_deg(CGM::Vector2D<T> Vec) const {
		return (180 * this->get_angle_rad(Vec)) / _PI;
	}

	template<typename T>
	inline double Vector2D<T>::get_angle_rad(CGM::Vector2D<T> Vec) const {
		return std::acos(this->get_dot_between(Vec));
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::operator+(CGM::Vector2D<T> Vec) const {
		return CGM::Vector2D<T>(this->x + Vec.x, this->y + Vec.y);
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::operator-(CGM::Vector2D<T> Vec) const {
		return CGM::Vector2D<T>(this->x - Vec.x, this->y - Vec.y);
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::operator*(T Val) const {
		return CGM::Vector2D<T>(this->x * Val, this->y * Val);
	}

	template<typename T>
	inline CGM::Vector2D<T> Vector2D<T>::operator/(T Val) const {
		return CGM::Vector2D<T>(this->x / Val, this->y / Val);
	}

	template<typename T>
	inline CGM::Vector2D<T>& Vector2D<T>::operator+=(CGM::Vector2D<T> Vec) {
		*this = this->operator+(Vec);
		return *this;
	}

	template<typename T>
	inline CGM::Vector2D<T>& Vector2D<T>::operator-=(CGM::Vector2D<T> Vec) {
		*this = this->operator-(Vec);
		return *this;
	}

	template<typename T>
	inline CGM::Vector2D<T>& Vector2D<T>::operator*=(T Val) {
		*this = this->operator*(Val);
		return *this;
	}

	template<typename T>
	inline CGM::Vector2D<T>& Vector2D<T>::operator/=(T Val) {
		*this = this->operator/(Val);
		return *this;
	}

	template<typename T>
	inline bool Vector2D<T>::operator==(CGM::Vector2D<T> Vec) const {
		return (this->x == Vec.x) && (this->y == Vec.y);
	}

	template<typename T>
	inline bool Vector2D<T>::operator!=(CGM::Vector2D<T> Vec) const {
		return !this->operator==(Vec);
	}

}