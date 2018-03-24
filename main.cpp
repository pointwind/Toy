#include<type_traits>
#include<iostream>
#include"type_list.h"
int main()
{
	using list1_t = type_list_t<int, long, char, double>;
	using list2_t = list1_t::push_back<std::string>;
	using list3_t = list2_t::push_front<list1_t>;
	using list4_t = list3_t::pop_front;
	using list5_t = list1_t::pop_front;
	using list6_t = list5_t::pop_back;
	using list7_t = type_list_t<int>;
	using list8_t = list1_t::remove<0>;
	using list9_t = list1_t::remove<1>;
	using list10_t = list1_t::remove<3>;
	using list11_t = list1_t::insert<0, float>;
	using list12_t = list1_t::insert<1, float>;
	using list13_t = list1_t::insert<4, float>;

	static_assert(list1_t::size == 4, "no");
	static_assert(std::is_same<list1_t::begin::type, int>::value, "no");
	static_assert(std::is_same<list1_t::begin::next::type, long>::value, "no");
	static_assert(std::is_same<list1_t::begin::next::next::next::next, list1_t::end>::value, "no");
	static_assert(std::is_same<list1_t::get<0>, int>::value, "no");
	static_assert(std::is_same<list1_t::get<1>, long>::value, "no");
	static_assert(std::is_same<list1_t::get<2>, char>::value, "no");
	static_assert(std::is_same<list1_t::get<3>, double>::value, "no");
	static_assert(std::is_same<list2_t::get<4>, std::string>::value, "no");
	static_assert(std::is_same<list3_t::get<1>, int>::value, "no");
	static_assert(std::is_same<list3_t::get<0>, list1_t>::value, "no");
	static_assert(std::is_same<list3_t::begin::type::begin::type, int>::value, "no");
	static_assert(std::is_same<list2_t, list4_t>::value, "no");
	static_assert(std::is_same<list2_t, list4_t>::value, "no");
	static_assert(list5_t::size == 3, "no");
	static_assert(std::is_same<list5_t::begin::type, long>::value, "no");
	static_assert(std::is_same<list5_t::begin::next::next::next, list5_t::end>::value, "no");
	static_assert(list6_t::size == 2, "no");
	static_assert(std::is_same<list6_t::begin::type, long>::value, "no");
	static_assert(std::is_same<list6_t::begin::next::next, list6_t::end>::value, "no");
	static_assert(std::is_same<list8_t, type_list_t<long, char, double>>::value, "no");
	static_assert(std::is_same<list9_t, type_list_t<int, char, double>>::value, "no");
	static_assert(std::is_same<list10_t, type_list_t<int, long, char>>::value, "no");
	static_assert(std::is_same<list11_t, type_list_t<float, int, long, char, double>>::value, "no");
	static_assert(std::is_same<list12_t, type_list_t<int, float, long, char, double>>::value, "no");
	static_assert(std::is_same<list13_t, type_list_t<int, long, char, double, float>>::value, "no");


	return 0;
}
