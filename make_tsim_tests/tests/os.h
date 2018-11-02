#if !defined(OS_H_)
#   define OS_H_
#   include "types.h"

struct Os
{
	struct Time
	{
		typedef u32 Type;

		static Type current()
		{
			return MockTime1::getTime();
		}

		static Type currentSec()
		{
			return current() / MockTime1::getTicksInSecond();
		}

		static Type ticks(f32 t_s)
		{
			return Type(t_s * f32(MockTime1::getTicksInSecond()));
		}

		static void delay(Type dt)
		{
			bool init = false;
			Type t0;
			Type t;
			do
			{
				t = current();
				if (!init)
				{
					init = true;
					t0 = t;
				}
			}
			while (t - t0 < dt);
		}

		class MockTime1
		{
		public:

			static u32 getTime() {
				return time;
			}

			static void setTime(u32 newTime) {
				time = newTime;
			}

			static u32 getTicksInSecond() {
				return ticksInSecond;
			}

		private:
			static u32 time;
			static const u32 ticksInSecond = 1000;
		};

	};
};

#endif  // OS_H_
