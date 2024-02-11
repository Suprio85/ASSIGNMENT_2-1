#include <cstdint>
#include<bits/stdc++.h>

constexpr uint32_t FNV_PRIME = 16777619;
constexpr uint32_t FNV_OFFSET_BASIS = 2166136261;

uint32_t fnv1a_hash(const void* key, size_t len) {
    const uint8_t* data = static_cast<const uint8_t*>(key);
    uint32_t hash = FNV_OFFSET_BASIS;

    for (size_t i = 0; i < len; i++) {
        hash ^= data[i];
        hash *= FNV_PRIME;
    }

    return hash;
}

// int main() {
//     const char* key = "Hello";
//     uint32_t hash = fnv1a_hash(key, strlen(key));

//     std::cout << "FNV-1a Hash: " << hash << std::endl;

//     return 0;
// }