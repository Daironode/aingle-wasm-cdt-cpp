/**
 *  @file
 *  @copyright defined in ont/LICENSE
 */
#pragma once
namespace aingle {
struct unsigned_int {
    unsigned_int( uint32_t v = 0 ):value(v){}

    template<typename T>
    unsigned_int( T v ):value(v){}

    template<typename T>
    operator T()const { return static_cast<T>(value); }

    unsigned_int& operator=( uint32_t v ) { value = v; return *this; }

    uint32_t value;

    friend bool operator==( const unsigned_int& i, const uint32_t& v )     { return i.value == v; }

    friend bool operator==( const uint32_t& i, const unsigned_int& v )     { return i       == v.value; }

    friend bool operator==( const unsigned_int& i, const unsigned_int& v ) { return i.value == v.value; }

    friend bool operator!=( const unsigned_int& i, const uint32_t& v )     { return i.value != v; }

    friend bool operator!=( const uint32_t& i, const unsigned_int& v )     { return i       != v.value; }

    friend bool operator!=( const unsigned_int& i, const unsigned_int& v ) { return i.value != v.value; }

    friend bool operator<( const unsigned_int& i, const uint32_t& v )      { return i.value < v; }

    friend bool operator<( const uint32_t& i, const unsigned_int& v )      { return i       < v.value; }

    friend bool operator<( const unsigned_int& i, const unsigned_int& v )  { return i.value < v.value; }

    friend bool operator>=( const unsigned_int& i, const uint32_t& v )     { return i.value >= v; }

    friend bool operator>=( const uint32_t& i, const unsigned_int& v )     { return i       >= v.value; }

    friend bool operator>=( const unsigned_int& i, const unsigned_int& v ) { return i.value >= v.value; }

    template<typename DataStream>
    friend DataStream& operator << ( DataStream& ds, const unsigned_int& v ){
	uint64_t val = v.value;
	WriteVarUint(ds, val);
	return ds;
    }

    template<typename DataStream>
    friend DataStream& operator >> ( DataStream& ds, unsigned_int& vi ){
	uint64_t val = ReadVarUint(ds); 
	vi.value = uint32_t(val);
	return ds;
    }
};

/**
 * Variable Length Signed Integer. This provides more efficient serialization of 32-bit signed int.
 * It serializes a 32-bit signed integer in as few bytes as possible.
 *
 * @note `varint32' is signed and uses [Zig-Zag encoding](https://developers.google.com/protocol-buffers/docs/encoding#signed-integers)
 */
struct signed_int {
    /**
     * Construct a new signed int object
     *
     * @param v - Source
     */
    signed_int( int32_t v = 0 ):value(v){}

    /**
     * Convert signed_int to primitive 32-bit signed integer
     *
     * @return int32_t - The converted result
     */
    operator int32_t()const { return value; }


    /**
     * Assign an object that is convertible to int32_t
     *
     * @tparam T - Type of the assignment object
     * @param v - Source
     * @return unsigned_int& - Reference to this object
     */
    template<typename T>
    signed_int& operator=( const T& v ) { value = v; return *this; }

    /**
     * Increment operator
     *
     * @return signed_int - New signed_int with value incremented from the current object's value
     */
    signed_int operator++(int) { return value++; }

    /**
     * Increment operator
     *
     * @return signed_int - Reference to current object
     */
    signed_int& operator++(){ ++value; return *this; }

    /**
     * Contained value
     */
    int32_t value;

    /**
     * Check equality between a signed_int object and 32-bit integer
     *
     * @param i - signed_int object to compare
     * @param v - 32-bit integer to compare
     * @return true - if equal
     * @return false - otherwise
     */
    friend bool operator==( const signed_int& i, const int32_t& v )    { return i.value == v; }

    /**
     * Check equality between 32-bit integer and  a signed_int object
     *
     * @param i - 32-bit integer to compare
     * @param v - signed_int object to compare
     * @return true - if equal
     * @return false - otherwise
     */
    friend bool operator==( const int32_t& i, const signed_int& v )    { return i       == v.value; }

    /**
     * Check equality between two signed_int objects
     *
     * @param i - First signed_int object to compare
     * @param v - Second signed_int object to compare
     * @return true - if equal
     * @return false - otherwise
     */
    friend bool operator==( const signed_int& i, const signed_int& v ) { return i.value == v.value; }


    /**
     * Check inequality between a signed_int object and 32-bit integer
     *
     * @param i - signed_int object to compare
     * @param v - 32-bit integer to compare
     * @return true - if inequal
     * @return false - otherwise
     */
    friend bool operator!=( const signed_int& i, const int32_t& v )    { return i.value != v; }

    /**
     * Check inequality between 32-bit integer and  a signed_int object
     *
     * @param i - 32-bit integer to compare
     * @param v - signed_int object to compare
     * @return true - if unequal
     * @return false - otherwise
     */
    friend bool operator!=( const int32_t& i, const signed_int& v )    { return i       != v.value; }

    /**
     * Check inequality between two signed_int objects
     *
     * @param i - First signed_int object to compare
     * @param v - Second signed_int object to compare
     * @return true - if inequal
     * @return false - otherwise
     */
    friend bool operator!=( const signed_int& i, const signed_int& v ) { return i.value != v.value; }

    /**
     * Check if the given signed_int object is less than the given 32-bit integer
     *
     * @param i - signed_int object to compare
     * @param v - 32-bit integer to compare
     * @return true - if i less than v
     * @return false - otherwise
     */
    friend bool operator<( const signed_int& i, const int32_t& v )     { return i.value < v; }

    /**
     * Check if the given 32-bit integer is less than the given signed_int object
     *
     * @param i - 32-bit integer to compare
     * @param v - signed_int object to compare
     * @return true -  if i less than v
     * @return false - otherwise
     */
    friend bool operator<( const int32_t& i, const signed_int& v )     { return i       < v.value; }

    /**
     * Check if the first given signed_int is less than the second given signed_int object
     *
     * @param i - First signed_int object to compare
     * @param v - Second signed_int object to compare
     * @return true -  if i less than v
     * @return false - otherwise
     */
    friend bool operator<( const signed_int& i, const signed_int& v )  { return i.value < v.value; }


    /**
     * Check if the given signed_int object is greater or equal to the given 32-bit integer
     *
     * @param i - signed_int object to compare
     * @param v - 32-bit integer to compare
     * @return true - if i is greater or equal to v
     * @return false - otherwise
     */
    friend bool operator>=( const signed_int& i, const int32_t& v )    { return i.value >= v; }

    /**
     * Check if the given 32-bit integer is greater or equal to the given signed_int object
     *
     * @param i - 32-bit integer to compare
     * @param v - signed_int object to compare
     * @return true -  if i is greater or equal to v
     * @return false - otherwise
     */
    friend bool operator>=( const int32_t& i, const signed_int& v )    { return i       >= v.value; }

    /**
     * Check if the first given signed_int is greater or equal to the second given signed_int object
     *
     * @param i - First signed_int object to compare
     * @param v - Second signed_int object to compare
     * @return true -  if i is greater or equal to v
     * @return false - otherwise
     */
    friend bool operator>=( const signed_int& i, const signed_int& v ) { return i.value >= v.value; }


    /**
     *  Serialize an signed_int object with as few bytes as possible
     *
     *  @param ds - The stream to write
     *  @param v - The value to serialize
     *  @tparam DataStream - Type of datastream
     *  @return DataStream& - Reference to the datastream
     */
    template<typename DataStream>
    friend DataStream& operator << ( DataStream& ds, const signed_int& v ){
      uint32_t val = uint32_t((v.value<<1) ^ (v.value>>31));
      do {
         uint8_t b = uint8_t(val) & 0x7f;
         val >>= 7;
         b |= ((val > 0) << 7);
         ds.write((char*)&b,1);//.put(b);
      } while( val );
       return ds;
    }

    /**
     *  Deserialize an signed_int object
     *
     *  @param ds - The stream to read
     *  @param vi - The destination for deserialized value
     *  @tparam DataStream - Type of datastream
     *  @return DataStream& - Reference to the datastream
     */
    template<typename DataStream>
    friend DataStream& operator >> ( DataStream& ds, signed_int& vi ){
      uint32_t v = 0; char b = 0; int by = 0;
      do {
         ds.get(b);
         v |= uint32_t(uint8_t(b) & 0x7f) << by;
         by += 7;
      } while( uint8_t(b) & 0x80 );
      vi.value = ((v>>1) ^ (v>>31)) + (v&0x01);
      vi.value = v&0x01 ? vi.value : -vi.value;
      vi.value = -vi.value;
      return ds;
    }
};
}
