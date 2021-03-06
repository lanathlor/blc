#include "blc/float.hpp"

#include <iostream>

blc::math::Float::Float() : _nb(0), _E(0)
{
}

blc::math::Float::Float(float i) : _nb(i), _E(0)
{
	if (this->_nb > 1 || this->_nb < -1){
		for (; this->_nb >= 10 || this->_nb <= -10;){
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;){
			this->_E--;
			this->_nb *= 10;
		}
	}
}

blc::math::Float::Float(float i, int E) : _nb(i), _E(E)
{
	if (this->_nb > 1 || this->_nb < -1){
		for (; this->_nb >= 10 || this->_nb <= -10;){
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;){
			this->_E--;
			this->_nb *= 10;
		}
	}
}

blc::math::Float::Float(const blc::math::Float &other) : _nb(other.getNb()), _E(other.getE())
{
}

blc::math::Float::Float(blc::math::Float &&other) : _nb(other.getNb()), _E(other.getE())
{
	other.setNb(0);
	other.setE(0);
}

blc::math::Float &blc::math::Float::operator=(float i)
{
	this->_nb = i;
	this->_E = 0;

	if (this->_nb > 1 || this->_nb < -1){
		for (; this->_nb >= 10 || this->_nb <= -10;){
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;){
			this->_E--;
			this->_nb *= 10;
		}
	}
	return (*this);
}

blc::math::Float &blc::math::Float::operator=(const blc::math::Float &other)
{
	this->_nb = other.getNb();
	this->_E = other.getE();
	return (*this);
}

blc::math::Float &blc::math::Float::operator=(blc::math::Float &&other)
{
	this->_nb = other.getNb();
	this->_E = other.getE();

	other.setNb(0);
	other.setE(0);
	return (*this);
}

blc::math::Float &blc::math::Float::operator+(float i)
{
	blc::math::Float fl(i);

	*this = *this + fl;
	return (*this);
}

blc::math::Float &blc::math::Float::operator+(const blc::math::Float &i)
{
	int diff = this->_E - i.getE();
	float tmp = i.getNb();

	while (diff != 0){
		if (diff < 0){
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	*this = blc::math::Float(this->_nb + tmp, this->_E);
	return (*this);
}

blc::math::Float &blc::math::Float::operator-(float i)
{
	blc::math::Float fl(i);

	*this = *this - fl;
	return (*this);
}

blc::math::Float &blc::math::Float::operator-(const blc::math::Float &i)
{
	int diff = this->_E - i.getE();
	float tmp = i.getNb();

	while (diff != 0){
		if (diff < 0){
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	*this = blc::math::Float(this->_nb - tmp, this->_E);
	return (*this);
}

blc::math::Float &blc::math::Float::operator*(float i)
{
	blc::math::Float fl(i);

	*this = *this * fl;
	return (*this);
}

blc::math::Float &blc::math::Float::operator*(const blc::math::Float &i)
{
	int diff = this->_E - i.getE();
	float tmp = i.getNb();

	while (diff != 0){
		if (diff < 0){
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	*this = blc::math::Float(this->_nb * tmp, this->_E);
	return (*this);
}

blc::math::Float &blc::math::Float::operator/(float i)
{
	blc::math::Float fl(i);

	*this = *this / fl;
	return (*this);
}

blc::math::Float &blc::math::Float::operator/(const blc::math::Float &i)
{
	int diff = this->_E - i.getE();
	float tmp = i.getNb();

	while (diff != 0){
		if (diff < 0){
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	*this = blc::math::Float(this->_nb * tmp, this->_E);
	return (*this);
}

bool blc::math::Float::operator==(float i)
{
	if (this->calculate() == i)
		return (true);
	return (false);
}

bool blc::math::Float::operator==(const blc::math::Float &i)
{
	if (this->_nb != i.getNb())
		return (false);
	if (this->_E != i.getE())
		return (false);
	return (true);
}

bool blc::math::Float::operator>(float i)
{
	if (this->calculate() > i)
		return (true);
	return (false);
}

bool blc::math::Float::operator>(const blc::math::Float &i)
{
	if (this->_E < i.getE())
		return (false);
	if (this->_nb <= i.getNb())
		return (false);
	return (true);
}

bool blc::math::Float::operator<(float i)
{
	if (this->calculate() < i)
		return (true);
	return (false);
}

bool blc::math::Float::operator<(const blc::math::Float &i)
{
	if (this->_E > i.getE())
		return (false);
	if (this->_nb >= i.getNb())
		return (false);
	return (true);
}

bool blc::math::Float::operator>=(float i)
{
	if (this->calculate() >= i)
		return (true);
	return (false);
}

bool blc::math::Float::operator>=(const blc::math::Float &i)
{
	if (this->_E < i.getE())
		return (false);
	if (this->_nb < i.getNb())
		return (false);
	return (true);
}

bool blc::math::Float::operator<=(float i)
{
	if (this->calculate() <= i)
		return (true);
	return (false);
}

bool blc::math::Float::operator<=(const blc::math::Float &i)
{
	if (this->_E > i.getE())
		return (false);
	if (this->_nb > i.getNb())
		return (false);
	return (true);
}

float blc::math::Float::operator()() const
{
	return (this->calculate());
}

float blc::math::Float::getNb() const
{
	return (this->_nb);
}

void blc::math::Float::setNb(float nb)
{
	this->_nb = nb;
}

int blc::math::Float::getE() const
{
	return (this->_E);
}

void blc::math::Float::setE(int E)
{
	this->_E = E;
}

float blc::math::Float::calculate() const
{
	int	tmp = this->_E;
	float	ret = this->_nb;

	while (tmp != 0){
		if (tmp < 0){
			ret /= 10;
			tmp++;
		} else {
			ret *= 10;
			tmp--;
		}
	}
	return (ret);
}

void blc::math::Float::align()
{
	if (this->_nb > 1 || this->_nb < -1){
		for (; this->_nb >= 10 || this->_nb <= -10;){
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;){
			this->_E--;
			this->_nb *= 10;
		}
	}
}

void blc::math::Float::align(int nb)
{
	if (nb > 0){
		while (nb != 0){
			this->_nb *= 10;
			this->_E--;
			nb--;
		}
	} else {
		while (nb != 0){
			this->_nb /= 10;
			this->_E++;
			nb++;
		}
	}
}

std::string blc::math::Float::serialize() const
{
	return ("");
}

void blc::math::Float::unserialize(const std::string &str)
{
}