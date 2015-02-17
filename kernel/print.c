void print(const char* a) {
	char *v = (char*)0xB8000;
	while(*a!=0) {
		*v++=*a++;
		*v++=(char)7;
	}	
}
