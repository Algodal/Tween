//Copyright (C) 2023 Alrick Grandison, Algodal™

#define TW_VERSION "0.1.0"
enum
{
TW_MAJOR_VERSION = 0,
TW_MAJOR_MINOR   = 1,
TW_MAJOR_PATCH   = 0,
};

#define TW_MAKE_API_VERSION(variant, major, minor, patch) \
    ((((uint32_t)(variant)) << 24) | (((uint32_t)(major)) << 16) | (((uint32_t)(minor)) << 8) | ((uint32_t)(patch)))

#define TW_API_VERSION TW_MAKE_API_VERSION(0, TW_MAJOR_VERSION, TW_MAJOR_MINOR, TW_MAJOR_PATCH)





