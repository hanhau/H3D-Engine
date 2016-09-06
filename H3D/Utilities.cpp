#include "Utilities.hpp"
#include <string>
/////////////////////////////////////////////////////////////////
H3D_API h3d::tagDebugstream h3d::Debugstream;
H3D_API bool h3d::DebugMode;
/////////////////////////////////////////////////////////////////
//	Writing in the file with "<<" operator
template<typename T>
std::ostream& h3d::tagDebugstream::operator<<(T stream)
{
	file_stream << stream;
	return (std::ostream)0;
}
/////////////////////////////////////////////////////////////////
//	Instances of Operator
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(int);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(unsigned int);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(float);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(double);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(char*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(const char*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(char const*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(const char[]);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(std::string);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(void*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<<(std::streambuf*);
template H3D_API std::ostream& h3d::tagDebugstream::operator<< (std::ostream& (*pf)(std::ostream&));
template H3D_API std::ostream& h3d::tagDebugstream::operator<< (std::ios& (*pf)(std::ios&));
template H3D_API std::ostream& h3d::tagDebugstream::operator<< (std::ios_base& (*pf)(std::ios_base&));
/////////////////////////////////////////////////////////////////
//	Closing/Opening file
bool h3d::tagDebugstream::open(const char* filename, std::ios_base::openmode mode)
{
	if (file_stream.is_open()) file_stream.close();
	file_stream.open(filename, mode | std::ios::ate);
	if (!file_stream.good()) return false;
	file_stream.rdbuf()->pubsetbuf(0, 0);
	return true;
}
void h3d::tagDebugstream::close()
{
	file_stream.close();
}
/////////////////////////////////////////////////////////////////