#pragma once

namespace gkhy
{
	namespace mfcplus
	{
		template <typename T>
		inline 	const T &qMin(const T &a, const T &b)
		{
			if (a < b) return a; return b; 
		}
		template <typename T>
		inline const T &qMax(const T &a, const T &b) 
		{
			if (a < b) return b; return a; 
		}

	}
}