#pragma once

#include <utility>
#include <stdint.h>

#include <boost/archive/detail/common_oarchive.hpp>
//protobuf io stream
#include "c:\\Users\\Anton\\Downloads\\protobuf-2.5.0\\protobuf-2.5.0\\vsprojects\\include\\google\\protobuf\\io\\coded_stream.h"

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost{
namespace archive{
		
class proto_oarchive: public detail::common_aorchive<proto_oarchive>
{
	public:
		proto_oarchive(std::ofstream os, unsigned int flags = 0);
		
		void save_binary(void const* address, std::size_t count);

	protected:
		friend class detail::interface_oarchive<proto_oarchive>;
		friend class save_access;
		
		//writing tag and varint type
		void save_start(char const* name);
		//dunno
		void save_end(char const* name);
		
		//overload override for tag-value pair
		template<typename T>
		void save_override(boost::serialization::tvp<T> const& t, int const);
		
		//overload save for basic types with protobuf api
		void save(bool const t);
		void save(char const t);
		void save(signed char const t);
		void save(unsigned char const t);
		//void save(wchar_t const t); 
		//void save(short const t);
		//void save(unsigned short const t);
		void save(int const t);
		void save(unsigned int const t);
		//void save(long const t);
		//void save(unsigned long const t);
		//void save(long long const t);
		//void save(unsigned long long const t);
		void save(float const t);
		void save(double const t);
		void save(std::string const& t);
		template<typename T>
		void save(std::vector<T> const& t)
		//void save(std::wstring const& t);
		
	private:
		uint64_t EncodeDouble(double value);		
		uint32_t EncodeFloat(float value);
};
	
} //archive
} //boost