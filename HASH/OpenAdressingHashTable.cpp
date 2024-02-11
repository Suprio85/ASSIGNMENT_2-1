#include <bits/stdc++.h>
#include "HashTable.cpp"
using namespace std;

#define ll unsigned long long
enum class ResulationMethod
{
    CUSTOM_PROBING,
    DOUBLE_HASHING
};

class OpenAdressingHashTable : public HashTable
{
    vector<node *> table;
    vector<bool> wasOccupied;
    ResulationMethod method;
    

    ll doubleHasing(int h, string key, int i)
    {
        return ((h == 1 ? hash1(key) : hash2(key)) + i * auxHash(key)) % this->size;
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

    ll customProbing(int h, string key, int i)
    {
        ll hashValue = 0;
        ll C1 = 5, C2 = 3;
        hashValue = ((h==1 ? hash1(key) : hash2(key)) + C1 * i * auxHash(key) + C2 * i * i) % size;
        return hashValue;
    }

    void doubleHashingInsert(int h, string key, int value)
    {   
        if(1.0*total_nodes/size > 0.5 or probecount/(0.1*size) > 2){
            reHash(expand);
        }

        if(this->total_nodes >= this->size){
           // cout<<"Table is full"<<endl;
            return;
        }

        int i = 0;
        ll index = doubleHasing(h, key, i);
        if(table[index] == nullptr){
            table[index] = new node(key, value);
            wasOccupied[index] = true;
        }
        else{
                this->collsioncount++;
            while (true)
            {
                i++;
                index = doubleHasing(h, key, i);
                if (table[index] == nullptr)
                {
                    table[index] = new node(key, value);
                    wasOccupied[index] = true;
                    break;
                }
               // cout<<"inserting at index: "<<index<<endl;  
            }
        }
        this->total_insert++;
        this->total_nodes++;
    }

    node *doubleHashingFind(int h, string key)
    {
        int i = 0;
        ll index = doubleHasing(h, key, i);

        if (table[index] == nullptr and !wasOccupied[index])
        {
            return nullptr;
        }

        while (true)
        {
            this->probecount++;

            if (table[index]->key == key)
            {
                found++;
                return table[index];
            }
            i++;
            index = doubleHasing(h, key, i);
            if (table[index] == nullptr and !wasOccupied[index])
            {
                break;
            }
        }

        return nullptr;
    }




    node *doubleHashingDelete(int h, string key)
    {
        if(1.0*this->total_nodes/size < 0.25){
            reHash(shrink);
        }
    
        int i = 0;
        node *temp = nullptr;
        while (true)
        {
            int index = doubleHasing(h, key, i);
            if (table[index] == nullptr and !wasOccupied[index])
            {
                return nullptr;
            }
            else if (table[index] != nullptr and table[index]->key == key)
            {
                node *temp = table[index];
                table[index] = nullptr;
                wasOccupied[index] = true;
                break;
            }
            i++;
        }
        this->total_delete++;
        this->total_nodes--;
        return temp;

    }

    void customProbingInsert(int h, string key, int value)
    {  
        if((1.0*total_nodes/size) > 0.5 or probecount/(0.1*size) > 2){
            reHash(expand);
        }
 
        if(this->total_nodes >= this->size){
           // cout<<"Table is full"<<endl;
            return;
        }
         //cout<<"ratio :"<<1.0*this->total_nodes/size<<endl;
        int i = 0;
        ll index = customProbing(h, key, i);
        if(table[index] == nullptr){
            table[index] = new node(key, value);
            wasOccupied[index] = true;
        }
        else{
                this->collsioncount++;
            while (true)
            {
                i++;
                index = customProbing(h, key, i);
                if (table[index] == nullptr)
                {
                    table[index] = new node(key, value);
                    wasOccupied[index] = true;
                    break;
                }
               // cout<<"inserting at index: "<<index<<endl;  
            }
        }
        this->total_insert++;
        this->total_nodes++;
    }

    node *customProbingFind(int h, string key)
    {
         int i = 0;
        ll index = customProbing(h, key, i);

        if (table[index] == nullptr and !wasOccupied[index])
        {
            return nullptr;
        }

        while (true)
        {
            this->probecount++;

            if (table[index]->key == key)
            {
                found++;
                return table[index];
            }
            i++;
            index = customProbing(h, key, i);
            if (table[index] == nullptr and !wasOccupied[index])
            {
                break;
            }
        }

        return nullptr;
    }

    node *customProbingDelete(int h, string key)
    {
         if(1.0*this->total_nodes/size < 0.25){
            reHash(shrink);
        }
        int i = 0;
        node *temp = nullptr;
        while (true)
        {
            int index = customProbing(h, key, i);
            if (table[index] == nullptr and !wasOccupied[index])
            {
                return nullptr;
            }
            else if (table[index] != nullptr and table[index]->key == key)
            {
                node *temp = table[index];
                table[index] = nullptr;
                wasOccupied[index] = true;
                break;
            }
            i++;
        }
        this->total_delete++;
        this->total_nodes--;

        return temp;
    }

    void reHash(int cndtn){

        cout<<"Rehashing"<<endl;
        ll old_size = this->size;
        this->size = cndtn==expand?old_size*2:old_size/2;
        vector<node*> old_table = table;
        table = vector<node*>(this->size, nullptr);
        wasOccupied = vector<bool>(this->size, false);
       // this->collsioncount = 0;
        //this->probecount = 0;
        this->total_nodes = 0;

        
        for(int i = 0; i<old_size; i++){
            if(old_table[i] != nullptr){
                insert(1, old_table[i]->key, old_table[i]->value);
            }
        }

       old_table.clear();
    }

public:
    OpenAdressingHashTable(int size, int c, ResulationMethod method) : HashTable(size, c)
    {

        table = vector<node *>(this->size, nullptr);
        wasOccupied.resize(this->size, false);
        this->method = method;
         this->found = 0;

    }

    void insert(int h,  string key, int value)
    {
        if (this->method == ResulationMethod::DOUBLE_HASHING)
        {
             doubleHashingInsert(h, key, value);
        }
        else
        {   // cout<<"Inserting: "<<key<<endl;
             customProbingInsert(h, key, value);
        }
    }


    node *find(int h, string key)
    {
        if (this->method == ResulationMethod::DOUBLE_HASHING)
        {
            return doubleHashingFind(h, key);
        }
        else
        {
            return customProbingFind(h, key);
        }
    }

    node *deleteNode(int h, string key)
    {
        if (this->method == ResulationMethod::DOUBLE_HASHING)
        {
            return doubleHashingDelete(h, key);
        }
        else
        {
            return customProbingDelete(h, key);
        }
    }

    void debug()
    {
        for (int i = 0; i < this->size; i++)
        {
            if (table[i] != nullptr)
            {
                cout << "Index: " << i << " Key: " << table[i]->key << " Value: " << table[i]->value << endl;
            }

            else
            {
                cout << "Index: " << i << " Key: " << "NULL; " << " Value: " << "NULL" << endl;
            }
        }
        cout<<"Total Nodes: "<<total_nodes<<endl;
        cout << "Probes: " << probecount << " Collisions: " << collsioncount << endl;
    }  
    int found ; 
};

int main(){
     freopen("out1.txt", "w", stdout);
    generator g;
    vector<string> data = g.unique_data();
    


    OpenAdressingHashTable h(5000, 100, ResulationMethod::DOUBLE_HASHING);

    for (int i = 0; i < data.size(); i++)
    {
        h.insert(1, data[i], i);
    }

    for (int i = 0; i < data.size(); i++)
    {
        h.find(1, data[i]);
    }
    // h.debug();
    // // for (int i = 0; i < data.size(); i++)
    // // {
    // //     h.deleteNode(1, data[i]);
    // // }



    // // cout << "Probes: " << endl;
    h.debug();
    cout<<"Total Found: "<<h.found<<endl;

}
