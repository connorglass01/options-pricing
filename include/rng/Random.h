#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>
#include <optional>

namespace Random
{
	std::seed_seq make_seed(std::optional<u_int64_t> userSeed)
	{
		std::seed_seq ss {};

		if (userSeed)
		{	
			return std::seed_seq {static_cast<std::seed_seq::result_type>(*userSeed)};
		}

		std::random_device rd{};

		return std::seed_seq {
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };
	}

    inline std::mt19937 generate(std::optional<u_int64_t> userSeed)
	{
		std::seed_seq ss{ make_seed(userSeed) };

		return std::mt19937{ ss };
	}

    //inline std::mt19937 mt{ generate() };

}

#endif