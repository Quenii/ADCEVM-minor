#pragma once

#ifdef MFCMINUS_EXPORTS
#	define MFCMINUS_API __declspec(dllexport)
#else
#	define MFCMINUS_API __declspec(dllimport)
#endif

namespace gkhy
{
	namespace MfcMinus
	{
		template <typename T>
		inline const T &qMin(const T &a, const T &b)
		{
			if (a < b) return a; return b;
		}

		template <typename T> const T &qMax(const T &a, const T &b) 
		{ 
			if (a < b) return b; return a;
		}
	}
}
