#pragma once
#include <stdint.h>

typedef int			i32;
typedef int64_t		i64;
typedef uint32_t	ui32;
typedef uint64_t	ui64;

typedef float		f32;
typedef double		f64;

#define _i32(x)		static_cast<i32>(x)
#define _i64(x)		static_cast<i64>(x)
#define _ui32(x)	static_cast<ui32>(x)
#define _ui64(x)	static_cast<ui64>(x)
#define _f32(x)		static_cast<f32>(x)
#define _f64(x)		static_cast<f64>(x)
