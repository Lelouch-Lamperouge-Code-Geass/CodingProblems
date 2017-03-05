class LFUCache {
public:
    LFUCache(int capacity) : m_capacity(capacity), m_min_frequency(0), m_size(0) {
        
    }
    
    int get(int key) {
        if (m_key_to_list_position.count(key) == 0) return -1; // cache miss
        
        std::size_t frequency = m_key_to_value_freq[key].second;
        m_frequency_to_keys[frequency].erase(m_key_to_list_position[key]);
        
        std::size_t new_frequency = frequency + 1; // increase frequency of this key
        m_key_to_value_freq[key].second = new_frequency; 
        m_frequency_to_keys[new_frequency].push_back(key);
        
        m_key_to_list_position[key] = --m_frequency_to_keys[new_frequency].end();
        
        if (m_frequency_to_keys[m_min_frequency].size() == 0) {
            ++ m_min_frequency;
        }
        
        return m_key_to_value_freq[key].first;
    }
    
    void put(int key, int value) {
        if (m_capacity == 0) return; 

        if (m_key_to_value_freq.count(key) != 0) {
            get(key);
            m_key_to_value_freq[key].first = value;
        } else {
            if (m_size == m_capacity) {
                int delete_key = m_frequency_to_keys[m_min_frequency].front();
                erase(delete_key);
            }
            
            m_key_to_value_freq[key] = {value, 1};
            m_frequency_to_keys[1].push_back(key);
            m_key_to_list_position[key] = --m_frequency_to_keys[1].end();
            m_min_frequency = 1;
            ++ m_size;
        }
    }
    
    void erase(int key) {
        if (m_key_to_value_freq.count(key) != 0 ) {
            m_key_to_value_freq.erase(key);
            m_key_to_list_position.erase(key);
            m_frequency_to_keys[m_min_frequency].pop_front();
            -- m_size;
        }
    }
private:
    std::size_t m_capacity;
    std::size_t m_size;
    std::size_t m_min_frequency;
    unordered_map<int, pair<int, std::size_t> > m_key_to_value_freq; //key to {value,freq};
    unordered_map<std::size_t, list<int>>  m_frequency_to_keys;  //frequency to key list;
    unordered_map<int, list<int>::iterator> m_key_to_list_position; //key to list iterator;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
