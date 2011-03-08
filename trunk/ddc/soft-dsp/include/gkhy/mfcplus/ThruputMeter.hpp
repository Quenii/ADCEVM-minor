#pragma once

namespace gkhy
{

	namespace mfcplus
	{
		struct AFX_EXT_CLASS MeterValue
		{
			UINT nStartTime;
			UINT nNowTime;

			UINT64 nTotal;

			UINT nAvgThruput;
			UINT nInstThruput;
		};

		class AFX_EXT_CLASS CThruputMeter
		{
		public:
			CThruputMeter(void);
			virtual ~CThruputMeter(void);
		public:
			enum UNIT
			{
				UNIT_B,
				UNIT_KB,
				UNIT_MB
			};

		public:
			/**
			* @param nInstTimeval - timeval(in ms) used to calculate inst thruput.
			*/
			void SetUp(UNIT unit, clock_t nInstTimeval);
			void Reset(void);

			void GetMeter(MeterValue& m);

			void Flow(int nCount);

		private:
			UNIT m_Unit;
			UINT64 m_nTotalCount;		//total count

			UINT m_nInstCount;          //instant count
			clock_t m_nInstTimeval;		//instant time value
			UINT m_nAvgThruput;			//average throughput
			UINT m_nInstThruput;		// instant throughput

			clock_t m_Start;            //start time
			clock_t m_JustNow;			//last time
			clock_t m_Now;				//current time
		};


	}

}

