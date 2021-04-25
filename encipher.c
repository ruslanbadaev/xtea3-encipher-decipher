#include <stdint.h>
#include <stdio.h>

uint32_t rol(uint32_t base, uint32_t shift)
{
    uint32_t res;
    shift &= 0x1F;
    res = (base << shift) | (base >> (32 - shift));
    return res;
}

void xtea3_encipher(unsigned int num_rounds, uint32_t *v, uint32_t const *k)
{
    unsigned int i;
    uint32_t a, b, c, d, sum = 0, t, delta = 0x9E3779B9;
    sum = 0;
    a = v[0] + k[0];
    b = v[1] + k[1];
    c = v[2] + k[2];
    d = v[3] + k[3];
    for (i = 0; i < num_rounds; i++)
    {
        a += (((b << 4) + rol(k[(sum % 4) + 4], b)) ^
              (d + sum) ^ ((b >> 5) + rol(k[sum % 4], b >> 27)));
        sum += delta;
        c += (((d << 4) + rol(k[((sum >> 11) % 4) + 4], d)) ^
              (b + sum) ^ ((d >> 5) + rol(k[(sum >> 11) % 4], d >> 27)));
        t = a;
        a = b;
        b = c;
        c = d;
        d = t;
    }
    v[0] = a ^ k[4];
    v[1] = b ^ k[5];
    v[2] = c ^ k[6];
    v[3] = d ^ k[7];
}

int main(void)
{
    //xtea3_encipher();
    return 0;
}