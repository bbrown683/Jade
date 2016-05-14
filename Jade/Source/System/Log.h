#pragma once

#include "System/File.h"

namespace Jade
{
	namespace System
	{
		class Log
		{
		private:

			File file;

		public:

			// Writes text to the recieving stream.  
			void Write(std::string text);
		};
	}
}
