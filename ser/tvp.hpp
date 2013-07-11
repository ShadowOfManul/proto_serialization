#include <boost/serialization/nvp.hpp>
#include <cstdlib>
#include <boost/serialization/version.hpp>

namespace boost{
namespace serialization{

template<class T>
struct tvp:
	public nvp<T>,
	public wrapper_traits<const tvp<T>>
{
	explicit tvp(const int tag_, T & t):
		nvp<T>(to_char(tag_), t)
	{}
		
	const int tag() const{
		//convert tvp tag from const char* in nvp
		//to const in in tvp. works well
		return atoi((*this).name());
	}
	template<class T>                                                          
	struct version                                                 
	{                 
		#define N 0	
		typedef mpl::int_<N> type;                                         
		typedef mpl::integral_c_tag tag;                                   
		BOOST_STATIC_CONSTANT(int, value = version::type::value);          
		BOOST_MPL_ASSERT((                                                 
			boost::mpl::less<                                              
				boost::mpl::int_<N>,                                       
				boost::mpl::int_<256>                                      
			>                                                              
		));                                                                                                                                 
	};  
private:
	//convert int-tag in tvp to const char * for
	//nvp constructor
	const char* to_char(const int tag_)
	{
		char* aux = new char;
		itoa(tag_ ,aux, sizeof(int));
		return aux;
	}

	
};
	
template<class T>
inline
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
const
#endif
tvp< T > make_tvp(const int tag, T & t){
    return tvp< T >(tag, t);
}

// to maintain efficiency and portability, we want to assign
// specific serialization traits to all instances of this wrappers.
// we can't strait forward method below as it depends upon
// Partial Template Specialization and doing so would mean that wrappers
// wouldn't be treated the same on different platforms.  This would
// break archive portability. Leave this here as reminder not to use it !!!
 // #ifndef boost_no_template_partial_specialization

template <class T>
struct implementation_level<tvp< T > >
{
   typedef mpl::integral_c_tag tag;
   typedef mpl::int_<object_serializable> type;
   BOOST_STATIC_CONSTANT(int, value = implementation_level::type::value);
};

// nvp objects are generally created on the stack and are never tracked
template<class T>
struct tracking_level<tvp< T > >
{
   typedef mpl::integral_c_tag tag;
   typedef mpl::int_<track_never> type;
   BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
};


}//serialization
}//boost