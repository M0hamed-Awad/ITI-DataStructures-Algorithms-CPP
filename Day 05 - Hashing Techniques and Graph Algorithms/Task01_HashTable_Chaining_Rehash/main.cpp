#include <iostream>
#include<vector>
#include<list> /// STL : Double Linked List
#include<functional>
#include<algorithm>

using namespace std;

struct Employee
{
    int id;
    string name;
    int age;
    float salary;
};

ostream& operator<<(ostream& os, const Employee& e)
{
    os << "{ID:" << e.id
       << ", Name:" << e.name
       << ", Age:" << e.age
       << ", Salary:" << e.salary << "}";
    return os;
}

template<class KeyType, class ValueType>
class HashEntry
{
    KeyType Key ;  /// int
    ValueType Value ; ///Employee

public :
    HashEntry(KeyType _key, ValueType _value): Key(_key), Value(_value) {}

    KeyType getKey() const
    {
        return Key;
    }

    ValueType getValue() const
    {
        return Value;
    }
};

template<class KeyType, class ValueType>
class HashTable
{
    vector<list<HashEntry<KeyType, ValueType>>> table;
    int currentSize;

public:
    explicit HashTable (int size = 101) : table(size), currentSize(0) {}

    bool isEmpty() const;

    bool contains (const KeyType & x) const;

    bool insertItem(const KeyType& X, const ValueType& Y);
    bool removeItem(const KeyType& X);
    ValueType searchTable(const KeyType& key) const;

    void printTable() const;

    void makeEmpty ();
    void rehash ();

protected:
    int hashFunction (const KeyType& key)const;
};

template<class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::hashFunction (const KeyType& key)const
{
    std::hash<KeyType> hashObject;
    return  hashObject(key) %  table.size();
}

template<class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::isEmpty() const
{
    return currentSize == 0;
}

template<class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::contains(const KeyType& key) const
{
    int hashValue = hashFunction(key); // The Bucket Index

    ///O(1) Const Time
    const auto& bucket = table[hashValue];  /// Double Linked List , List key May be in it
    // list<MapEntry<KeyType,ValueType>>& bucket = table[hashValue];

    ///Manually Loop through each double Linked List Nodes , till key is found - O(N)
    auto bItr = bucket.begin();

    for(auto bItr = bucket.begin(); bItr != bucket.end(); bItr++)
        if (bItr->getKey() == key) return true;

    return false;
}

template<class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::insertItem(const KeyType& key, const ValueType& value)
{
    if (contains(key)) return false; // No duplicates allowed

    int hashValue = hashFunction(key); // To which Bucket Index

    table[hashValue].emplace_back(key, value); // Construct the entry and push it into the correct bucket

    currentSize++;

    if (currentSize > table.size() * 0.75) rehash();
    return true;
}

template<class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::removeItem(const KeyType& key)
{
    // 1- Find the bucket of Interest (Bucket Index)
    int hashValue = hashFunction(key); // To which Bucket Index

    // 2. Get a reference to the specific bucket
    auto& bucket = table[hashValue];

    // 3. Search using an iterator (Manual)
    for (auto bItr = bucket.begin(); bItr != bucket.end(); bItr++)
    {
        // Look inside the Entry to check the Key
        if (bItr->getKey() == key)
        {
            bucket.erase(bItr); // Remove the element at this position
            currentSize--;
            return true;
        }
    }

    return false;
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::makeEmpty()
{
    for (auto& bucket : table) bucket.clear();
    currentSize = 0;
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::rehash()
{
    /// Size *2 , Rehash Existing Objects
    // 1. Keep a reference to the old table
    vector<list<HashEntry<KeyType, ValueType>>> oldTable = table;

    // 2. Resize the main table to double
    table.resize(oldTable.size() * 2);

    // 3. Clear the new table
    makeEmpty();

    // 4. Re-insert items (they will get new hash positions)
    for (auto& bucket : oldTable)
    {
        for (auto& entry : bucket) insertItem(entry.getKey(), entry.getValue());
    }
}


template<class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::searchTable(const KeyType& key) const
{
    /*Basic Function of Hash Table*/

    ///1. Compute Hash Value for Key : Index
    int index = hashFunction(key);

    ///2. Access Bucket
    const auto& bucket = table[index];

    ///3. Search Linearly for Key
    for (auto bItr = bucket.begin(); bItr != bucket.end(); ++bItr)
    {
        ///4. if Found return Value
        if (bItr->getKey() == key)
        {
            return bItr->getValue(); // Found it!
        }
    }

    // If key doesn't exist.
    throw std::runtime_error("Key not found in Hash Table");
}

template<class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::printTable() const
{
    for(int i = 0; i < table.size(); i++)
    {
        cout << "Bucket No. " << i << " is ===> ";
        for(auto bItr = table[i].begin(); bItr != table[i].end(); bItr++)
        {
            cout << "[" << bItr->getKey() << ":" << bItr->getValue() << "] ";
        }
        cout << endl;
    }
}

int main()
{
    HashTable<int, Employee> employees(5);

    cout << "--- Initial State ---" << endl;

    employees.insertItem(101, {101, "Alice",   30, 5000.0f});
    employees.insertItem(102, {102, "Bob",     25, 4200.0f});
    employees.insertItem(103, {103, "Charlie", 28, 4600.0f});

    employees.printTable();
    cout << "Current Size: 3 | Buckets: 5" << endl;

    // 2. This insertion should trigger a REHASH
    // 4 items > (5 * 0.75)
    cout << "\n--- Adding 4th & 5th items (Should trigger Rehash) ---" << endl;

    employees.insertItem(104, {104, "David",  35, 6000.0f});
    employees.insertItem(105, {105, "Eve",    29, 4800.0f});

    employees.printTable();

    // 3. Verify data integrity after rehash
    cout << "\n--- Verification ---" << endl;

    Employee e1 = employees.searchTable(101);
    cout << "ID 101 -> " << e1.name << ", Salary: " << e1.salary << endl;

    Employee e2 = employees.searchTable(105);
    cout << "ID 105 -> " << e2.name << ", Salary: " << e2.salary << endl;

    // 4. Test removal
    cout << "\n--- Removing Bob (102) ---" << endl;
    employees.removeItem(102);

    employees.printTable();

    return 0;
}
