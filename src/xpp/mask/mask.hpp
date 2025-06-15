#pragma once 

class MaskBit{
    private:
    long data;
    public:
    MaskBit(long _initial = 0);
    bool empty() const;
    bool contains(long newmask);
    long unwrap();
    void add(long newmask);
    void remove(long newmask);
};