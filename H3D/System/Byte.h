#pragma once
#include <stdint.h>
#include <vector>

namespace h3d{
	class Byte {
		uint8_t m_byte;
	public:
		inline unsigned char  asUChar()  { return (unsigned char)m_byte; }
		inline char			  asChar()   { return (char)m_byte; }
		inline unsigned int   asUInt()   { return (unsigned int)m_byte; }
		inline int			  asInt()    { return (int)m_byte; }
		inline unsigned short asUShort() { return (unsigned short)m_byte; }
		inline short	      asShort()  { return (short)m_byte; }

		template<typename T>
		T as() {
			return reinterpret_cast<T>(m_byte);
		}

		inline void* rawPtr() { return (void*)&m_byte; }
	};

	class ByteArray {
		std::vector<Byte> m_bytes;
		size_t ssss;
	public:
		inline ByteArray(size_t& size) {m_bytes.resize(size);}
		inline ByteArray(size_t&& size) {m_bytes.resize(size);}

		template<typename T> ByteArray(T& object) {
			size_t size = sizeof object;
			m_bytes.reserve(size);
			memcpy_s((void*)&m_bytes.data()[0], size, (void*)&object, size);
		}
		template<typename T> ByteArray(T* array) {
			size_t size = ssss = sizeof(array);
			memcpy_s(m_bytes.get(), size, &array[0], size);
		}

		inline Byte& operator[](int index) {

		}

		template<typename T>
		T asObject() {
			if (sizeof(T) == sizeof(*m_bytes))
				return reinterpret_cast<T>(*m_bytes);
			else
				return nullptr;
		}
		template<typename T>
		T asObject(size_t offset) {
			return reinterpret_cast<T>(*m_bytes+offset);
		}

		template<typename T>
		T* asArrayPtr() {
			return (void*)&*m_bytes[0];
		}
	};
}