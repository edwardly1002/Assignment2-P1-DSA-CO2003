template <class K, class V>
class Entry {
public:
    K key;
    V value;

    Entry(K key, V value) : key(key), value(value) {}
};
