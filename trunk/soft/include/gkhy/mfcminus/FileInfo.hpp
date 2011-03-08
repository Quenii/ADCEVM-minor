#pragma  once
#include "gkhy/mfcminus/mfcminus_global.hpp"
#include <string>

namespace gkhy
{
	namespace MfcMinus
	{
		class FileInfo
		{
		public:
			FileInfo(const std::string filePath);

		public:
			// including the extension
			std::string fileName();

		private:
			std::string m_filePath;
		};
	}
}

