#include<type_traits>
#include<iostream>
#include <algorithm>
#include <functional>
#include <vector>
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


int main()
{
	std::vector<int> a{3,1,5,8};
	std::cout << maxCoins(a, [](const auto& lhs_num, const auto& rhs_num) {return lhs_num > rhs_num ? lhs_num : rhs_num; });
	return 0;
}
