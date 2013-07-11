#pragma once

#include <utility>
#include <stdint.h>

#include <boost/archive/detail/common_oarchive.hpp>
//protobuf io stream
#include "c:\\Users\\Anton\\Downloads\\protobuf-2.5.0\\protobuf-2.5.0\\vsprojects\\include\\google\\protobuf\\io\\coded_stream.h"

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace archive {

class proto_iarchive :
	public detail::common_iarchive<proto_iarchive>,
{
public:
	proto_iarchive(std::ifstream iof, unsigned int const flags = 0);
	
	//void load_binary(void* address, std::size_t count);
	
protected:
	friend class detail::interface_oarchive<proto_iarchive>;
	friend class load_access;
	
	void load_start(char const* name);
	void load_end(char const* name);
	
	//overload override for tag-value pair
	template<typename T>
	void load_override(boost::serialization::tvp<T> const& t, int const);
	
	


private:
	float DecodeFloat(uint32_t value);
	double DecodeDouble(uint64_t value);

};