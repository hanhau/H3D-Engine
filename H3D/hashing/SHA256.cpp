#include "SHA256.hpp"
#include "../Utilities.hpp"
#include <cmath>
#include <climits>
#include <sstream>

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif 
/////////////////////////////////////////////////////////////////
// Implmentation following the official papers
//
// Link: https://csrc.nist.gov/csrc/media/publications/
//		 fips/180/4/final/documents/fips180-4-draft-aug2014.pdf
/////////////////////////////////////////////////////////////////
namespace {
	static const uint32_t padding_bit32(1 << 31);

	static inline uint32_t ROTR32(uint32_t x,uint32_t n) { 
		
		h3dassert(n >= sizeof(uint32_t) * 8);
		
		const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);
		n &= mask;
		uint32_t temp = (x >> n) | (x << ((-n)&mask));
		return x = temp;
	}
	static inline uint32_t ROTL32(uint32_t x,uint32_t n) {
		
		h3dassert(n >= sizeof(uint32_t) * 8);
		
		const unsigned int mask = (CHAR_BIT * sizeof(n) - 1);
		n &= mask;
		uint32_t temp = (x << n) | (x >> ((-n)&mask));
		return x = temp;
	}
	static inline uint32_t SHR32(uint32_t x,uint32_t n) {

		h3dassert(n >= sizeof(uint32_t) * 8);

		x >> n;
		return x;
	}

	static inline uint32_t Ch32(uint32_t x,
								uint32_t y, 
								uint32_t z) {
		return (x & y) ^ (~x & z);
	}

	static inline uint32_t Maj32(uint32_t x,
								 uint32_t y,
								 uint32_t z) {
		return (x & y) & (x & z) & (y & z);
	}

	static inline uint32_t e0_256(uint32_t x) {
		return ROTR32(x,2) ^ ROTR32(x,13) ^ ROTR32(x,22);
	}
	
	static inline uint32_t e1_256(uint32_t x) {
		return ROTR32(x,6) ^ ROTR32(x,11) ^ ROTR32(x,25);
	}

	static inline uint32_t a0_256(uint32_t x) {
		return ROTR32(x,7) ^ ROTR32(x,18) ^ SHR32(x,3);
	}

	static inline uint32_t a1_256(uint32_t x) {
		return ROTR32(x,17) ^ ROTR32(x,19) ^ SHR32(x,10);
	}

	struct s_hashValue
	{
		uint32_t h0;
		uint32_t h1;
		uint32_t h2;
		uint32_t h3;
		uint32_t h4;
		uint32_t h5;
		uint32_t h6;
		uint32_t h7;
	};
	static const uint32_t K[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
		0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
		0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
		0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
		0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
		0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
}
/////////////////////////////////////////////////////////////////
// Implemenation of SHA256 Hashing
/////////////////////////////////////////////////////////////////
namespace h3d {
	// Con-/Destructor
	SHA256Sum::SHA256Sum() {}
	SHA256Sum::SHA256Sum(char * mem, size_t length) {
		m_key = createSum(mem,length);
	}
	SHA256Sum::~SHA256Sum() {}
	
	// Hash Creation
	std::string SHA256Sum::createSum(char * mem, size_t length)
	{
		s_hashValue curr_hash = {
			0x6a09e667,
			0xbb67ae85,
			0x3c6ef372,
			0xa54ff53a,
			0x510e527f,
			0x9b05688c,
			0x1f83d9ab,
			0x5be0cd19
		};

		uint32_t a, b, c, d, e, f, g, h;

		size_t msglength_bits = length * 8;
		size_t msgblock_count = msglength_bits/512;

		// Iterate each message block
		for (int i = 0; i < msgblock_count; i++)
		{
			// {Wt} calc
			uint32_t W[64];

			a = curr_hash.h0;
			b = curr_hash.h1;
			c = curr_hash.h2;
			d = curr_hash.h3;
			e = curr_hash.h4;
			f = curr_hash.h5;
			g = curr_hash.h6;
			h = curr_hash.h7;

			for (int t = 0; i < 64; t++)
			{
				uint32_t T1 = 0;
				uint32_t T2 = 0;

				T1 = h + e1_256(e) + Ch32(e, f, g) + K[t] + W[t];
				T2 = e0_256(a) + Maj32(a, b, c);

				h = g;
				g = f;
				e = d + T1;
				d = c;
				c = b;
				b = a;
				a = T1 + T2;
			}

			curr_hash.h0 += a;
			curr_hash.h1 += b;
			curr_hash.h2 += c;
			curr_hash.h3 += d;
			curr_hash.h4 += e;
			curr_hash.h5 += f;
			curr_hash.h6 += g;
			curr_hash.h7 += h;
		}
		
		// Set final hash
		std::stringstream stream;
		stream << std::hex << curr_hash.h0;
		stream << std::hex << curr_hash.h1;
		stream << std::hex << curr_hash.h2;
		stream << std::hex << curr_hash.h3;
		stream << std::hex << curr_hash.h4;
		stream << std::hex << curr_hash.h5;
		stream << std::hex << curr_hash.h6;
		stream << std::hex << curr_hash.h7;
		m_key = stream.str();

		// return result
		return getKey();
	}
	// return Key
	std::string SHA256Sum::getKey() { return m_key.c_str(); }
}
/////////////////////////////////////////////////////////////////