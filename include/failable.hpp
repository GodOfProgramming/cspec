#pragma once
#include <string>

#include "misc.hpp"

namespace cspec
{
	class Failable
	{
	public:
		static bool ItFailed;

	protected:
		Failable() = default;
		~Failable() = default;

		template <typename... Args>
		void checkResult(bool res, std::string failure_message, Args&&... args);

		const char* mFile;
		int mLine;
	};

	template <typename... Args>
	void Failable::checkResult(bool res, std::string failure_message, Args&&... args)
	{
		if (!res) {
			capture('\n', mFile, " (", mLine, "): ", "\x1b[31m", "Evaluation Failed\n\t", "\x1b[m", failure_message, '\n');
			if (sizeof...(args) > 0) {
				capture("\tMessage: ", args..., '\n');
			}
			ItFailed = true;
		}
	}
}  // namespace cspec

