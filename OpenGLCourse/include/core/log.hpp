// Ad Maiorem Dei Gloriam!
#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <string_view>
#include <source_location>

#ifdef NDEBUG
inline constexpr bool is_debug{ false };
#else
inline constexpr bool is_debug{true};
#endif

namespace Log
{

	constexpr auto kResetEscapeCode = "\033[0m";
	constexpr auto kErrorEscapeCode = "\033[31m\033[1m";
	constexpr auto kLogEscapeCode = "\033[36m\033[1m";

	inline void log(std::string_view message)
	{
		std::cout << kLogEscapeCode << "LOG: " << kResetEscapeCode << message << std::endl;
	}

	inline void log_error(std::string_view message)
	{
		std::cerr << kErrorEscapeCode << "ERROR: " << kResetEscapeCode << message << std::endl;
	}

	inline void log_debug(std::string_view message)
	{
		if constexpr (is_debug) log(message);
	}
	
	inline void log_error_debug(std::string_view message, std::source_location loc = std::source_location::current())
	{
		if constexpr (is_debug) 
			std::cerr 
			<< kErrorEscapeCode 
			<< "ERROR: at [" 
			<< loc.file_name() 
			<< ": " << loc.line() 
			<< '(' << loc.function_name() 
			<< ")]: " << kResetEscapeCode 
			<< message 
			<< std::endl;
	}
}
#endif