#include <bits/stdc++.h>
// #include "generator.cpp"
#include "HashTable.cpp"
// #include "hash.cpp"
// #include "hash2.cpp"

using namespace std;

#define ll unsigned long long
// #define expand 1
// #define shrink 2


class ChainingHashTable : public HashTable
{
    vector<node *> *table;  
    int max_chain_length;

   

    ll doubleHasing(ll (*hash)(string), string key, int i)
    {

        return (hash(key) + i * auxHash(key)) % size;
    }

    ll doubleHasing(string key, int i)
    {

        return (hash1(key) + i * auxHash(key)) % size;
    }

    ll auxHash(string key)
    {
        int hashValue = 0;
        ll R = prime_less_than_size(this->size);

        for (int i = 0; i < key.size(); i++)
        {
            hashValue += (int)key[i];
        }

        hashValue = R - (hashValue % R);
        return (ll)hashValue;
    }

    ll customProbing(string key, int i)
    {

        ll hashValue = 0;
        int C1 = 3079, C2 = 12289;
        hashValue = (hash1(key) + C1 * i * auxHash(key) + C2 * i * i) % size;
        return hashValue;
    }

    ll customProbing(ll (*hash)(string), string key, int i)
    {
        ll hashValue = 0;
        int C1 = 3079, C2 = 12289;
        hashValue = (hash(key) + C1 * i * auxHash(key) + C2 * i * i) % size;
        return hashValue;
    }

public:
    ChainingHashTable(ll size, int c) : HashTable(size, c)
    {
        this->table = new vector<node *>[this->size];
        this->max_chain_length = 0;
    }
    
    void debug()
    {
        cout << "debugging After Inserting : " << endl;
        cout << "table_size: " << size << endl;
        int cnt = 0;
        for (int i = 0; i < size; i++)
        {
      //      cout << "Index: " << i << " ";
            for (int j = 0; j < table[i].size(); j++)
            {
                if (table[i][j] != NULL)
                {
                    cout << table[i][j]->key << " " << table[i][j]->value << " ->";
                    if (j > 0)
                    {
                        cnt++;
                    }
                }
            }
            if (cnt > 0)
            {
                cout << "Collisions: " << cnt << endl;
            }
            cnt = 0;
            cout << endl;
            cout<<"debugging"<<endl;
        }
        cout << "Probes: " << probecount << " Collisions: " << collsioncount << "max_chain_length: " << max_chain_length << endl;

    }

    void insertChaining(string key, int value)
    {

        if (total_insert % 100 == 0 and this->max_chain_length > this->c)
        {
            reHash(expand);
        }

        ll index = hash1(key) % this->size;
        if (table[index].size() == 0)
        {
            table[index].push_back(new node(key, value));
        }
        else
        {
            table[index].push_back(new node(key, value));
            collsioncount++;
        }

        if (table[index].size() > max_chain_length)
        {
            max_chain_length = table[index].size();
        }
        total_insert++;
    }

    node *searchChaining(string key)
    {
        ll index = hash1(key) % this->size;

        if (table[index].size() == 1)
        {
           found++;
            probecount++;
            return table[index][0];
        }

        for (int i = 0; i < table[index].size(); i++)
        {
            probecount++;
            if (table[index][i]->key == key)
            {   found++;
                return table[index][i];
            }
        }
        return NULL;
    }

    node *deleteChaining(string key)
    {
        if(total_delete%100==0 and this->max_chain_length<(int)0.8*this->c){
            reHash(shrink);
        }

        ll index = hash1(key) % this->size;
        for (int i = 0; i < table[index].size(); i++)
        {
            if (table[index][i]->key == key)
            {
                node *temp = table[index][i];
                table[index].erase(table[index].begin() + i);
                return temp;
            }
        }
        total_delete++;
        return NULL;
    }

   

    void insert(string key, int value)
    {

        insertChaining(key, value);
    }

    void reHash(int cndn)
    {  
        cout<<"Rehashing"<<endl;
        ll old_size = this->size;
        this->size = nearby_prime((ll)(cndn == expand ? this->size * 2 : this->size / 2));
        int oldCollisions = collsioncount;
        vector<node *> *oldTable = table;
        this->table = new vector<node *>[this->size];
        this->max_chain_length=0;
        this->collsioncount = 0;
        this->probecount = 0;
         this->total_nodes = 0;

        for (int i = 0; i < old_size; i++)
        {

            if (oldTable[i].size() > 0)
            {
                for (int j = 0; j < oldTable[i].size(); j++)
                {
                    insertChaining(oldTable[i][j]->key, oldTable[i][j]->value);
                    
                }
            }
        }
    }

    int found = 0;
};

int main()
{
    freopen("out.txt", "w", stdout);
    generator g;
    vector<string> data = g.unique_data();

    ChainingHashTable h(10000, 10);

    for (int i = 0; i < data.size(); i++)
    {
        h.insertChaining(data[i], i + 1);
    }
    cout << "Probes: " << endl;
    
    for(int i=0;i<data.size();i++){
        h.searchChaining(data[i]);
        //cout<<h.searchChaining(data[i])->key<<" "<<h.probecount<<endl;
    }
    h.debug();
    cout<<"Total Nodes: "<<h.total_nodes<<endl; 
    cout<<"Total Found: "<<h.found<<endl; 

    for(int i=0;i<data.size();i++){
        h.deleteChaining(data[i]);
    }

    h.debug();



    return 0;
}
