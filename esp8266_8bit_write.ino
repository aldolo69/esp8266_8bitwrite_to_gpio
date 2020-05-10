//how to use esp8266 gpio pins as an 8 bit parallel port
//aldo buson
//uses gpio from 0 to 15. 16 not supported
//max bitbang frequency is 500Khz


int _8bit_bits[8];
void _8bit_init(int gpio0,
                int gpio1,
                int gpio2,
                int gpio3,
                int gpio4,
                int gpio5,
                int gpio6,
                int gpio7)
{
  _8bit_bits[0] = (1 << gpio0);
  _8bit_bits[1] = (1 << gpio1);
  _8bit_bits[2] = (1 << gpio2);
  _8bit_bits[3] = (1 << gpio3);
  _8bit_bits[4] = (1 << gpio4);
  _8bit_bits[5] = (1 << gpio5);
  _8bit_bits[6] = (1 << gpio6);
  _8bit_bits[7] = (1 << gpio7);

  pinMode(gpio0, OUTPUT);//d1=5on nodemcu
  pinMode(gpio1, OUTPUT);//d2=4on nodemcu
  pinMode(gpio2, OUTPUT);//d3=0on nodemcu
  pinMode(gpio3, OUTPUT);//d4=2on nodemcu
  pinMode(gpio4, OUTPUT);//d5=14on nodemcu
  pinMode(gpio5, OUTPUT);//d6=12on nodemcu
  pinMode(gpio6, OUTPUT);//d7=13on nodemcu
  pinMode(gpio7, OUTPUT);//d8=15on nodemcu
}

void _8bit_write(int value)
{
  int output1 = 0;
  int output0 = 0;

#define _8bit_setbit(b) ({      \
    if (value & (1<<b))         \
    {                           \
      output1 += _8bit_bits[b]; \
    }                           \
    else                        \
    {                           \
      output0 += _8bit_bits[b]; \
    }                           \
  })

  _8bit_setbit(0);
  _8bit_setbit(1);
  _8bit_setbit(2);
  _8bit_setbit(3);
  _8bit_setbit(4);
  _8bit_setbit(5);
  _8bit_setbit(6);
  _8bit_setbit(7);

  GPOS = (output1);
  GPOC = (output0);
}


void setup() {
//nodemcu pins  
  _8bit_init(D1, D2, D3, D4, D5, D6, D7, D8);

}

void loop() {
  for (;;) {
    _8bit_write(128 + 0);
    _8bit_write(128 + 1);
    _8bit_write(128 + 2);
    _8bit_write(128 + 3);
    _8bit_write(4);
    _8bit_write(5);
    _8bit_write(6);
    _8bit_write(7);

  }
}
