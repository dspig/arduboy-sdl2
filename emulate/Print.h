#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h>

// #include "WString.h"
// #include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

class Print
{
  private:
    int write_error;
  //   size_t printNumber(unsigned long, uint8_t);
  //   size_t printFloat(double, uint8_t);
  protected:
    void setWriteError(int err = 1) { write_error = err; }
  public:
    Print() : write_error(0) {}
  
    int getWriteError() { return write_error; }
    void clearWriteError() { setWriteError(0); }
  
    virtual size_t write(uint8_t) = 0;
    size_t write(const char *str) {
      if (str == NULL) return 0;
      return write((const uint8_t *)str, strlen(str));
    }
	
    virtual size_t write(const uint8_t *buffer, size_t size) {
	  size_t n = 0;
	  while (size--) {
	    if (write(*buffer++)) n++;
	    else break;
	  }
	  return n;
	}
	
    size_t write(const char *buffer, size_t size) {
      return write((const uint8_t *)buffer, size);
    }
    
    size_t print(const char str[]) { return write((const char *)str); };
    size_t print(char c) { return write(c); };
    size_t print(unsigned char b, int base = DEC) { return print((unsigned long) b, base); };
    size_t print(int n, int base = DEC) { return print((long) n, base); };
    size_t print(unsigned int n, int base = DEC) { return print((unsigned long) n, base); };
    size_t print(long, int = DEC) { return 0; };
    size_t print(unsigned long, int = DEC) { return 0; };
    size_t print(double, int = 2) { return 0; };

    size_t println(const char str[]) {
		size_t n = print(str);
		n += println();
		return n;
	};
	
    size_t println(char c) {
		size_t n = print(c);
		n += println();
		return n;
    };
	
    size_t println(unsigned char c, int base = DEC) {
		size_t n = print(c, base);
		n += println();
		return n;
    };
	
    size_t println(int n, int base = DEC) { return println((long) n, base); };
	
    size_t println(unsigned int n, int base = DEC) { return println((unsigned long) n, base); };
	
    size_t println(long l, int base = DEC) {
		size_t n = print(l, base);
		n += println();
		return n;
	};

    size_t println(unsigned long l, int base = DEC) {
		size_t n = print(l, base);
		n += println();
		return n;
	};
		
    size_t println(double d, int base = 2) {
		size_t n = print(d, base);
		n += println();
		return n;
	};

    size_t println(void) {
    	return print("\r\n");
    };
};

#endif