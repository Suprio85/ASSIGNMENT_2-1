#include <bits/stdc++.h>
#include "generator.cpp"
#include "hash.cpp"
#include "hash2.cpp"

using namespace std;

#define ll unsigned long long
#define expand 1
#define shrink 2

bool isPrime(ll n)
{
    if (n == 2 || n == 3)
    {
        return true;
    }
    if (n == 1 || n % 2 == 0)
    {
        return false;
    }
    for (ll i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

ll nearby_prime(ll n)
{
    ll prime = n;

    if (prime % 2 == 0)
    {
        prime++;
    }

    while (1)
    {
        if (isPrime(prime))
        {
            return prime;
        }
        prime += 2;
    }
}

ll prime_less_than_size(ll n)
{
    ll prime = n;

    if (prime % 2 == 0)
    {
        prime--;
    }

    while (1)
    {
        if (isPrime(prime))
        {
            return prime;
        }
        prime -= 2;
    }
}

struct node
{
    string key;
    int value;

    node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }

    node()
    {

    }
};

class HashTable{

    public :

   
    ll size;
    int probecount;
    int collsioncount;
    int total_insert;
    int total_delete;
    int total_nodes;
    int c;

     ll hash1(string key)
    {
        //cout << "hash1: " << (ll)murmur3_32(key.c_str(), key.size(), 0) << endl;
        return (ll)murmur3_32(key.c_str(), key.size(), 0);
    }

    ll hash2(string key)
    {
       // cout << "hash2: " << (ll)fnv1a_hash(key.c_str(), key.size()) << endl;
        return (ll)fnv1a_hash(key.c_str(), key.size());
    }


     HashTable(int size, int c)
    {   this->total_nodes = 0;
        this->size = nearby_prime(size);
        this->probecount = 0;
        this->collsioncount = 0;
        this->total_insert = 0;
        this->total_delete = 0;
        this->c = c;
    }


};