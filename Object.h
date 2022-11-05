/*
	Object/Map Datatype
	by x-f2 (https://github.com/x-f2)
	Copyright 2022
*/
#include <vector>
#include <algorithm>

/*
	Object class. Acts as an alternate, less
	convoluted version of std::Map.
*/
template <typename Key, typename Value>
class Object {
private:
	std::vector<Key> keys;
	std::vector<Value> values;
public:
	/*
		Default constructor. (does nothing)
		PRE:
		POST:
	*/
	Object() {}

	/*
		Destructor. (does nothing)
		PRE:
		POST:
	*/
	~Object() {}

	/*
		Constructor which sets the first key/value pair.
		PRE: key and value are defined
		POST: key/value pair are inserted
	*/
	Object(Key key, Value value) {
		insert(key, value);
	}

	/*
		Inserts a key/value pair into the object.
		PRE: key and value are defined
		POST: key/value pair are inserted
	*/
	void insert(Key key, Value value) {
		keys.push_back(key);
		values.push_back(value);
	}

	/*
		Gets a value from a key/value pair given the key.
		PRE: key is defined
		POST: Value is given if the key exists
		@return Value from the key/value pair
	*/
	Value get(Key key) {
		typename std::vector<Key>::iterator keyPtr;
		keyPtr = std::find(keys.begin(), keys.end(), key);
		size_t index = std::distance(keys.begin(), keyPtr);
		return values.at(index);
	}

	/*
		Removes a key/value pair given its key.
		PRE: key is defined
		POST: the key/value pair is removed if it exists
		@return Whether the removal was successful
	*/
	bool remove(Key key) {
		typename std::vector<Key>::iterator keyPtr;
		typename std::vector<Value>::iterator valPtr;
		keyPtr = std::find(keys.begin(), keys.end(), key);
		size_t index = std::distance(keys.begin(), keyPtr);
		valPtr = values.begin();
		std::advance(valPtr, index);
		if (keyPtr != keys.end() && valPtr != values.end()) {
			keys.erase(keyPtr);
			values.erase(valPtr);
			return true;
		}
		return false;
	}

	/*
		Applies the given lambda function to each
		key/value pair that exists in the object.
		PRE: the given function has the correct parameters
		POST: The function is called with the keys and
			values passed as arguments.
	*/
	template <typename Return_type>
	void forEach(Return_type (*mutator)(Key&, Value&)) {
		size_t size = keys.size();
		for (size_t i = 0; i < size; i++) {
			mutator(keys.at(i), values.at(i));
		}
	}
	/*
		An overload of the previous method to allow
		non-pass-by-reference lambdas.
		PRE: the given function has the correct parameters
		POST: The function is called with the keys and
			values passed as arguments.
	*/
	template <typename Return_type>
	void forEach(Return_type (*accessor)(Key, Value)) {
		size_t size = keys.size();
		for (size_t i = 0; i < size; i++) {
			accessor(keys.at(i), values.at(i));
		}
	}
};
