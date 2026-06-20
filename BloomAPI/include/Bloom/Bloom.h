#pragma once

#ifdef BLOOM_EXPORT
#define BLOOM_API __declspec(dllexport)
#define BLOOM_GLOBAL BLOOM_API inline
#else
#define BLOOM_API __declspec(dllimport)
#define BLOOM_GLOBAL BLOOM_API extern
#endif