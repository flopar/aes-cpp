// Utility functions 
uchar byteUpperBits(const uchar byte){
    return (byte & 0xF0);
}

uchar byteLowerBits(const uchar byte){
    return (byte & 0x0F);
}   


// AES functions

// SubBytes
uchar subByte(uchar messageByte, __global const uchar *sBox){
    uchar upperBits = byteUpperBits(messageByte)>>4;
    uchar lowerBits = byteLowerBits(messageByte);
    return sBox[(upperBits*0x10)+lowerBits];
}

// Sub message
void subMessage(__global uchar *message, __global uchar *output, __global const uchar *sBox){
    int i = get_global_id(0);
    int j = get_global_id(1);
    output[i*4+j] = subByte(message[i*4+j], sBox);
    barrier(CLK_GLOBAL_MEM_FENCE);
}

// MixColumns
uchar polynomialMul(uchar messageByte, uchar encryptionByte){
    if(encryptionByte == 0x2){
        // perform polynomial multiplication with X
        ushort res = messageByte << 1;
        // check if the 8th bit is set
        if (res &  0x0100){
            uchar temp = (uchar)res;
            res = temp^0x1B;
        }
        return res;
    }
    else if(encryptionByte == 0x3){
        // polynomial multiplication with (X+1)
        ushort res = messageByte << 1;
        res = res ^ messageByte;
        if(res & 0x0100){
            uchar temp = (uchar)res;
            res = temp ^ 0x1B;
        }
        return res; 
    }
    else{
        return messageByte;
    }
}



// Mix columns and key expansion done this way works only for Nb = Nk
void expandKey(__global uchar *expandedKey, __global const uchar *sBox, __global const unsigned int *rcon, uchar round){
    int i = get_global_id(0);
    int j = get_global_id(1);
    uchar k;
    unsigned int keyTemp=0; 
    for(k=0; k<4; k++){
        // Key expansion
        if(k==0){
            keyTemp =  (subByte(expandedKey[(4*0)+16*(round-1)+3], sBox) | subByte(expandedKey[(4*1)+16*(round-1)+3], sBox)<<8*3 | subByte(expandedKey[(4*2)+16*(round-1)+3], sBox)<<8*2 | subByte(expandedKey[(4*3)+16*(round-1)+3],sBox)<<8) ^ rcon[(round-1)];
        }
        keyTemp ^= (expandedKey[(4*(round-1)+0)*4+k]<<8*3 | expandedKey[(4*(round-1)+1)*4+k]<<8*2 | expandedKey[(4*(round-1)+2)*4+k]<<8 | expandedKey[(4*(round-1)+3)*4+k]);
        expandedKey[(4*round+0)*4+k] = (keyTemp&(0xFF<<(8*3)))>>(8*3);
        expandedKey[(4*round+1)*4+k] = (keyTemp&(0xFF<<(8*2)))>>(8*2);
        expandedKey[(4*round+2)*4+k] = (keyTemp&(0xFF<<8))>>8;
        expandedKey[(4*round+3)*4+k] = (keyTemp&0xFF);
    }
    barrier(CLK_GLOBAL_MEM_FENCE);
}

// Add Round Key
void addRoundKey( __global uchar *message, __global uchar *expandedKey, __global uchar *output, uchar round){
    int i = get_global_id(0);
    int j = get_global_id(1);
    output[i*4+j] = message[i*4+j] ^ expandedKey[(4*round+i)*4+j];
    barrier(CLK_GLOBAL_MEM_FENCE);
}

void shiftRows(__global uchar* output){
    uchar temp;
    int i = get_global_id(0);
    int j = get_global_id(1);
    int index = (i+j)%4;
    barrier(CLK_GLOBAL_MEM_FENCE);
    temp = output[i*4+index];
    barrier(CLK_GLOBAL_MEM_FENCE);
    output[i*4+j] = temp;
    barrier(CLK_GLOBAL_MEM_FENCE);
}

void mix(__global uchar *message, __global uchar *mixMatrix, __global uchar *output){
    uchar temp=0;   
    int i = get_global_id(0);
    int j = get_global_id(1);
    
    for(uchar k=0; k<4;k++){
        temp ^= polynomialMul(message[k*4+i], mixMatrix[j*4+k]);
    }
    output[j*4+i] = temp;
}
__kernel void aes(__global uchar *message, __global uchar *expandedKey, __global const uchar *sBox, 
                  __global const uchar *mixMatrix, __global uchar* output, 
                  __global const unsigned int *rcon){
    uchar round = 1;
    addRoundKey(message, expandedKey, output, 0); 
    for(;round<10;round++){
        subMessage(output, output, sBox);    
        shiftRows(output);
        mix(output, mixMatrix, message);
        expandKey(expandedKey, sBox, rcon, round);
        addRoundKey(message,expandedKey, output, round);
    }
    subMessage(output, output, sBox);    
    shiftRows(output);
    expandKey(expandedKey, sBox, rcon, round);
    addRoundKey(output,expandedKey, message, round);
}
