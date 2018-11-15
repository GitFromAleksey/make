#if !defined(DATASTREAM_H)
#   define DATASTREAM_H

//#############################################################################

enum ByteOrder {bigEndian, littleEndian};

struct DataStreamBase
{
    template <ByteOrder v> struct ByteOrder2Type {enum {value = v};};
};

//#############################################################################

template <ByteOrder byteOrder>
class DataStreamForRead: private DataStreamBase
{
public:
    DataStreamForRead() {}
    DataStreamForRead(const u8 *p): readPtr(p) {}
    //-----------------------------------------------------------------------
    void setFocus(const u8 *p) {readPtr = p;}
    const u8 *focus() const {return readPtr;}
    //-----------------------------------------------------------------------
    void skipReadRawData(u32 len) {readPtr += len;}
    //-----------------------------------------------------------------------
    void readRawData(u8 *s, u32 len)
    {
        const u8 *p = readPtr;
        while (len--)
        {
            *s++ = *p++;
        }
        readPtr = p;
    }
    //-----------------------------------------------------------------------
    DataStreamForRead &readBytes(u8 *s, u32 len)
    {
        readRawData(s, len);
        return *this;
    }
    //-----------------------------------------------------------------------
    void readString(char *s)
    {
        const u8 *p = readPtr;
        while (*s)
        {
            *s++ = *p++;
        }
        readPtr = p;
    }
    //-----------------------------------------------------------------------
    DataStreamForRead &operator >>(char *s)
    {
        readString(s);
        return *this;
    }
    //-----------------------------------------------------------------------
    u8 read8() {return *readPtr++;}
    u16 read16() {return read16(ByteOrder2Type<byteOrder>());}
    u32 read32() {return read32(ByteOrder2Type<byteOrder>());}
    u64 read64() {return read64(ByteOrder2Type<byteOrder>());}
    //-----------------------------------------------------------------------
    DataStreamForRead &operator >>(u8 &i)
    {
        i = read8();
        return *this;
    }
    DataStreamForRead &operator >>(s8 &i)
    {
        return *this >> *(u8 *)&i;
    }
    //-----------------------------------------------------------------------
    DataStreamForRead &operator >>(u16 &i)
    {
        i = read16();
        return *this;
    }
    DataStreamForRead &operator >>(s16 &i)
    {
        return *this >> *(u16 *)&i;
    }
    //-----------------------------------------------------------------------
    DataStreamForRead &operator >>(u32 &i)
    {
        i = read32();
        return *this;
    }
    DataStreamForRead &operator >>(s32 &i)
    {
        return *this >> *(u32 *)&i;
    }
    //-----------------------------------------------------------------------
    DataStreamForRead &operator >>(u64 &i)
    {
        i = read64();
        return *this;
    }
    DataStreamForRead &operator >>(s64 &i)
    {
        return *this >> *(u64 *)&i;
    }
    //-----------------------------------------------------------------------
    DataStreamForRead &operator >>(bool &i)
    {
        return *this >> *(u8 *)&i;
    }
    //-----------------------------------------------------------------------
private:
    const u8 *readPtr;
    //-----------------------------------------------------------------------
    u16 read16(ByteOrder2Type<littleEndian>)
    {
        u16 res;
        const u8 *p = readPtr;
        res  = u16(*p++) << 8 * 0;
        res |= u16(*p++) << 8 * 1;
        readPtr = p;
        return res;
    }
    u32 read32(ByteOrder2Type<littleEndian>)
    {
        u32 res;
        const u8 *p = readPtr;
        res  = u32(*p++) << 8 * 0;
        res |= u32(*p++) << 8 * 1;
        res |= u32(*p++) << 8 * 2;
        res |= u32(*p++) << 8 * 3;
        readPtr = p;
        return res;
    }
    u64 read64(ByteOrder2Type<littleEndian>)
    {
        u64 res;
        const u8 *p = readPtr;
        res  = u64(*p++) << 8 * 0;
        res |= u64(*p++) << 8 * 1;
        res |= u64(*p++) << 8 * 2;
        res |= u64(*p++) << 8 * 3;
        res |= u64(*p++) << 8 * 4;
        res |= u64(*p++) << 8 * 5;
        res |= u64(*p++) << 8 * 6;
        res |= u64(*p++) << 8 * 7;
        readPtr = p;
        return res;
    }
    //-----------------------------------------------------------------------
    u16 read16(ByteOrder2Type<bigEndian>)
    {
        u16 res;
        const u8 *p = readPtr;
        res  = u16(*p++) << 8 * 1;
        res |= u16(*p++) << 8 * 0;
        readPtr = p;
        return res;
    }
    u32 read32(ByteOrder2Type<bigEndian>)
    {
        u32 res;
        const u8 *p = readPtr;
        res  = u32(*p++) << 8 * 3;
        res |= u32(*p++) << 8 * 2;
        res |= u32(*p++) << 8 * 1;
        res |= u32(*p++) << 8 * 0;
        readPtr = p;
        return res;
    }
    u64 read64(ByteOrder2Type<bigEndian>)
    {
        u64 res;
        const u8 *p = readPtr;
        res  = u64(*p++) << 8 * 7;
        res |= u64(*p++) << 8 * 6;
        res |= u64(*p++) << 8 * 5;
        res |= u64(*p++) << 8 * 4;
        res |= u64(*p++) << 8 * 3;
        res |= u64(*p++) << 8 * 2;
        res |= u64(*p++) << 8 * 1;
        res |= u64(*p++) << 8 * 0;
        readPtr = p;
        return res;
    }
};

//#############################################################################

template <ByteOrder byteOrder>
class DataStreamForWrite: private DataStreamBase
{
public:
    DataStreamForWrite() {}
    DataStreamForWrite(u8 *p): writePtr(p) {}
    //-----------------------------------------------------------------------
    void setFocus(u8 *p) {writePtr = p;}
    u8 *focus() const {return writePtr;}
    //-----------------------------------------------------------------------
    void skipWriteRawData(u32 len) {writePtr += len;}
    //-----------------------------------------------------------------------
    void writeRawData(const u8 *s, u32 len)
    {
        u8 *p = writePtr;
        while (len--)
        {
            *p++ = *s++;
        }
        writePtr = p;
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &writeBytes(const u8 *s, u32 len)
    {
        writeRawData(s, len);
        return *this;
    }
    //-----------------------------------------------------------------------
    void writeString(const char *s)
    {
        u8 *p = writePtr;
        while (*s)
        {
            *p++ = *s++;
        }
        writePtr = p;
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(const char *s)
    {
        writeString(s);
        return *this;
    }
    //-----------------------------------------------------------------------
    void write8(u8 i) {*writePtr++ = i;}
    void write16(u16 i) {write16(i, ByteOrder2Type<byteOrder>());}
    void write32(u32 i) {write32(i, ByteOrder2Type<byteOrder>());}
    void write64(u64 i) {write64(i, ByteOrder2Type<byteOrder>());}
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(u8 i)
    {
        write8(i);
        return *this;
    }
    DataStreamForWrite &operator <<(s8 i)
    {
        return *this << u8(i);
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(u16 i)
    {
        write16(i);
        return *this;
    }
    DataStreamForWrite &operator <<(s16 i)
    {
        return *this << u16(i);
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(u32 i)
    {
        write32(i);
        return *this;
    }
    DataStreamForWrite &operator <<(s32 i)
    {
        return *this << u32(i);
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(u64 i)
    {
        write64(i);
        return *this;
    }
    DataStreamForWrite &operator <<(s64 i)
    {
        return *this << u64(i);
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(const f32 &f)
    {
        return *this << *(s32 *)&f;
    }
    //-----------------------------------------------------------------------
    DataStreamForWrite &operator <<(bool i)
    {
        return *this << u8(i);
    }
    //-----------------------------------------------------------------------
private:
    u8 *writePtr;
    //-----------------------------------------------------------------------
    void write16(u16 i, ByteOrder2Type<littleEndian>)
    {
        u8 *p = writePtr;
        *p++ = i >> 8 * 0;
        *p++ = i >> 8 * 1;
        writePtr = p;
    }
    void write32(u32 i, ByteOrder2Type<littleEndian>)
    {
        u8 *p = writePtr;
        *p++ = i >> 8 * 0;
        *p++ = i >> 8 * 1;
        *p++ = i >> 8 * 2;
        *p++ = i >> 8 * 3;
        writePtr = p;
    }
    void write64(u64 i, ByteOrder2Type<littleEndian>)
    {
        u8 *p = writePtr;
        *p++ = i >> 8 * 0;
        *p++ = i >> 8 * 1;
        *p++ = i >> 8 * 2;
        *p++ = i >> 8 * 3;
        *p++ = i >> 8 * 4;
        *p++ = i >> 8 * 5;
        *p++ = i >> 8 * 6;
        *p++ = i >> 8 * 7;
        writePtr = p;
    }
    //-----------------------------------------------------------------------
    void write16(u16 i, ByteOrder2Type<bigEndian>)
    {
        u8 *p = writePtr;
        *p++ = i >> 8 * 1;
        *p++ = i >> 8 * 0;
        writePtr = p;
    }
    void write32(u32 i, ByteOrder2Type<bigEndian>)
    {
        u8 *p = writePtr;
        *p++ = i >> 8 * 3;
        *p++ = i >> 8 * 2;
        *p++ = i >> 8 * 1;
        *p++ = i >> 8 * 0;
        writePtr = p;
    }
    void write64(u64 i, ByteOrder2Type<bigEndian>)
    {
        u8 *p = writePtr;
        *p++ = i >> 8 * 7;
        *p++ = i >> 8 * 6;
        *p++ = i >> 8 * 5;
        *p++ = i >> 8 * 4;
        *p++ = i >> 8 * 3;
        *p++ = i >> 8 * 2;
        *p++ = i >> 8 * 1;
        *p++ = i >> 8 * 0;
        writePtr = p;
    }
};

//#############################################################################

template <ByteOrder byteOrder = littleEndian>
class DataStream:
    public DataStreamForRead<byteOrder>,
    public DataStreamForWrite<byteOrder>
{
public:
    DataStream() {}
    DataStream(u8 *base, u32 count = 0):
        DataStreamForRead<byteOrder>(base),
        DataStreamForWrite<byteOrder>(base + count)
    {}
    //-----------------------------------------------------------------------
    void init(u8 *base, u32 count = 0)
    {
        DataStreamForRead<byteOrder>::setFocus(base);
        DataStreamForWrite<byteOrder>::setFocus(base + count);
    }
    //-----------------------------------------------------------------------
    void setWriteFocus(u8 *p)
    {
        DataStreamForWrite<byteOrder>::setFocus(p);
    }
    //-----------------------------------------------------------------------
    u8 *writeFocus() const
    {
        return DataStreamForWrite<byteOrder>::focus();
    }
    //-----------------------------------------------------------------------
    void setReadFocus(const u8 *p)
    {
        DataStreamForRead<byteOrder>::setFocus(p);
    }
    //-----------------------------------------------------------------------
    const u8 *readFocus() const
    {
        return DataStreamForRead<byteOrder>::focus();
    }
    //-----------------------------------------------------------------------
    s32 count() const {return writeFocus() - readFocus();}
    //-----------------------------------------------------------------------
    bool isErrorPresent() const {return writeFocus() < readFocus();}
};

//#############################################################################

#endif  // DATASTREAM_H
