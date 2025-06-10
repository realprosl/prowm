#include<mask.hpp>

MaskBit::MaskBit(long _initial) : data(_initial) {}

bool MaskBit::contains(long newmask){
    return (data & newmask) == newmask;
}

bool MaskBit::empty() const{
    return data == 0;
}

long MaskBit::unwrap(){
    return data;
}

void MaskBit::add(long newmask){
    if(data == 0) data = newmask;
    else data |= newmask;
}

void MaskBit::remove(long newmask){
    data &= ~newmask;
}