#include<type_traits>
#include<iostream>
//#include<boost/test/unit_test.hpp>
#include <algorithm>
#include <functional>
#include <vector>
#include <ctime>
#include <Windows.h>
#include<io.h>
#include<string>
#include<fstream>
#include<optional>

template<typename T>auto create(bool b,const T& value)
{
	return b ? std::optional<T>{value} : std::nullopt;
}
template<typename T, typename most = decltype(std::max<T>) >auto maxCoins( std::vector<T>& nums, most get_most = most())
{
	nums.insert(nums.begin(), 1);
	nums.push_back(1);
	std::vector<std::vector<T>> dp(nums.size(), std::vector<T>(nums.size()));
	const size_t len = nums.size() - 2;


	for (size_t i = 1; i <= len; ++i) {    //从1个气球开始
		for (size_t left = 1; left <= len - i + 1; ++left) {    //获得当前left与right下标。
			auto right = left + i - 1;
			for (auto k = left; k <= left + i - 1; ++k) {       //计算dp[left][right]

				dp[left][right] = get_most( create(static_cast<bool>(dp[left][right]),dp[left][right]).
										   value_or(dp[left][k - 1] + dp[k + 1][right] + nums[left - 1] * nums[k] * nums[right + 1]),
										   dp[left][k - 1] + dp[k + 1][right] + nums[left - 1] * nums[k] * nums[right + 1]);

			}
		}
	}
	return dp[1][len];
}

void test(std::vector<int>& lhs)
{
	LARGE_INTEGER t1, t2, tc;                                 
	QueryPerformanceFrequency(&tc);                           
	QueryPerformanceCounter(&t1);         
	//std::cout<< maxCoins(lhs, [](const auto& lhs_num, const auto& rhs_num) {return lhs_num > rhs_num ? lhs_num : rhs_num; });
	//std::cout << maxCoins(lhs);
	QueryPerformanceCounter(&t2);                             
	printf("  numbers cost : %fms\n", (t2.QuadPart - t1.QuadPart)*1e3 / tc.QuadPart);   
}


int main()
{
	std::vector<int> a{3,1,5,8};
	std::cout << maxCoins(a, [](const auto& lhs_num, const auto& rhs_num) {return lhs_num > rhs_num ? lhs_num : rhs_num; });
	/*using list1_t = type_list_t<int, long, char, double>;
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
	static_assert(std::is_same<list13_t, type_list_t<int, long, char, double, float>>::value, "no");*/
	/*RB_tree<char> tree;
	Node<char> a;
	Node<char> b;
	Node<char> c;
	Node<char> d;
	a.number = 0;
	b.number = 1;
	c.number = 2;
	d.number = 3;
	Node<char> e;
	Node<char> h;
	Node<char> g;
	Node<char> f;
	e.number = 4;
	h.number = 5;
	g.number = 6;
	f.number = 7;


	tree.insert_node(&a);
	tree.insert_node(&b);
	tree.insert_node(&c);
	tree.insert_node(&d);
	tree.insert_node(&e);
	tree.insert_node(&h);
	tree.insert_node(&g);
	tree.insert_node(&f);

	std::cout << "pre_order : " << std::endl;
	tree.display(tree.root);
	std::cout << "in_order print : " << std::endl;
	tree.or_display(tree.root);
	std::cout << "post_order print : " << std::endl;
	tree.la_display(tree.root);
	std::cout << "������� :  " << std::endl;
	tree.layer_display(tree.root);*/

	return 0;
}
