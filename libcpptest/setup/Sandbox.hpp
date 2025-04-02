#ifndef LIBCPPTEST_SETUP_SANDBOX_HPP
#define LIBCPPTEST_SETUP_SANDBOX_HPP

#include <libcpplog/logger/Logger.hpp>

#include <filesystem>
#include <string>

namespace cpptest::setup {

	/**
	 * @brief A class handling setup, enter, exit and clean up of a sandbox
	 * 
	 * Upon construction of this object the current working directory is changed
	 * into the sandbox. Upon destruction the current working directory is changed
	 * back to the previous location.
	 * 
	 * @details
	 * Patterns
	 *  - RAII
	 */
	class Sandbox {

	public:
		/**
		 * @brief Constructor to setup a sandbox
		 * 
		 * @param[in] directoryPath The sandbox directory including path
		 * @param[in] logger The logger to be used
		 * @param[in] keep Set to true to prevent clean up of sandbox
		 * @param[in] keepPrevious Set to true to prevent clean up of already existing
		 * sandbox directory
		 */
		explicit Sandbox(
			std::string directoryPath,
			cpplog::logger::Logger& logger,
			bool keep = false,
			bool keepPrevious = false);

		/**
		 * @brief Destructor to clean up a sandbox
		 */
		~Sandbox();

	private:
		const std::string directoryPath; ///< The directory that will be created as sandbox

		const cpplog::logger::Logger& logger; ///< Logger used for log messages

		std::filesystem::path cwd; ///< Stores current working directory to return to after test

		bool keep; ///< Flag whether to keep the sandbox directory or clean it up

		/// @brief Flag whether to keep the previous sandbox directory in case it already exists
		bool keepPrevious; 

	};

}

#endif