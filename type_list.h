#include <cstddef>
#include <type_traits>
#include <utility>


template<typename ...args>struct type_node_t;
template<typename ...args>struct type_list_t;

template<typename T,typename ...next_t>struct type_node_t<T,next_t...>
{
	using type = T;
	using next = type_node_t<next_t...>;
};
template<>struct type_node_t<>{};


template<typename iter_t,size_t I>struct type_node_move_t//寻找
{
	using iter = typename type_node_move_t<typename iter_t::next,I-1>::iter;
};
template<typename iter_t>struct type_node_move_t<iter_t,0>//找到
{
	using iter = iter_t;
};


template<bool found,size_t I, class list_t, typename ...args>struct type_list_get_type_t//找指定位置类型
{
	using iter = typename type_node_move_t<typename list_t::begin, I >::iter;
	using type = typename iter::type;
};

template<size_t I, class list_t, typename ...other_t>struct type_list_get_list_t;

template<size_t I, class list_t, typename ...others_t>struct type_list_get_type_t<false,I,list_t,others_t...>//未找到
{
	using type =typename  type_list_get_list_t<I - list_t::size, others_t...>::type;
};

template<size_t I,class list_t,typename ...other_t>struct type_list_get_list_t//为了get
{
	using type = typename type_list_get_type_t<(I < list_t::size), I, list_t, other_t...>::type;//此处因为是size_t，负数不为他，过大疯狂重复减size，直到小于size，然后找到
};
template<class ...list_t>struct type_list_get_t
{
	template<size_t I>struct get//这样设计为了使用
	{
		using type =typename type_list_get_list_t<I,list_t...>::type;
	};
};

template<typename T, typename ...args>struct list_node_pop_front_t
{
	using type = type_list_t<args...>;
};
template<class list_t,class I>struct type_list_get_first_part_t;
template<class get_t, size_t B, class T>struct type_list_builder_t;
template<class get_t, size_t B, size_t ...I>struct type_list_builder_t<get_t, B, std::integer_sequence<size_t, I...>>
{
	using type = type_list_t<typename get_t::template get<B + I>::type...>;
};
template<size_t begin, size_t size, class list_t>struct type_list_slice_t
{
	using type = typename type_list_builder_t<type_list_get_t<list_t>, begin, std::make_index_sequence<size>>::type;
};
template<typename list_t>struct list_node_pop_back_t
{
	using type =typename type_list_slice_t<0,list_t::size-1,list_t>::type;
};
/*template<typename T,typename list_t,size_t ...I>struct type_list_slice_t
{
	using first =typename list_get_first_part_t<list_t,I...>::list;
	using second =typename list_get_first_part_t<list_t::size, list_t,I>::type;
};*/
template<class ...list_t>struct type_list_size_t;
template<class list_t,class ...others_t>struct type_list_size_t<list_t,others_t...>
{
	static constexpr size_t size = list_t::size + type_list_size_t<others_t...>::size;
};
template<>struct type_list_size_t<>
{
	static constexpr size_t size = 0;
};
template<class ...list_t>struct type_list_merge_t
{
	static constexpr size_t size = type_list_size_t<list_t...>::size;
	using type = typename type_list_builder_t<type_list_get_t<list_t...>, 0, std::make_index_sequence<size>>::type;
};
template<typename ...args>struct type_list_t
{

	static constexpr size_t size = sizeof...(args);
	using begin = type_node_t<args...>;
	using end = type_node_t<>;
	using next =typename  type_node_t<args...>::next;
	template<size_t T>using get = typename type_list_get_t<type_list_t<args...>>::template get<T>::type;
	template<typename T>using push_back = type_list_t<args..., T>;
	template<typename T>using push_front = type_list_t<T,args...>;
	using pop_back = typename list_node_pop_back_t<type_list_t<args...>>::type;
	using pop_front = typename list_node_pop_front_t<args...>::type;
	template<size_t begin, size_t size> using slice =typename type_list_slice_t<begin, size, type_list_t<args...>>::type;
	template<size_t I, typename T>using insert =typename type_list_merge_t<slice<0, I>, type_list_t<T>, slice<I, size-I>>::type;
	//template<size_t I, typename T>using insert = typename type_list_merge_t<typename type_list_get_first_part_t<type_list_t<args...>,std::make_index_sequence<I>>::list, type_list_t<T>, slice<I, size - I>>::type;
	template<size_t I>using remove =typename type_list_merge_t<slice<0, I>, slice<I+1, size - I-1>>::type;
};
template<>
struct type_list_t<>
{
	using begin = type_node_t<>;
	using end = type_node_t<>;
	static constexpr size_t size = 0;
	template<class T> using push_back = type_list_t<T>;
	template<class T> using push_front = type_list_t<T>;
	template<class other_t> using cat = other_t;
	template<size_t begin, size_t size> using slice = typename type_list_slice_t<begin,size,type_list_t<>>::type;
	template<size_t I, class T> using insert = typename type_list_slice_t<0,I,type_list_t<T>>::type;
};
