#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  int i;
	for(i = 0; s[i] != '\0'; i++);
	return i;
}

char *strcpy(char* dst,const char* src) {
  int i;
	for(i = 0; src[i] != '\0'; i++){
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return dst;
}

char* strncpy(char* dst, const char* src, size_t n) {
	char *tmp = dst;
	while (n) {
		if ((*tmp = *src) != 0)
			src++;
		tmp++;
		n--;
	}
  return dst;
}

char* strcat(char* dst, const char* src) {
  int n = strlen(dst);
	int i;
	for(i = 0; src[i] != '\0'; i++){
		dst[n+i] = src[i];
	}
	dst[n+i] = '\0';
	return dst;
}

int strcmp(const char* s1, const char* s2) {
  unsigned char c1, c2;
	while (1) {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  unsigned char c1, c2;
	while (n) {
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
		n--;
	}
	return 0;
}

void* memset(void* v,int c,size_t n) {
  char *xs = v;
	while (n--)
		*xs++ = c;
	return v;
}

void* memcpy(void* out, const void* in, size_t n) {
  char *tmp = out;
	const char *s = in;
 
	while (n--)
		*tmp++ = *s++;
	return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  const unsigned char *su1, *su2;
	int res = 0;
 
	for (su1 = s1, su2 = s2; 0 < n; ++su1, ++su2, n--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}

#endif
