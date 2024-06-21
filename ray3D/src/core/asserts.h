#pragma once

#include "core/logger.h"

#ifdef _DEBUG

#define R_ASSERT(expression)																	\
		if (expression)																			\
		{																						\
																								\
		}																						\
		else																					\
		{																						\
			ray3D::report_assertion_failure(#expression, "", __FILE__, __LINE__);				\
			__debugbreak();																		\
		}																						\

#define R_ASSERT_MSG(expression, msg)															\
		if (expression)																			\
		{																						\
																								\
		}																						\
		else																					\
		{																						\
			ray3D::report_assertion_failure(#expression, msg, __FILE__, __LINE__);				\
			__debugbreak();																		\
		}																						\

#else
#define R_ASSERT(expression)
#define R_ASSERT_MSG(expression, msg)
#endif // _DEBUG