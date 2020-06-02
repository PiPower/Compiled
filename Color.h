#pragma once
class Color
{
public:
	Color(int c) noexcept : c(c) {}
	Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A = 255)
	{
		c = (R << 16) | (G << 8) | (B << 0) | (A << 24);
	}
	void SetR(unsigned char R) noexcept { c = (c & 0xFF00FFFF) | (R << 16); }
	void SetG(unsigned char G) noexcept { c = (c & 0xFFFF00FF) | (G << 8); }
	void SetB(unsigned char B) noexcept { c = (c & 0xFFFFF00) | (B << 0); }
	void SetA(unsigned char A) noexcept { c = (c & 0xFFFFFFFF) | (A << 24); }
	unsigned char GetR() const noexcept { return (c >> 16u) & 0xFFu; }
	unsigned char GetG() const noexcept { return (c >> 8) & 0xFFu; }
	unsigned char GetB() const noexcept { return  (c >> 0) & 0xFFu; }
	unsigned char GetA() const noexcept { return  (c >> 24u) & 0xFFu; }
	int GetIntValue() const noexcept { return c; }
private:
	unsigned int c;
};